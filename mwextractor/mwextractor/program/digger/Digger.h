
#pragma once

#include <vector>

#include "Config.h"

#include "../../structure/io/RelevantTupleSetLoader.h"

#include "../../structure/builder/WcclOperatorLoader.h"
#include "../../structure/builder/OrthExtractor.h"

#include "../../function/FunctionFactory.h"
#include "../../function/association/Extractor.h"
#include "../../machine_learning/Classifier.h"
#include "../../function/score/ScoreFunction.h"
#include "../../function/filter/Filter.h"


namespace program
{
	namespace digger
	{


class Digger
{
private:
	typedef std::vector<function::FunctionFactory::AssociationFunctionPtrS>			AssociationFunctionPtrSVector;
	typedef std::vector<function::FunctionFactory::VectorAssociationMeasurePtrS>	VectorAssociationMeasurePtrSVector;
	typedef std::vector<function::FunctionFactory::QualityFunctionPtrS>				QualityFunctionPtrSVector;
	typedef std::vector<function::FunctionFactory::AggregationFunctionPtrS>			AggregationFunctionPtrSVector;

	typedef std::shared_ptr<machine_learning::Classifier>							ClassifierPtrS;
	typedef std::vector<ClassifierPtrS>												ClassifierPtrSVector;
	typedef std::shared_ptr<function::score::ScoreFunction>							ScoreFunctionPtrS;
	typedef std::vector<ScoreFunctionPtrS>											ScoreFunctionPtrSVector;

	typedef function::association::Extractor										Extractor;
	typedef Extractor::KBestTupleList												KBestTupleList;
	typedef Extractor::KBestTupleListVector											KBestTupleListVector;

	typedef structure::storage::MatrixTupleStorage									TupleStorage;
	typedef std::shared_ptr<TupleStorage>											TupleStoragePtrS;
	typedef TupleStorage::TupleIdVector												TupleIdVector;
	typedef function::association::RankerData										RankerData;
	typedef std::shared_ptr<RankerData>												RankerDataPtrS;

	typedef structure::io::RelevantTupleSetLoader									RelevantLoader;
	typedef RelevantLoader::RelevantTupleIdSet										RelevantTupleIdSet;


	typedef structure::builder::WcclOperatorLoader<Wccl::Bool>						WcclOperatorLoader;
	typedef WcclOperatorLoader::WcclOperatorDataVector								WcclOperatorDataVector;

	typedef structure::builder::OrthExtractor::OrthForm 							OrthForm;
	typedef structure::builder::OrthExtractor::OrthFormSet							OrthFormSet;
	typedef structure::builder::OrthExtractor::OrthFormMap							OrthFormMap;

public:
	void dig(Config const& pConfig);

private:
	void createFunctions();
	void loadData();
	void initialize();

	void dig() const;

	void digSingleComponent(
		Extractor& 		pExtractor,
		OrthFormMap&	pOrthMap,
		bool			pExtractOrths) const;

	void digSingleComponentSpeededUp(
		Extractor& 		pExtractor,
		OrthFormMap&	pOrthMap,
		bool			pExtractOrths) const;

	void digMultiComponent(
		Extractor& 		pExtractor,
		OrthFormMap&	pOrthMap,
		bool			pExtractOrths) const;

	void digClassifiers(
		Extractor& 		pExtractor,
		OrthFormMap&	pOrthMap,
		bool			pExtractOrths) const;

	void writeKBest(
		KBestTupleList const& 	pKBest,
		size_t					pAssociationFunctionIndex) const;

	void computeAndWriteQualites(
		KBestTupleList const& 	pKBest,
		size_t					pAssociationFunctionIndex,
		std::string const&		pAssociationFunctionReprezentation) const;

	void extractAndWriteOrths(OrthFormMap& pOrthMap) const;

	Corpus2::Tagset const& getTagset() const;

private:
	Config mConfig;

	/* Functions */
	AssociationFunctionPtrSVector 		mAssociationFunctions;
	VectorAssociationMeasurePtrSVector	mVectorAssociationMeasures;
	AggregationFunctionPtrSVector		mAggregationFunctions;
	QualityFunctionPtrSVector 			mQualityFunctions;

	VectorAssociationMeasurePtrSVector	mFeaturesVector;
	ClassifierPtrSVector				mClassifiers;
	ScoreFunctionPtrSVector				mPreprocessors;

	/* Data */
	RankerDataPtrS						mRankerData;
	TupleIdVector						mInterestedTupleIdVector;

	WcclOperatorDataVector				mWcclOperatorDataVector;
	std::vector<std::string>			mCorporaVector;
};


	}
}
