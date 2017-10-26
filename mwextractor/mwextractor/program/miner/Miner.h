
#pragma once

#include <vector>

#include "Config.h"

#include "../../function/FunctionFactory.h"

#include "../../function/association/Extractor.h"
#include "../../function/association/CrossValidator.h"

#include "../../structure/storage/TupleFeatureGenerator.h"
#include "../../structure/storage/ContingencyTableGenerator.h"

#include "../../structure/io/RelevantTupleSetLoader.h"


namespace program
{
	namespace miner
	{


class Miner
{
private:
	typedef function::FunctionFactory						FunctionFactory;

	typedef FunctionFactory::FilterFunctionPtrS				FilterFunctionPtrS;
	typedef FunctionFactory::AssociationFunctionPtrS		AssociationFunctionPtrS;
	typedef FunctionFactory::VectorAssociationMeasurePtrS	VectorAssociationMeasurePtrS;
	typedef FunctionFactory::AggregationFunctionPtrS		AggregationFunctionPtrS;
	typedef FunctionFactory::ClassifierPtrS					ClassifierPtrS;
	typedef FunctionFactory::ScoreFunctionPtrS				ScoreFunctionPtrS;
	typedef FunctionFactory::QualityFunctionPtrS			QualityFunctionPtrS;

	typedef std::vector<AssociationFunctionPtrS>			AssociationFunctionPtrSVector;
	typedef std::vector<VectorAssociationMeasurePtrS>		VectorAssociationMeasurePtrSVector;
	typedef std::vector<AggregationFunctionPtrS>			AggregationFunctionPtrSVector;
	typedef std::vector<ClassifierPtrS>						ClassifierPtrSVector;
	typedef std::vector<ScoreFunctionPtrS>					ScoreFunctionPtrSVector;
	typedef std::vector<QualityFunctionPtrS>				QualityFunctionPtrSVector;

	typedef function::association::Extractor				Extractor;
	typedef function::association::CrossValidator::Result	CrossValidationResult;
	typedef Extractor::KBestTupleList						KBestTupleList;
	typedef Extractor::KBestTupleListVector					KBestTupleListVector;

	typedef function::association::RankerData				RankerData;
	typedef std::shared_ptr<RankerData>						RankerDataPtrS;
	typedef structure::storage::MatrixTupleStorage			TupleStorage;
	typedef std::shared_ptr<TupleStorage>					TupleStoragePtrS;
	typedef TupleStorage::TupleIdVector						TupleIdVector;
	typedef TupleStorage::TupleIdSet						TupleIdSet;

	typedef structure::io::RelevantTupleSetLoader			RelevantLoader;
	typedef RelevantLoader::RelevantTupleIdSetPtrS			RelevantTupleIdSetPtrS;

	typedef structure::storage::TupleFeatureGenerator		TupleFeatureGenerator;
	typedef std::shared_ptr<TupleFeatureGenerator>			TupleFeatureGeneratorPtrS;

	typedef structure::storage::ContingencyTableGenerator	ContingencyTableGenerator;
	typedef ContingencyTableGenerator::TableCreationPolicy	ContingencyTableCreationPolicy;


public:
	void build(Config const& pConfig);
	void mine();


private:
	/* building functions */
	void createFunctions();
	void loadStorage();
	void loadRelevantTupleSet();
	void parseCreationPolicy();

	std::string constructFilename(
		size_t pMeasureIndex,
		size_t pRoundNumber,
		size_t pFoldNumber) const;

	void processKBest(
		CrossValidationResult const&	pCrossValidationResult,
		size_t 							pMeasureIndex,
		size_t 							pRoundNumber,
		size_t 							pFoldNumber) const;

private:
	Config mConfig;

	/* Functions */
	FilterFunctionPtrS					mStatisticsFilter;
	FilterFunctionPtrS					mExtractionFilter;
	AssociationFunctionPtrSVector 		mAssociationFunctions;
	VectorAssociationMeasurePtrSVector	mVectorAssociationMeasures;
	AggregationFunctionPtrSVector		mAggregationFunctions;
	ClassifierPtrSVector				mClassifiers;
	VectorAssociationMeasurePtrS		mClassifierFeatureGenerator;
	ScoreFunctionPtrS					mFeaturesProcessors;
	QualityFunctionPtrSVector 			mQualityFunctions;

	/* Data */
	RankerDataPtrS					mRankerData;
	ContingencyTableCreationPolicy	mTableCreationPolicy;
	TupleIdVector					mStatisticDataTuples;
	TupleIdSet						mExtractionTuples;
};


	}
}
