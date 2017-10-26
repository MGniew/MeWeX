
#include <iostream>
#include <fstream>

#include "../../utils/Time.h"
#include "../../utils/File.h"
#include "../../utils/Textual.h"

#include "../../structure/io/StreamingFileReader.h"
#include "../../structure/io/KBestTupleListIO.h"
#include "../../structure/io/DecodedTupleStorageIO.h"

#include "../../function/filter/Filtrator.h"

#include "Digger.h"


namespace program
{
	namespace digger
	{


void Digger::dig(Config const& pConfig)
{
	mConfig = pConfig;

	createFunctions();
	loadData();
	initialize();
	dig();

	std::cerr << "Done" << std::endl;
}


void Digger::createFunctions()
{
	function::FunctionFactory ff;
	for (size_t af = 0; af < mConfig.associationFunctions.size(); ++af)
	{
		std::cerr << "Building association function: " << mConfig.associationFunctions[af] << std::endl;
		mAssociationFunctions.push_back(ff.createAssociationFunction(mConfig.associationFunctions[af]));
		std::cerr << "Build association function: " << (*mAssociationFunctions.rbegin())->reprezentation() << std::endl;
	}

	for (size_t avf = 0; avf < mConfig.associationVectorFunctions.size(); ++avf)
	{
		std::cerr << "Building association vector function: " << mConfig.associationVectorFunctions[avf] << std::endl;
		mAssociationVectorFunctions.push_back(ff.createAssociationVectorFunction(mConfig.associationVectorFunctions[avf]));
		std::cerr << "Build association vector function: " << (*mAssociationVectorFunctions.rbegin())->reprezentation() << std::endl;
	}

	for (size_t af = 0; af < mConfig.aggregationFunctions.size(); ++af)
	{
		std::cerr << "Building aggregation function: " << mConfig.aggregationFunctions[af] << std::endl;
		mAggregationFunctions.push_back(ff.createAggregationFunction(mConfig.aggregationFunctions[af]));
		std::cerr << "Build aggregation function: " << (*mAggregationFunctions.rbegin())->reprezentation() << std::endl;
	}

	for (size_t q = 0; q < mConfig.qualityFunctions.size(); ++q)
	{
		std::cerr << "Building quality function: " << mConfig.qualityFunctions[q] << std::endl;
		mQualityFunctions.push_back(ff.createQualityFunction(mConfig.qualityFunctions[q]));
		std::cerr << "Build quality function: " << (*mQualityFunctions.rbegin())->reprezentation() << std::endl;
	}
}


void Digger::loadData()
{
	typedef structure::storage::TupleFrequencyIndex::TableCreationPolicy __Policy;

	mTupleStorage.reset(new TupleStorage());
	structure::io::DecodedTupleStorageIO().read(mConfig.inputDirectory, *mTupleStorage);

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
			filter->construct(*mTupleStorage);

			std::cerr << "Filtering using: " << filter->reprezentation() << std::endl;
			mInterestedTupleIdVector = __Filtrator()(*mTupleStorage, filter);

			if (!mConfig.qualityFunctions.empty())
			{
				std::cerr << "Loading relevant set using tuple id set..." << std::endl;
				mRelevantTupleIdSet = RelevantLoader().loadFromFile(
					mConfig.fileWithRelevantSet,
					*mTupleStorage,
					elementOrder,
					TupleStorage::TupleIdSet(
						mInterestedTupleIdVector.begin(), mInterestedTupleIdVector.end()));
			}
		}
		else
		{
			mInterestedTupleIdVector.reserve(mTupleStorage->getDistinctTupleCount());
			for (auto iter = mTupleStorage->beginTuples(); iter != mTupleStorage->endTuples(); ++iter)
			{
				mInterestedTupleIdVector.push_back(mTupleStorage->findTupleId(iter));
			}

			if (!mConfig.qualityFunctions.empty())
			{
				std::cerr << "Loading relevant set..." << std::endl;
				mRelevantTupleIdSet = RelevantLoader().loadFromFile(
					mConfig.fileWithRelevantSet,
					*mTupleStorage,
					elementOrder);
			}
		}
	}

