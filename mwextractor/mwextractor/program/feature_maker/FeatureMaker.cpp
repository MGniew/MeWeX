
#include <iostream>
#include <fstream>
#include <sstream>

#include "../../utils/Time.h"
#include "../../utils/File.h"
#include "../../utils/Textual.h"

#include "../../structure/io/StreamingFileReader.h"
#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/ContingencyTableGeneratorIO.h"
#include "../../structure/io/ContingencyTableStorageIO.h"
#include "../../structure/io/RelevantTupleSetLoader.h"
#include "../../structure/io/KBestTupleListIO.h"
#include "../../structure/io/ArffTupleFeatureStorageIO.h"

#include "../../structure/storage/TupleFeatureStorage.h"

#include "../../structure/builder/TupleFeatureStorageBuilder.h"

#include "../../function/filter/Filtrator.h"

#include "FeatureMaker.h"


namespace program
{
	namespace feature_maker
	{


void FeatureMaker::make(Config const& pConfig)
{
	mConfig = pConfig;

	createFunctions();
	loadData();
	initialize();
	make();

	std::cerr << "Done" << std::endl;
}


void FeatureMaker::createFunctions()
{
	function::FunctionFactory ff;

	std::cerr << "Building feature generator: " << mConfig.featureGenerator << std::endl;
	mFeatureGenerator.reset(new TupleFeatureGenerator(ff.createVectorAssociationMeasure(mConfig.featureGenerator)));
	std::cerr << "Build feature generator: " << mFeatureGenerator->getVectorAssociationMeasure()->reprezentation() << std::endl;

	if (!mConfig.scoreFunction.empty())
	{
		std::cerr << "Building score function: " << mConfig.scoreFunction << std::endl;
		mScoreFunction = ff.createScoreFunction(mConfig.scoreFunction);
		std::cerr << "Build score function: " << mScoreFunction->reprezentation() << std::endl;
	}

	mRankerData.reset(new RankerData(nullptr));
	if (!mConfig.validStatisticTupleFilter.empty())
	{
		std::cerr << "Building statistic filter: " << mConfig.validStatisticTupleFilter << std::endl;
		mRankerData->setStatisticTupleFilter(ff.createFilterFunction(mConfig.validStatisticTupleFilter));
		std::cerr << "Build statistic filter: " << mRankerData->getStatisticTupleFilter()->reprezentation() << std::endl;
	}
}


void FeatureMaker::loadData()
{
	typedef structure::storage::ContingencyTableGenerator::TableCreationPolicy 	__Policy;
	typedef TupleStorage::RelationIdSet											__RelationIdSet;

	TupleStoragePtrS storage = structure::io::DecodedTupleStorageIO().read(mConfig.inputDirectory);
	mRankerData->setMatrixTupleStorage(storage);

	{
		typedef structure::io::RelevantTupleSetLoader 	RelevantLoader;
		typedef RelevantLoader::ElementOrder 			__ElemOrder;

		__ElemOrder elementOrder =
			mConfig.tupleElementsFixedOrder ?
				__ElemOrder::FIXED :
				__ElemOrder::FLEXIBLE;

		if (!mConfig.extractionFilter.empty())
		{
			typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
			typedef function::filter::Filtrator					__Filtrator;

			std::cerr << "Building filter: " << mConfig.extractionFilter << std::endl;
			__FilterPtrS extractionFilter = function::FunctionFactory().createFilterFunction(mConfig.extractionFilter);
			extractionFilter->initialize(storage);

			std::cerr << "Filtering using: " << extractionFilter->reprezentation() << std::endl;
			mInterestedTupleIdVector = __Filtrator()(*storage, extractionFilter);

			std::cerr << "Loading relevant set using tuple id set..." << std::endl;
			mRankerData->setRelevantTupleIdSet(RelevantLoader().loadFromFile(
				mConfig.fileWithRelevantSet,
				*storage,
				elementOrder,
				TupleStorage::TupleIdSet(
					mInterestedTupleIdVector.begin(), mInterestedTupleIdVector.end())));
		}
		else
		{
			mInterestedTupleIdVector.reserve(storage->getDistinctTupleCount());
			for (auto iter = storage->beginTuples(); iter != storage->endTuples(); ++iter)
			{
				mInterestedTupleIdVector.push_back(storage->findTupleId(iter));
			}

			std::cerr << "Loading relevant set..." << std::endl;
			mRankerData->setRelevantTupleIdSet(RelevantLoader().loadFromFile(
				mConfig.fileWithRelevantSet,
				*storage,
				elementOrder));
		}
	}

	if (!mConfig.fileWithTupleFrequencyIndex.empty())
	{
		std::cerr << "Loading tuple frequency index..." << std::endl;
		auto generator = structure::io::ContingencyTableGeneratorIO().
			read(*storage, mConfig.fileWithTupleFrequencyIndex);
		switch (mConfig.indexTableCreationPolicy)
		{
			case 'n':
			{
				generator->setTableCreationPolicy(__Policy::JOIN_NONE);
			}
			break;
			case 's':
			{
				generator->setTableCreationPolicy(__Policy::JOIN_SAME_SIZE_RELATIONS);
			}
			break;
			default:
			{
				XASSERT(false, "Unknown Tuple Frequency Index table creation policy.");
			}
		}
		mRankerData->setContingencyTableSource(generator);
	}
	else if (!mConfig.fileWithContingencyTable.empty())
	{
		std::cerr << "Loading contingency table..." << std::endl;
		mRankerData->setContingencyTableSource(structure::io::ContingencyTableStorageIO().
			read(*storage, mConfig.fileWithContingencyTable));
	}
	else
	{
		std::cerr << "Contingency table neither tuple frequency index file set." << std::endl;
	}
}


void FeatureMaker::initialize()
{
	mFeatureGenerator->getVectorAssociationMeasure()->initialize(mRankerData);
}


void FeatureMaker::make() const
{
	typedef TupleStorage::TupleId 					__TupleId;
	typedef Extractor::KBestTupleList				__KBestTupleList;
	typedef structure::storage::TupleFeatureStorage	__TFS;
	typedef std::shared_ptr<__TFS>					__TFSPtrS;

	Extractor extractor;

	utils::Time timerStart;

	std::cerr << "Building features..." << std::endl;
	__TFSPtrS dataSet = structure::builder::TupleFeatureStorageBuilder().build(
		*mFeatureGenerator,
		mRankerData->getMatrixTupleStorage(),
		mInterestedTupleIdVector,
		mConfig.threadCount);
	dataSet->setRelationName("FeatureMakerResult");

	{
		dataSet->getHeaderNoteVector().reserve(3);
		std::stringstream str1;
		str1 << "feature generator used: " << mFeatureGenerator->getVectorAssociationMeasure()->reprezentation();
		dataSet->getHeaderNoteVector().push_back(str1.str());
	}

	if (mScoreFunction != nullptr)
	{
		mScoreFunction->buildForFeatures(*dataSet);
		mScoreFunction->scoreFeatures(*dataSet);
	}

	utils::Time timerEnd;
	std::cerr << "Feature making time: " << (timerEnd - timerStart) << "sec" << std::endl;

	structure::io::ArffTupleFeatureStorageIO().writeToFile(
		mConfig.outputFile,
		dataSet,
		mRankerData->getMatrixTupleStorage());
}


	}
}
