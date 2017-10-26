
#pragma once

#include <vector>

#include "Config.h"

#include "../../structure/io/TupleFrequencyIndexIO.h"
#include "../../structure/io/ContingencyTableIO.h"
#include "../../function/FunctionFactory.h"
#include "../../function/association/Extractor.h"
#include "../../structure/builder/WcclOperatorLoader.h"
#include "../../structure/builder/OrthExtractor.h"
#include "../../structure/io/RelevantTupleSetLoader.h"


namespace program
{
	namespace digger
	{


class Digger
{
private:
	typedef std::vector<function::FunctionFactory::AssociationFunctionPtrS>			AssociationFunctionPtrSVector;
	typedef std::vector<function::FunctionFactory::AssociationVectorFunctionPtrS>	AssociationVectorFunctionPtrSVector;
	typedef std::vector<function::FunctionFactory::QualityFunctionPtrS>				QualityFunctionPtrSVector;
	typedef std::vector<function::FunctionFactory::AggregationFunctionPtrS>			AggregationFunctionPtrSVector;

	typedef function::association::Extractor										Extractor;
	typedef Extractor::KBestTupleList												KBestTupleList;
	typedef Extractor::KBestTupleListVector											KBestTupleListVector;

	typedef structure::storage::MatrixTupleStorage									TupleStorage;
	typedef std::shared_ptr<TupleStorage>											TupleStoragePtrS;
	typedef structure::io::ContingencyTableIO::ContingencyTableStoragePtrS			ContingencyTableStoragePtrS;
	typedef structure::io::TupleFrequencyIndexIO::TupleFrequencyIndexPtrS			TupleFrequencyIndexPtrS;
	typedef TupleStorage::TupleIdVector												TupleIdVector;

	typedef structure::io::RelevantTupleSetLoader									RelevantLoader;
	typedef RelevantLoader::RelevantTupleIdSet										RelevantTupleIdSet;


	typedef structure::builder::WcclOperatorLoader<Wccl::Bool>						WcclOperatorLoader;
	typedef WcclOperatorLoader::WcclOperatorDataVector								WcclOperatorDataVector;
	typedef structure::builder::OrthExtractor::OrthMap								OrthMap;
	typedef structure::builder::OrthExtractor::OrthMapElement 						OrthMapElement;

public:
	void dig(Config const& pConfig);

private:
	void createFunctions();
	void loadData();
	void initialize();

	void dig() const;

	void digSingleComponent(
		Extractor& 	pExtractor,
		OrthMap&	pOrthMap,
		bool		pExtractOrths) const;

	void digSingleComponentSpeededUp(
		Extractor& 	pExtractor,
		OrthMap&	pOrthMap,
		bool		pExtractOrths) const;

	void digMultiComponent(
		Extractor& 	pExtractor,
		OrthMap&	pOrthMap,
		bool		pExtractOrths) const;

	void writeKBest(
		KBestTupleList const& 	pKBest,
		size_t					pAssociationFunctionIndex) const;

	void computeAndWriteQualites(
		KBestTupleList const& 	pKBest,
		size_t					pAssociationFunctionIndex,
		std::string const&		pAssociationFunctionReprezentation) const;

	void extractAndWriteOrths(OrthMap& pOrthMap) const;

	Corpus2::Tagset const& getTagset() const;

private:
	Config mConfig;

	/* Functions */
	AssociationFunctionPtrSVector 		mAssociationFunctions;
	AssociationVectorFunctionPtrSVector	mAssociationVectorFunctions;
	AggregationFunctionPtrSVector		mAggregationFunctions;
	QualityFunctionPtrSVector 			mQualityFunctions;

	/* Data */
	RelevantTupleIdSet 					mRelevantTupleIdSet;
	TupleStoragePtrS 					mTupleStorage;
	ContingencyTableStoragePtrS 		mContingencyTable;
	TupleFrequencyIndexPtrS				mTupleFrequencyIndex;
	TupleIdVector						mInterestedTupleIdVector;

	WcclOperatorDataVector				mWcclOperatorDataVector;
	std::vector<std::string>			mCorporaVector;
};


	}
}