	if (!mConfig.fileWithTupleFrequencyIndex.empty())
	{
		std::cerr << "Loading tuple frequency index..." << std::endl;
		mTupleFrequencyIndex = structure::io::TupleFrequencyIndexIO().
			read(*mTupleStorage, mConfig.fileWithTupleFrequencyIndex);
		switch (mConfig.indexTableCreationPolicy)
		{
			case 'n':
			{
				mTupleFrequencyIndex->setTableCreationPolicy(__Policy::JOIN_NONE);
			}
			break;
			case 's':
			{
				mTupleFrequencyIndex->setTableCreationPolicy(__Policy::JOIN_SAME_SIZE_RELATIONS);
			}
			break;
			case 'a':
			{
				mTupleFrequencyIndex->setTableCreationPolicy(__Policy::JOIN_ALL_RELATIONS);
			}
			break;
			default:
			{
				XASSERT(false, "Unknown Tuple Frequency Index table creation policy.");
			}
		}
	}
	else if (!mConfig.fileWithContingencyTable.empty())
	{
		std::cerr << "Loading contingency table..." << std::endl;
		mContingencyTable = structure::io::ContingencyTableIO().
			read(*mTupleStorage, mConfig.fileWithContingencyTable);
	}
	else
	{
		std::cerr << "Contingency table neither tuple frequency index file set." << std::endl;
	}

	if (!mConfig.fileWithWcclOperators.empty())
	{
		std::cerr << "Loading wccl operators..." << std::endl;
		mWcclOperatorDataVector = structure::builder::WcclOperatorLoader<Wccl::Bool>().
			loadOperators(getTagset(), mConfig.fileWithWcclOperators, "");
	}

	if (!mConfig.fileWithCorporas.empty())
	{
		std::cerr << "Loading corporas list..." << std::endl;
		utils::loadLinesFromFile(mConfig.fileWithCorporas, mCorporaVector);
	}
}


void Digger::initialize()
{
	for (size_t af = 0; af < mAssociationFunctions.size(); ++af)
	{
		mAssociationFunctions[af]->initialize(mTupleStorage, mTupleFrequencyIndex, mContingencyTable);
	}

	for (size_t avf = 0; avf < mAssociationVectorFunctions.size(); ++avf)
	{
		mAssociationVectorFunctions[avf]->initialize(mTupleStorage, mTupleFrequencyIndex, mContingencyTable);
	}
}


void Digger::dig() const
{
	Extractor extractor;

	OrthMap orths;
	bool extractOrths = !mConfig.fileWithCorporas.empty();

	if (mConfig.speedItUp)
	{
		digSingleComponentSpeededUp(extractor, orths, extractOrths);
	}
	else
	{
		digSingleComponent(extractor, orths, extractOrths);
	}

	digMultiComponent(extractor, orths, extractOrths);

	if (extractOrths)
	{
		std::cerr << "Extracting orths..." << std::endl;
		extractAndWriteOrths(orths);
	}
}


void Digger::digSingleComponent(
	Extractor& 	pExtractor,
	OrthMap&	pOrthMap,
	bool		pExtractOrths) const
{
	for (size_t af = 0; af < mAssociationFunctions.size(); ++af)
	{
		std::string associationFunctionReprezentation = mAssociationFunctions[af]->reprezentation();

		std::cerr << "Digging using: " << associationFunctionReprezentation << std::endl;
		utils::Time diggingStart;

		KBestTupleList kbestResult = pExtractor.extract(
			mAssociationFunctions[af],
			mInterestedTupleIdVector,
			mConfig.kbestLength,
			mConfig.threadCount);
		kbestResult.setDescription(associationFunctionReprezentation);

		utils::Time diggingEnd;
		std::cerr << "Digging time: " << (diggingEnd - diggingStart) << "sec" << std::endl;

		writeKBest(kbestResult, af);
		computeAndWriteQualites(kbestResult, af, associationFunctionReprezentation);

		if (pExtractOrths)
		{
			for (size_t i = 0; i < kbestResult.size(); ++i)
			{
				pOrthMap.insert(OrthMapElement(kbestResult[i].element, std::map<std::string, size_t>()));
			}
		}
	}
}


void Digger::digSingleComponentSpeededUp(
	Extractor& 	pExtractor,
	OrthMap&	pOrthMap,
	bool		pExtractOrths) const
{
	function::FunctionFactory::AssociationVectorFunctionPtrS functions(
		new function::association::AssociationVectorFunction(mAssociationFunctions));
	functions->initialize(mTupleStorage, mTupleFrequencyIndex, mContingencyTable);

	std::cerr << "Digging speeded up using: " << functions->reprezentation() << std::endl;
	utils::Time diggingStart;

	KBestTupleListVector kbestResultVector = pExtractor.extract(
		functions,
		mInterestedTupleIdVector,
		mConfig.kbestLength,
		mConfig.threadCount);

	utils::Time diggingEnd;
	std::cerr << "Digging time: " << (diggingEnd - diggingStart) << "sec" << std::endl;

	for (size_t i = 0; i < kbestResultVector.size(); ++i)
	{
		std::string repr = mAssociationFunctions[i]->reprezentation();
		kbestResultVector[i].setDescription(repr);
		writeKBest(kbestResultVector[i], i);
		computeAndWriteQualites(kbestResultVector[i], i, repr);

		/* orths */
		for (size_t j = 0; j < kbestResultVector[i].size() && pExtractOrths; ++j)
		{
			pOrthMap.insert(OrthMapElement(kbestResultVector[i][j].element, std::map<std::string, size_t>()));
		}
	}
}


