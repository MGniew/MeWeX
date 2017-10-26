
#include <iostream>
#include <fstream>

#include "../../utils/Time.h"
#include "../../utils/File.h"
#include "../../utils/Textual.h"

#include "../../structure/io/StreamingFileReader.h"
#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/ContingencyTableGeneratorIO.h"
#include "../../structure/io/ContingencyTableStorageIO.h"
#include "../../structure/io/KBestTupleListIO.h"
#include "../../structure/builder/TupleFeatureStorageBuilder.h"

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
		std::cerr << "Build association function: " << mAssociationFunctions.back()->reprezentation() << std::endl;
	}

	for (size_t avf = 0; avf < mConfig.vectorAssociationMeasures.size(); ++avf)
	{
		std::cerr << "Building vector association measure: " << mConfig.vectorAssociationMeasures[avf] << std::endl;
		mVectorAssociationMeasures.push_back(ff.createVectorAssociationMeasure(mConfig.vectorAssociationMeasures[avf]));
		std::cerr << "Build vector association measure: " << mVectorAssociationMeasures.back()->reprezentation() << std::endl;
	}

	for (size_t af = 0; af < mConfig.aggregationFunctions.size(); ++af)
	{
		std::cerr << "Building aggregation function: " << mConfig.aggregationFunctions[af] << std::endl;
		mAggregationFunctions.push_back(ff.createAggregationFunction(mConfig.aggregationFunctions[af]));
		std::cerr << "Build aggregation function: " << mAggregationFunctions.back()->reprezentation() << std::endl;
	}

	for (size_t af = 0; af < mConfig.classifiers.size(); ++af)
	{
		std::cerr << "Building classifier: " << mConfig.classifiers[af] << std::endl;
		mClassifiers.push_back(ff.createClassifier(mConfig.classifiers[af]));
		std::cerr << "Build classifier: " << mClassifiers.back()->reprezentation() << std::endl;
	}

	for (size_t af = 0; af < mConfig.features.size(); ++af)
	{
		std::cerr << "Building features: " << mConfig.features[af] << std::endl;
		mFeaturesVector.push_back(ff.createVectorAssociationMeasure(mConfig.features[af]));
		std::cerr << "Build features: " << mFeaturesVector.back()->reprezentation() << std::endl;
	}

	for (size_t af = 0; af < mConfig.preprocessors.size(); ++af)
	{
		std::cerr << "Building preprocessor: " << mConfig.preprocessors[af] << std::endl;
		mPreprocessors.push_back(ff.createScoreFunction(mConfig.preprocessors[af]));
		std::cerr << "Build preprocessor: " << mPreprocessors.back()->reprezentation() << std::endl;
	}

	for (size_t q = 0; q < mConfig.qualityFunctions.size(); ++q)
	{
		std::cerr << "Building quality function: " << mConfig.qualityFunctions[q] << std::endl;
		mQualityFunctions.push_back(ff.createQualityFunction(mConfig.qualityFunctions[q]));
		std::cerr << "Build quality function: " << mQualityFunctions.back()->reprezentation() << std::endl;
	}

	mRankerData.reset(new RankerData(nullptr));
	if (!mConfig.validStatisticTupleFilter.empty())
	{
		std::cerr << "Building statistic filter: " << mConfig.validStatisticTupleFilter << std::endl;
		mRankerData->setStatisticTupleFilter(ff.createFilterFunction(mConfig.validStatisticTupleFilter));
		std::cerr << "Build statistic filter: " << mRankerData->getStatisticTupleFilter()->reprezentation() << std::endl;
	}
}


