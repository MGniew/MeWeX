
#pragma once

#include "Config.h"

#include "../../function/FunctionFactory.h"
#include "../../function/association/Extractor.h"

#include "../../structure/storage/TupleFeatureGenerator.h"


namespace program
{
	namespace feature_maker
	{


class FeatureMaker
{
private:
	typedef function::FunctionFactory::AssociationFunctionPtrS		AssociationFunctionPtrS;
	typedef function::FunctionFactory::VectorAssociationMeasurePtrS	VectorAssociationMeasurePtrS;
	typedef function::FunctionFactory::AggregationFunctionPtrS		AggregationFunctionPtrS;
	typedef function::FunctionFactory::ScoreFunctionPtrS			ScoreFunctionPtrS;

	typedef structure::storage::MatrixTupleStorage					TupleStorage;
	typedef std::shared_ptr<TupleStorage>							TupleStoragePtrS;
	typedef function::association::RankerData						RankerData;
	typedef std::shared_ptr<RankerData>								RankerDataPtrS;
	typedef structure::storage::TupleFeatureGenerator				TupleFeatureGenerator;
	typedef std::shared_ptr<TupleFeatureGenerator>					TupleFeatureGeneratorPtrS;

	typedef TupleStorage::TupleId									TupleId;
	typedef TupleStorage::TupleIdVector								TupleIdVector;

	typedef function::association::Extractor						Extractor;
	typedef structure::storage::Instance							Instance;

public:
	void make(Config const& pConfig);

private:
	void createFunctions();
	void loadData();
	void initialize();

	void make() const;

private:
	Config mConfig;

	/* Functions */
	TupleFeatureGeneratorPtrS	mFeatureGenerator;
	ScoreFunctionPtrS			mScoreFunction;

	/* Data */
	TupleStoragePtrS 	mTupleStorage;
	RankerDataPtrS		mRankerData;
	TupleIdVector		mInterestedTupleIdVector;
};


	}
}
