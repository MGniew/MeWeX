
#include <iostream>

#include "../../utils/File.h"

#include "../../structure/builder/WcclOperatorLoader.h"
#include "../../structure/builder/ContingencyTableGeneratorBuilder.h"
#include "../../structure/builder/TupleFeatureStorageBuilder.h"
#include "../../structure/storage/TupleFeatureGenerator.h"

#include "../../function/FunctionFactory.h"

#include "../../function/dispersion/DispersionData.h"
#include "../../function/dispersion/Disperser.h"
#include "../../function/filter/Filtrator.h"
#include "../../function/association/Extractor.h"

#include "../../structure/io/KBestTupleListIO.h"
#include "../../structure/io/KBestTupleWithOrthsListIO.h"

#include "WebTool.h"


namespace program
{
	namespace web_tool
	{


void WebTool::start(Config const& pConfig)
{
	mConfig = pConfig;

	auto storage = parseCorpora();
	disperseStorage(storage);

	TupleIdVector ids;
	auto rankerData = buildRankerData(storage, ids);

	auto kbest = generateKBest(rankerData, ids);
	auto orths = extractOrths(rankerData, kbest);
	writeKBest(rankerData, kbest, orths);
}


auto WebTool::parseCorpora() const -> MatrixTupleStoragePtrS
{
	using namespace structure::builder;

	std::vector<std::string> corporas;
	utils::loadLinesFromFile(mConfig.corpusFilepathList, corporas);

	auto const& tagset = Corpus2::get_named_tagset(mConfig.tagsetName);
	auto wcclOperators = WcclOperatorLoader<Wccl::Bool>().
		loadOperators(tagset, mConfig.wcclRelationsFile, "");

	return CorporaParser().parse(corporas, wcclOperators, tagset, mConfig.readerName);
}


void WebTool::disperseStorage(MatrixTupleStoragePtrS const& pStorage) const
{
	if (!mConfig.dispersionFunction.empty())
	{
		using namespace structure::builder;
		using namespace function;
		using namespace function::dispersion;

		EXCEPTION(pStorage->getCorporaCount() >= 2, "WebTool::disperseStorage(): Corpora count must be greater or equal to 2.");

		auto dispersionFunction = FunctionFactory().
			createDispersionFunction(mConfig.dispersionFunction);

		std::shared_ptr<DispersionData> data(new DispersionData(
			pStorage, ContingencyTableGeneratorBuilder().build(pStorage, pStorage->retrieveTupleIdVector())));
		dispersionFunction->initialize(data);
		Disperser().dispersTuplesInPlace(dispersionFunction, pStorage, false, 0.0);
	}
}


auto WebTool::buildRankerData(MatrixTupleStoragePtrS const& pStorage,
		                      TupleIdVector& pExtractionIds) const -> RankerDataPtrS
{
	using namespace structure::builder;
	using namespace structure::storage;
	using namespace function;

	/* Collect data for building statistic informations */
	if (!mConfig.statisticDataFilter.empty())
	{
		auto filterFunction = FunctionFactory().createFilterFunction(mConfig.statisticDataFilter);
		filterFunction->initialize(pStorage);
		pExtractionIds = filter::Filtrator()(*pStorage, filterFunction);
	}
	else
	{
		pExtractionIds = pStorage->retrieveTupleIdVector();
	}

	/* Set ranker data: storage and contingency source */
	RankerDataPtrS rankerData(new RankerData(
		pStorage, ContingencyTableGeneratorBuilder().build(pStorage, pExtractionIds)));

	/* Obtain tuple ids which should be extracted */
	if (!mConfig.extractionDataFilter.empty())
	{
		auto filterFunction = FunctionFactory().createFilterFunction(mConfig.extractionDataFilter);
		filterFunction->initialize(pStorage);
		pExtractionIds = filter::Filtrator()(*pStorage, filterFunction);
	}
	else if (!mConfig.statisticDataFilter.empty())
	{
		pExtractionIds = pStorage->retrieveTupleIdVector();
	}

	/* Build features if it is necessary */
	if (!mConfig.features.empty())
	{
		auto featureFunctions = FunctionFactory().createVectorAssociationMeasure(mConfig.features);
		featureFunctions->initialize(rankerData);
		auto featureSource = TupleFeatureStorageBuilder().build(
			TupleFeatureGenerator(featureFunctions), pStorage, pExtractionIds, 1);
		rankerData->setTupleFeatureSource(featureSource);

		if (!mConfig.featuresPreprocessor.empty())
		{
			auto preproc = FunctionFactory().createScoreFunction(mConfig.featuresPreprocessor);
			preproc->scoreFeatures(*featureSource);
		}
	}

	return rankerData;
}


auto WebTool::generateKBest(RankerDataPtrS const& pRankerData,
                            TupleIdVector const& pExtractionIds) const -> KBestTupleList
{
	using namespace function;
	using namespace function::association;

	typedef Extractor::TupleIdVector 	TupleIdVector;
	typedef std::shared_ptr<RankerData>	RankerDataPtrS;

	auto const& storage = pRankerData->getMatrixTupleStorage();

	if (!mConfig.aggregator.empty())
	{
		auto vam = FunctionFactory().createVectorAssociationMeasure(mConfig.ranker);
		auto agg = FunctionFactory().createAggregationFunction(mConfig.aggregator);
		vam->initialize(pRankerData);
		auto res = Extractor().extract(vam, pExtractionIds, mConfig.rankLength, 1);
		auto kbest = agg->aggregateKBestVector(res, 1);
		kbest.setDescription(vam->reprezentation());
		return kbest;
	}
	else if (!mConfig.features.empty())
	{
		auto classifier = FunctionFactory().createClassifier(mConfig.ranker);
		classifier->initialize(pRankerData);
		auto kbest = Extractor().extract(classifier, pExtractionIds, mConfig.rankLength, 1);
		kbest.setDescription(classifier->reprezentation());
		return kbest;
	}
	else
	{
		auto assocFunc = FunctionFactory().createAssociationFunction(mConfig.ranker);
		assocFunc->initialize(pRankerData);
		auto kbest = Extractor().extract(assocFunc, pExtractionIds, mConfig.rankLength, 1);
		kbest.setDescription(assocFunc->reprezentation());
		return kbest;
	}
}


auto WebTool::extractOrths(RankerDataPtrS const& pRankerData,
						   KBestTupleList const& pKBestList) const -> OrthFormMap
{
	if (!mConfig.extractOrths)
	{
		return OrthFormMap();
	}

	using namespace structure::builder;

	std::vector<std::string> corporas;
	utils::loadLinesFromFile(mConfig.corpusFilepathList, corporas);

	auto const& tagset = Corpus2::get_named_tagset(mConfig.tagsetName);
	auto wcclOperators = WcclOperatorLoader<Wccl::Bool>().
		loadOperators(tagset, mConfig.wcclRelationsFile, "");

	OrthFormMap orthMap;
	for (size_t i = 0; i < pKBestList.size(); ++i)
	{
		orthMap.insert(std::make_pair(pKBestList[i].element, OrthExtractor::OrthFormSet()));
	}

	OrthExtractor().extract(orthMap, pRankerData->getMatrixTupleStorage(),
		corporas, wcclOperators, tagset, mConfig.readerName);

	return orthMap;
}


void WebTool::writeKBest(RankerDataPtrS const& 	pRanker,
						 KBestTupleList const& 	pKBestList,
						 OrthFormMap const&		pOrthMap) const
{
	using namespace structure::io;

	if (mConfig.extractOrths)
	{
		KBestTupleWithOrthsListIO().write(pKBestList, pOrthMap, *pRanker->getMatrixTupleStorage(), mConfig.kbestFilepath);
	}
	else
	{
		KBestTupleListIO().write(pKBestList, *pRanker->getMatrixTupleStorage(), mConfig.kbestFilepath);
	}
}


	}
}