void Digger::loadData()
{
	typedef structure::storage::ContingencyTableGenerator::TableCreationPolicy __Policy;

	TupleStoragePtrS const& storage = structure::io::DecodedTupleStorageIO().read(mConfig.inputDirectory);
	mRankerData->setMatrixTupleStorage(storage);

	{
		RelevantLoader::ElementOrder elementOrder =
			mConfig.tupleElementsFixedOrder ?
				RelevantLoader::ElementOrder::FIXED :
				RelevantLoader::ElementOrder::FLEXIBLE;

		if (!mConfig.extractionFilter.empty())
		{
			typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
			typedef function::filter::Filtrator					__Filtrator;


			std::cerr << "Building extraction filter: " << mConfig.extractionFilter << std::endl;
			__FilterPtrS extractionFilter = function::FunctionFactory().createFilterFunction(mConfig.extractionFilter);
			extractionFilter->initialize(storage);

			std::cerr << "Filtering using extraction filter: " << extractionFilter->reprezentation() << std::endl;
			mInterestedTupleIdVector = __Filtrator()(*storage, extractionFilter);

			if (!mConfig.qualityFunctions.empty())
			{
				std::cerr << "Loading relevant set using tuple id set..." << std::endl;
				mRankerData->setRelevantTupleIdSet(RelevantLoader().loadFromFile(
					mConfig.relevantSetFilepath,
					*storage,
					elementOrder,
					TupleStorage::TupleIdSet(
						mInterestedTupleIdVector.begin(), mInterestedTupleIdVector.end())));
			}
		}
		else
		{
			mInterestedTupleIdVector.reserve(storage->getDistinctTupleCount());
			for (auto iter = storage->beginTuples(); iter != storage->endTuples(); ++iter)
			{
				mInterestedTupleIdVector.push_back(storage->findTupleId(iter));
			}

			if (!mConfig.qualityFunctions.empty())
			{
				std::cerr << "Loading relevant set..." << std::endl;
				mRankerData->setRelevantTupleIdSet(RelevantLoader().loadFromFile(
					mConfig.relevantSetFilepath,
					*storage,
					elementOrder));
			}
		}
	}

	if (!mConfig.contingencyTableGeneratorFilepath.empty())
	{
		std::cerr << "Loading tuple frequency index..." << std::endl;
		auto contingencyTableGenerator = structure::io::ContingencyTableGeneratorIO().
			read(*storage, mConfig.contingencyTableGeneratorFilepath);
		switch (mConfig.indexTableCreationPolicy)
		{
			case 'n':
			{
				contingencyTableGenerator->setTableCreationPolicy(__Policy::JOIN_NONE);
			}
			break;
			case 's':
			{
				contingencyTableGenerator->setTableCreationPolicy(__Policy::JOIN_SAME_SIZE_RELATIONS);
			}
			break;
			default:
			{
				XASSERT(false, "Unknown Tuple Frequency Index table creation policy.");
			}
		}
		mRankerData->setContingencyTableSource(contingencyTableGenerator);
	}
	else if (!mConfig.contingencyTableStorageFilepath.empty())
	{
		std::cerr << "Loading contingency table..." << std::endl;
		mRankerData->setContingencyTableSource(structure::io::ContingencyTableStorageIO().
			read(*storage, mConfig.contingencyTableStorageFilepath));
	}
	else
	{
		std::cerr << "No contingency table source not set." << std::endl;
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
		mAssociationFunctions[af]->initialize(mRankerData);
	}

	for (size_t avf = 0; avf < mVectorAssociationMeasures.size(); ++avf)
	{
		mVectorAssociationMeasures[avf]->initialize(mRankerData);
	}

	//std::cerr << mClassifiers.size() << ' ' << mFeaturesVector.size() << std::endl;
	for (size_t c = 0; c < mClassifiers.size(); ++c)
	{
		mClassifiers[c]->initialize(mRankerData);
		mFeaturesVector[c]->initialize(mRankerData);
	}
}


void Digger::dig() const
{
	Extractor extractor;

	OrthFormMap orths;
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

	digClassifiers(extractor, orths, extractOrths);

	if (extractOrths)
	{
		std::cerr << "Extracting orths..." << std::endl;
		extractAndWriteOrths(orths);
	}
}


void Digger::digSingleComponent(
	Extractor& 		pExtractor,
	OrthFormMap&	pOrthMap,
	bool			pExtractOrths) const
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
				pOrthMap.insert(std::make_pair(kbestResult[i].element, OrthFormSet()));
			}
		}
	}
}


void Digger::digSingleComponentSpeededUp(
	Extractor& 		pExtractor,
	OrthFormMap&	pOrthMap,
	bool			pExtractOrths) const
{
	function::association::VectorAssociationMeasure::AssociationMeasurePtrSVector components(
		mAssociationFunctions.begin(), mAssociationFunctions.end());

	function::FunctionFactory::VectorAssociationMeasurePtrS functions(
		new function::association::VectorAssociationMeasure(components));
	functions->initialize(mRankerData);

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
			pOrthMap.insert(std::make_pair(kbestResultVector[i][j].element, OrthFormSet()));
		}
	}
}


