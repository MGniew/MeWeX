
#include "Cover.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "../../utils/File.h"
#include "../../utils/Textual.h"

#include "../../structure/io/DecodedTupleStorageIO.h"

#include "../../function/FunctionFactory.h"
#include "../../function/filter/Filtrator.h"



namespace program
{
	namespace cover
	{


void Cover::check(Config const& pConfig)
{
	mConfig = pConfig;

	loadData();
	check();

	std::cerr << "Done." << std::endl;
}


void Cover::loadData()
{
	mTupleStorage = structure::io::DecodedTupleStorageIO().read(mConfig.inputDirectory);

	{
		RelevantLoader::ElementOrder elementOrder =
			mConfig.tupleElementsFixedOrder ?
				RelevantLoader::ElementOrder::FIXED :
				RelevantLoader::ElementOrder::FLEXIBLE;

		if (!mConfig.filter.empty())
		{
			typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
			typedef function::filter::Filtrator					__Filtrator;

			std::cerr << "Building filter: " << mConfig.filter << std::endl;
			__FilterPtrS filter = function::FunctionFactory().createFilterFunction(mConfig.filter);
			filter->initialize(mTupleStorage);

			std::cerr << "Filtering using: " << filter->reprezentation() << std::endl;
			TupleIdVector ids = __Filtrator()(*mTupleStorage, filter);
			mInterestedTupleIdSet.insert(ids.begin(), ids.end());
		}
		else
		{
			for (auto iter = mTupleStorage->beginTuples(); iter != mTupleStorage->endTuples(); ++iter)
			{
				mInterestedTupleIdSet.insert(mTupleStorage->findTupleId(iter));
			}
		}

		std::cerr << "Loading relevant set..." << std::endl;
		mRelevantTupleIdSet = RelevantLoader().loadFromFile(
			mConfig.fileWithRelevantSet,
			*mTupleStorage,
			elementOrder,
			mInterestedTupleIdSet);
	}
}


void Cover::check()
{
	std::cerr << "Computing cover between relations..." << std::endl;
	auto matrix = computeCoverMatrix();

	std::cerr << "Computing relevant units per relation..." << std::endl;
	auto relevants = computeRelevantStats();

	std::cerr << "Writing results..." << std::endl;
	writeRelevantSet();
	writeStatistics(matrix, relevants);
}


auto Cover::computeCoverMatrix() const -> CoverMatrix
{
	std::map<RelationId, size_t> relationIndex;
	for (auto iter = mTupleStorage->beginRelations(); iter != mTupleStorage->endRelations(); ++iter)
	{
		relationIndex.insert(std::pair<RelationId, size_t>(
			mTupleStorage->findRelationId(iter), relationIndex.size()));
	}

	CoverMatrix matrix(relationIndex.size(), relationIndex.size());

	for (auto iter = mTupleStorage->beginTuples(); iter != mTupleStorage->endTuples();)
	{
		TupleIdVector tupleIdVector = mTupleStorage->findTupleIdsAllRelations(*iter);
		std::advance(iter, tupleIdVector.size());

		for (size_t i = 0; i < tupleIdVector.size(); ++i)
		{
			RelationId rid = mTupleStorage->findTuple(tupleIdVector[i]).getRelation();
			size_t idx = relationIndex.find(rid)->second;
			matrix[idx][idx] += 1;
			for (size_t j = i + 1; j < tupleIdVector.size(); ++j)
			{
				RelationId secondRid = mTupleStorage->findTuple(tupleIdVector[j]).getRelation();
				size_t secondIdx = relationIndex.find(secondRid)->second;
				matrix[idx][secondIdx] += 1;
				matrix[secondIdx][idx] += 1;
			}
		}
	}

	return matrix;
}


auto Cover::computeRelevantStats() const -> RelevantStats
{
	RelevantStats relevant;

	for (auto iter = mTupleStorage->beginRelations(); iter != mTupleStorage->endRelations(); ++iter)
	{
		relevant.insert(std::pair<RelationId, size_t>(mTupleStorage->findRelationId(iter), 0));
	}


	for (auto iter = mRelevantTupleIdSet->begin(); iter != mRelevantTupleIdSet->end(); ++iter)
	{
		TupleStorage::TupleT const& tuple = mTupleStorage->findTuple(*iter);
		auto insertIter = relevant.find(tuple.getRelation());
		insertIter->second += 1;
	}

	return relevant;
}


void Cover::writeRelevantSet() const
{
	std::cerr << "Opening relevant set output file..." << std::endl;
	std::string ofn = mConfig.inputDirectory + '/' + mConfig.outputRelevantSetFile;
	std::fstream outputFile(ofn, std::ios_base::out);
	EXCEPTION(outputFile.is_open(), "Cover::writeRelevantSet(): Cannot open output file '" << ofn << "'.");
	utils::setStreamMaxDoublePrecision(outputFile);

	for (auto iter = mRelevantTupleIdSet->begin(); iter != mRelevantTupleIdSet->end(); ++iter)
	{
		outputFile << mTupleStorage->createTupleWordChain(*iter) << std::endl;
	}

	outputFile.close();
}


void Cover::writeStatistics(
	CoverMatrix const& 		pCoverMatrix,
	RelevantStats const&	pRelevantStats)	const
{
	std::cerr << "Opening stats output file..." << std::endl;
	std::string ofn = mConfig.inputDirectory + '/' + mConfig.outputStatsFile;
	std::fstream outputFile(ofn, std::ios_base::out);
	EXCEPTION(outputFile.is_open(), "Cover::computeAndWriteCover(): Cannot open output file '" << ofn << "'.");
	utils::setStreamMaxDoublePrecision(outputFile);

	for (auto relationIter = mTupleStorage->beginRelations(); relationIter != mTupleStorage->endRelations(); ++relationIter)
	{
		TupleStorage::RelationT const& relation = mTupleStorage->findRelation(relationIter);
		outputFile << '\t' << relation.getName() << ' ' << relation.getArity();
	}
	outputFile << std::endl;

	{
		auto relationIter = mTupleStorage->beginRelations();
		for (size_t r = 0; r < pCoverMatrix.getRowCount(); ++r)
		{
			TupleStorage::RelationT const& relation = mTupleStorage->findRelation(relationIter);
			outputFile << relation.getName() << ' ' << relation.getArity();
			for (size_t c = 0; c < pCoverMatrix.getRowSize(); ++c)
			{
				outputFile << '\t' << pCoverMatrix[r][c];
			}
			outputFile << std::endl;

			++relationIter;
		}
	}

	outputFile << std::endl << "Relevant units per relation:" << std::endl;

	size_t sum = 0;
	for (auto iter = pRelevantStats.begin(); iter != pRelevantStats.end(); ++iter)
	{
		outputFile << mTupleStorage->createRelationReprezentation(iter->first) << '\t' << iter->second << std::endl;
		sum += iter->second;
	}

	outputFile << std::endl << "Relevant units sum:\t" << sum << std::endl;

	outputFile.close();
}


	}
}
