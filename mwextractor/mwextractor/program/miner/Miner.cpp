
#include <iostream>
#include <fstream>

#include "../../utils/Time.h"
#include "../../utils/File.h"
#include "../../utils/Textual.h"

#include "../../structure/io/StreamingFileReader.h"
#include "../../structure/io/KBestTupleListIO.h"
#include "../../structure/io/DecodedTupleStorageIO.h"

#include "../../function/filter/Filtrator.h"

#include "Miner.h"


namespace program
{
	namespace miner
	{


void Miner::build(Config const& pConfig)
{
	mConfig = pConfig;

	srand(static_cast<unsigned int>(time(0)));

	createFunctions();
	loadStorage();
	loadRelevantTupleSet();
	parseCreationPolicy();
}


void Miner::createFunctions()
{
	FunctionFactory ff;
	for (size_t a = 0; a < mConfig.associationFunctions.size(); ++a)
	{
		std::cerr << "Building association function: " << mConfig.associationFunctions[a] << std::endl;
		mAssociationFunctions.push_back(ff.createAssociationFunction(mConfig.associationFunctions[a]));
		std::cerr << "Build association function: " << mAssociationFunctions.back()->reprezentation() << std::endl;
	}

	for (size_t v = 0; v < mConfig.vectorAssociationMeasures.size(); ++v)
	{
		std::cerr << "Building vector association measure: " << mConfig.vectorAssociationMeasures[v] << std::endl;
		mVectorAssociationMeasures.push_back(ff.createVectorAssociationMeasure(mConfig.vectorAssociationMeasures[v]));
		std::cerr << "Build vector association measure: " << mVectorAssociationMeasures.back()->reprezentation() << std::endl;
	}

	for (size_t g = 0; g < mConfig.aggregationFunctions.size(); ++g)
	{
		std::cerr << "Building aggregation function: " << mConfig.aggregationFunctions[g] << std::endl;
		mAggregationFunctions.push_back(ff.createAggregationFunction(mConfig.aggregationFunctions[g]));
		std::cerr << "Build aggregation function: " << mAggregationFunctions.back()->reprezentation() << std::endl;
	}

	for (size_t r = 0; r < mConfig.classifiers.size(); ++r)
	{
		std::cerr << "Building classifier: " << mConfig.classifiers[r] << std::endl;
		mClassifiers.push_back(ff.createClassifier(mConfig.classifiers[r]));
		std::cerr << "Build classifier: " << mClassifiers.back()->reprezentation() << std::endl;
	}

	if (!mConfig.classifierFeatureGenerator.empty())
	{
		std::cerr << "Building classifier features generator: " << mConfig.classifierFeatureGenerator << std::endl;
		mClassifierFeatureGenerator = ff.createVectorAssociationMeasure(mConfig.classifierFeatureGenerator);
		std::cerr << "Build classifier features generator: " << mClassifierFeatureGenerator->reprezentation() << std::endl;
	}

	if (!mConfig.classifierFeatureProcessor.empty())
	{
		std::cerr << "Building features processors: " << mConfig.classifierFeatureProcessor << std::endl;
		mFeaturesProcessors = ff.createScoreFunction(mConfig.classifierFeatureProcessor);
		std::cerr << "Build features processors: " << mFeaturesProcessors->reprezentation() << std::endl;
	}

	for (size_t q = 0; q < mConfig.qualityFunctions.size(); ++q)
	{
		std::cerr << "Building quality function: " << mConfig.qualityFunctions[q] << std::endl;
		mQualityFunctions.push_back(ff.createQualityFunction(mConfig.qualityFunctions[q]));
		std::cerr << "Build quality function: " << mQualityFunctions.back()->reprezentation() << std::endl;
	}

	if (!mConfig.statisticDataFilter.empty())
	{
		std::cerr << "Building statistic data filter: " << mConfig.statisticDataFilter << std::endl;
		mStatisticsFilter = ff.createFilterFunction(mConfig.statisticDataFilter);
		std::cerr << "Build statistic data filter: " << mStatisticsFilter->reprezentation() << std::endl;
	}

	if (!mConfig.extractionFilter.empty())
	{
		std::cerr << "Building extraction data filter: " << mConfig.extractionFilter << std::endl;
		mExtractionFilter = ff.createFilterFunction(mConfig.extractionFilter);
		std::cerr << "Build extraction data filter: " << mExtractionFilter->reprezentation() << std::endl;
	}
}


void Miner::loadStorage()
{
	mRankerData.reset(new RankerData(structure::io::DecodedTupleStorageIO().read(mConfig.inputStorageDirectory)));
}


void Miner::loadRelevantTupleSet()
{
	std::cerr << "Loading relevant tuple set..." << std::endl;

	RelevantLoader::ElementOrder elementOrder =
		mConfig.tupleElementsFixedOrder ?
			RelevantLoader::ElementOrder::FIXED :
			RelevantLoader::ElementOrder::FLEXIBLE;

	TupleStoragePtrS const& storage = mRankerData->getMatrixTupleStorage();

	std::cerr << "Loading relevant set using tuple id set..." << std::endl;
	mRankerData->setRelevantTupleIdSet(RelevantLoader().loadFromFile(
		mConfig.relevantTupleSetFilepath,
		*storage,
		elementOrder));
}


void Miner::parseCreationPolicy()
{
	std::cerr << "Parsing creation policy..." << std::endl;

	switch (mConfig.contingencyTableGeneratorPolicy)
	{
		case 'n':
		{
			mTableCreationPolicy = ContingencyTableCreationPolicy::JOIN_NONE;
		}
		break;
		case 's':
		{
			mTableCreationPolicy = ContingencyTableCreationPolicy::JOIN_SAME_SIZE_RELATIONS;
		}
		break;
		default:
		{
			XASSERT(false, "Unknown Contingency Table Generator table creation policy.");
		}
	}
}


void Miner::mine()
{
	typedef function::association::CrossValidator 	CrossValidator;
	typedef CrossValidator::FunctionSet				FunctionSet;
	typedef CrossValidator::ParameterSet			ParameterSet;
	typedef CrossValidator::DataSet					DataSet;
	typedef CrossValidator::KBestTupleListVector	KBestTupleListVector;

	std::cerr << "Mining..." << std::endl;

	FunctionSet functionSet;
	functionSet.statisticFilter					= mStatisticsFilter;
	functionSet.extractionFilter				= mExtractionFilter;
	functionSet.associationFunctionVector 		= mAssociationFunctions;
	functionSet.vectorAssociationMeasureVector	= mVectorAssociationMeasures;
	functionSet.classifierVector				= mClassifiers;
	functionSet.featureGenerator				= mClassifierFeatureGenerator;
	functionSet.featureProcessor				= mFeaturesProcessors;
	functionSet.vectorMeasureAggregatorVector	= mAggregationFunctions;

	ParameterSet parameterSet;
	parameterSet.foldCount	 			= mConfig.foldCount;
	parameterSet.rankSize 				= mConfig.kbestLengthForQualities;
	parameterSet.threadCount 			= mConfig.threadCount;
	parameterSet.tableCreationPolicy 	= mTableCreationPolicy;
	parameterSet.foldCreationPolicy		= CrossValidator::FoldsBuilder::Policy::WITHOUT_REPEATS;

	DataSet	dataSet;
	dataSet.relevantTupleIdSet 	= mRankerData->getRelevantTupleIdSet();
	dataSet.tupleStorage 		= mRankerData->getMatrixTupleStorage();

	CrossValidator cv(functionSet, parameterSet, dataSet);

	for (size_t round = 0; round < mConfig.repeatCount; ++round)
	{
		std::cerr << "Round " << (round + 1) << " started." << std::endl;
		cv.prepareRound();

		for (size_t fold = 0; fold < mConfig.foldCount; ++fold)
		{
			std::cerr << "Fold " << (fold + 1) << " started." << std::endl;

			utils::Time foldStart;
			CrossValidator::ResultPtrS cvres = cv.performForNextFold();
			utils::Time foldEnd;
			std::cerr << "Fold done in: " << (foldEnd - foldStart) << "s." << std::endl;

			std::cerr << "Writing kbest lists, computing qualities and writing results." << std::endl;
			utils::Time postProcessingStart;

			/* vector association functions */
			utils::parallelFor(0, functionSet.vectorAssociationMeasureVector.size(), [&](size_t pThread, size_t pJob)
			{
				cvres->foldResultForFunctions[pJob].setDescription(
					functionSet.vectorAssociationMeasureVector[pJob]->reprezentation());

				processKBest(
					*cvres,
					pJob,
					round,
					fold);
			}, std::min(parameterSet.threadCount, functionSet.vectorAssociationMeasureVector.size()));

			/* association functions */
			utils::parallelFor(0, functionSet.associationFunctionVector.size(), [&](size_t pThread, size_t pJob)
			{
				size_t resultIndex = pJob + functionSet.vectorAssociationMeasureVector.size();

				cvres->foldResultForFunctions[resultIndex].setDescription(
					functionSet.associationFunctionVector[pJob]->reprezentation());

				processKBest(
					*cvres,
					resultIndex,
					round,
					fold);
			}, std::min(parameterSet.threadCount, functionSet.associationFunctionVector.size()));

			/* classifiers */
			utils::parallelFor(0, functionSet.classifierVector.size(), [&](size_t pThread, size_t pJob)
			{
				size_t resultIndex = pJob + functionSet.vectorAssociationMeasureVector.size() +
					functionSet.associationFunctionVector.size();

				cvres->foldResultForFunctions[resultIndex].setDescription(
					functionSet.classifierVector[pJob]->reprezentation());

				processKBest(
					*cvres,
					resultIndex,
					round,
					fold);
			}, std::min(parameterSet.threadCount, functionSet.classifierVector.size()));

			utils::Time postProcessingEnd;
			std::cerr << "Writing kbests, computing qualities and writing results done in " << (postProcessingEnd - postProcessingStart) << "s." << std::endl;

			std::cerr << "Fold " << (fold + 1) << " ended." << std::endl;
		}

		std::cerr << "Round " << (round + 1) << " ended." << std::endl;
	}
}


void Miner::processKBest(
	CrossValidationResult const&	pCrossValidationResult,
	size_t 							pMeasureResultIndex,
	size_t 							pRoundNumber,
	size_t 							pFoldNumber) const
{
	std::stringstream kbstr;
	kbstr << mConfig.outputResultsDirectory << "/kbest." << pMeasureResultIndex << '.' << pRoundNumber << '.' << pFoldNumber << ".csv";
	std::string kbestFilepath = kbstr.str();

	if (mConfig.writeKBestFiles)
	{
		//std::cerr << "Writing '" << pCrossValidationResult.foldResultForFunctions[pMeasureIndex].getDescription() << "' to " << kbestFilepath << std::endl;
		structure::io::KBestTupleListIO().writeSome(
			pCrossValidationResult.foldResultForFunctions[pMeasureResultIndex],
			*mRankerData->getMatrixTupleStorage(),
			kbestFilepath,
			mConfig.writeKbestLength);
	}

	for (size_t q = 0; q < mQualityFunctions.size(); ++q)
	{
		std::stringstream qstr;
		qstr << mConfig.outputResultsDirectory << "/quality." << pMeasureResultIndex << '.' << pRoundNumber << '.' << pFoldNumber << '.' << q <<".csv";
		std::string qualityFilepath = qstr.str();

		//std::cerr << "\t" << q << ". Checking KBest '" << pCrossValidationResult.foldResultForFunctions[pMeasureIndex].getDescription()
		//	<< "' quality using: " << mQualityFunctions[q]->reprezentation() << std::endl;
		function::quality::QualityMatrix qualityResult =
			(*mQualityFunctions[q])(
				pCrossValidationResult.foldResultForFunctions[pMeasureResultIndex],
				*pCrossValidationResult.foldRelevantTupleIdSetExtraction,
				*mRankerData->getMatrixTupleStorage());

		std::stringstream qdesc;
		qdesc << pCrossValidationResult.foldRelevantTupleIdSetExtraction->sourceSize() << '\t'
			<< pCrossValidationResult.foldRelevantTupleIdSetExtraction->size() << '\t'
			<< pCrossValidationResult.foldResultForFunctions[pMeasureResultIndex].getDescription() << '\n' + mQualityFunctions[q]->reprezentation();
		qualityResult.setDescription(qdesc.str());

		std::fstream output(
			qualityFilepath,
			std::ios_base::out);
		EXCEPTION(output.is_open(), "Miner::processKBest(): Cannot open output file '" << qualityFilepath << "'.");
		utils::setStreamMaxDoublePrecision(output);
		qualityResult.writeToStream(output);
		output.close();
	}
}


	}
}