void Digger::digMultiComponent(
	Extractor& 	pExtractor,
	OrthMap&	pOrthMap,
	bool		pExtractOrths) const
{
	for (size_t avf = 0; avf < mAssociationVectorFunctions.size(); ++avf)
	{
		std::string associationFunctionReprezentation = mAssociationVectorFunctions[avf]->reprezentation();

		std::cerr << "Digging using: " << associationFunctionReprezentation << std::endl;
		utils::Time diggingStart;

		KBestTupleListVector kbestResultVector = pExtractor.extract(
			mAssociationVectorFunctions[avf],
			mInterestedTupleIdVector,
			mConfig.kbestLength,
			mConfig.threadCount);

		KBestTupleList kbestResult = (*mAggregationFunctions[avf])(kbestResultVector);
		kbestResult.setDescription(associationFunctionReprezentation);

		utils::Time diggingEnd;
		std::cerr << "Digging time: " << (diggingEnd - diggingStart) << "sec" << std::endl;

		writeKBest(kbestResult, avf + mAssociationFunctions.size());
		computeAndWriteQualites(kbestResult, avf + mAssociationFunctions.size(), associationFunctionReprezentation);

		if (pExtractOrths)
		{
			for (size_t i = 0; i < kbestResult.size(); ++i)
			{
				pOrthMap.insert(OrthMapElement(kbestResult[i].element, std::map<std::string, size_t>()));
			}
		}
	}
}


void Digger::writeKBest(
	KBestTupleList const& 	pKBest,
	size_t					pAssociationFunctionIndex) const
{
	std::cerr << "Writing kbest..." << std::endl;
	structure::io::KBestTupleListIO().write(
			pKBest,
		*mTupleStorage,
		mConfig.outputDirectory + '/' + std::to_string(pAssociationFunctionIndex) + ".kbest.csv");
}


void Digger::computeAndWriteQualites(
	KBestTupleList const& 	pKBest,
	size_t					pAssociationFunctionIndex,
	std::string const&		pAssociationFunctionReprezentation) const
{
	for (size_t q = 0; q < mQualityFunctions.size(); ++q)
	{
		std::cerr << "Checking result quality using: " << mQualityFunctions[q]->reprezentation() << std::endl;
		function::quality::QualityMatrix qualityResult =
			(*mQualityFunctions[q])(pKBest, mRelevantTupleIdSet, *mTupleStorage);
		qualityResult.setDescription(
			pAssociationFunctionReprezentation + '\n' +
			mQualityFunctions[q]->reprezentation());

		std::string qualityOutputFile = mConfig.outputDirectory + '/' + std::to_string(pAssociationFunctionIndex) + '.' + std::to_string(q) + ".quality.csv";
		std::fstream output(
				qualityOutputFile,
			std::ios_base::out);
		EXCEPTION(output.is_open(), "Digger::checkQuality(): Cannot open output file '" << qualityOutputFile << "'.");
		utils::setStreamMaxDoublePrecision(output);
		qualityResult.writeToStream(output);
		output.close();
	}
}


void Digger::extractAndWriteOrths(OrthMap& pOrthMap) const
{
	typedef structure::builder::OrthExtractor OrthExtractor;

	OrthExtractor().extract(pOrthMap, mTupleStorage, mCorporaVector, mWcclOperatorDataVector, getTagset(), mConfig.readerName);

	std::fstream orthsOutputFile(mConfig.outputDirectory + "/orths.csv", std::ios_base::out);
	EXCEPTION(orthsOutputFile.is_open(), "Digger::dig(): Cannot open output file '" << mConfig.outputDirectory << "/orths.csv'.");

	for (auto iter = pOrthMap.begin(); iter != pOrthMap.end(); ++iter)
	{
		orthsOutputFile << mTupleStorage->createTupleReprezentation(iter->first) << std::endl;
		for (auto orth = iter->second.begin(); orth != iter->second.end(); ++orth)
		{
			orthsOutputFile << '\t' << orth->second << ' ' << orth->first << std::endl;
		}
	}
}


Corpus2::Tagset const& Digger::getTagset() const
{
	return Corpus2::get_named_tagset(mConfig.tagsetName);
}


	}
}