void Digger::digMultiComponent(
	Extractor& 		pExtractor,
	OrthFormMap&	pOrthMap,
	bool			pExtractOrths) const
{
	for (size_t avf = 0; avf < mVectorAssociationMeasures.size(); ++avf)
	{
		std::string associationFunctionReprezentation = mVectorAssociationMeasures[avf]->reprezentation();

		std::cerr << "Digging using: " << associationFunctionReprezentation << std::endl;
		utils::Time diggingStart;

		KBestTupleListVector kbestResultVector = pExtractor.extract(
			mVectorAssociationMeasures[avf],
			mInterestedTupleIdVector,
			mConfig.kbestLength,
			mConfig.threadCount);

		KBestTupleList kbestResult = (*mAggregationFunctions[avf])(kbestResultVector, mConfig.threadCount);
		kbestResult.setDescription(associationFunctionReprezentation);

		utils::Time diggingEnd;
		std::cerr << "Digging time: " << (diggingEnd - diggingStart) << "sec" << std::endl;

		writeKBest(kbestResult, avf + mAssociationFunctions.size());
		computeAndWriteQualites(kbestResult, avf + mAssociationFunctions.size(), associationFunctionReprezentation);

		if (pExtractOrths)
		{
			for (size_t i = 0; i < kbestResult.size(); ++i)
			{
				pOrthMap.insert(std::make_pair(kbestResult[i].element, OrthFormSet()));
			}
		}
	}
}


void Digger::digClassifiers(
	Extractor& 		pExtractor,
	OrthFormMap&	pOrthMap,
	bool			pExtractOrths) const
{
	auto tupleIds = mRankerData->getMatrixTupleStorage()->retrieveTupleIdVector();

	for (size_t c = 0; c < mClassifiers.size(); ++c)
	{
		std::string classifierReprezentation = mClassifiers[c]->reprezentation();

		std::cerr << "Digging using: " << classifierReprezentation << std::endl;
		utils::Time diggingStart;

		// do features
		auto feats = structure::builder::TupleFeatureStorageBuilder().build(
			structure::storage::TupleFeatureGenerator(mFeaturesVector[c]),
			mRankerData->getMatrixTupleStorage(),
			tupleIds,
			mConfig.threadCount);
		mPreprocessors[c]->scoreFeatures(*feats);
		mRankerData->setTupleFeatureSource(feats);

		KBestTupleList kbestResult = pExtractor.extract(
			mClassifiers[c],
			mInterestedTupleIdVector,
			mConfig.kbestLength,
			mConfig.threadCount);

		kbestResult.setDescription(classifierReprezentation);

		utils::Time diggingEnd;
		std::cerr << "Digging time: " << (diggingEnd - diggingStart) << "sec" << std::endl;

		writeKBest(kbestResult, c + mVectorAssociationMeasures.size() + mAssociationFunctions.size());
		computeAndWriteQualites(kbestResult, c + mVectorAssociationMeasures.size() + mAssociationFunctions.size(), classifierReprezentation);

		if (pExtractOrths)
		{
			for (size_t i = 0; i < kbestResult.size(); ++i)
			{
				pOrthMap.insert(std::make_pair(kbestResult[i].element, OrthFormSet()));
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
		*mRankerData->getMatrixTupleStorage(),
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
			(*mQualityFunctions[q])(pKBest, *mRankerData->getRelevantTupleIdSet(), *mRankerData->getMatrixTupleStorage());
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


void Digger::extractAndWriteOrths(OrthFormMap& pOrthFormMap) const
{
	typedef structure::builder::OrthExtractor OrthExtractor;

	OrthExtractor().extract(pOrthFormMap, mRankerData->getMatrixTupleStorage(),
		mCorporaVector, mWcclOperatorDataVector, getTagset(), mConfig.readerName);

	std::fstream orthsOutputFile(mConfig.outputDirectory + "/orths.csv", std::ios_base::out);
	EXCEPTION(orthsOutputFile.is_open(), "Digger::dig(): Cannot open output file '" << mConfig.outputDirectory << "/orths.csv'.");

	for (auto iter = pOrthFormMap.begin(); iter != pOrthFormMap.end(); ++iter)
	{
		orthsOutputFile << mRankerData->getMatrixTupleStorage()->createTupleReprezentation(iter->first) << std::endl;
		for (auto orth = iter->second.begin(); orth != iter->second.end(); ++orth)
		{
			orthsOutputFile << '\t' << orth->frequency << ' ' << orth->form << std::endl;
		}
	}
}


Corpus2::Tagset const& Digger::getTagset() const
{
	return Corpus2::get_named_tagset(mConfig.tagsetName);
}


	}
}
