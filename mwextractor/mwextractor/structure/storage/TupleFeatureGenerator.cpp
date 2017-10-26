
#include "TupleFeatureGenerator.h"


namespace structure
{
	namespace storage
	{


TupleFeatureGenerator::TupleFeatureGenerator(VectorAssociationMeasurePtrS const& pVectorAssociationMeasure)
:
	mVectorAssociationMeasure(pVectorAssociationMeasure)
{

}


auto TupleFeatureGenerator::getVectorAssociationMeasure() const -> VectorAssociationMeasurePtrS const&
{
	return mVectorAssociationMeasure;
}


auto TupleFeatureGenerator::getVectorAssociationMeasure() -> VectorAssociationMeasurePtrS&
{
	return mVectorAssociationMeasure;
}


size_t TupleFeatureGenerator::getFeatureCount() const
{
	return mVectorAssociationMeasure->size();
}


Instance TupleFeatureGenerator::constructInstance(
	TupleId 						pTupleId,
	MatrixTupleStoragePtrS const&	pTupleStorage) const
{
	XASSERT(
		mVectorAssociationMeasure->hasRankerData() &&
		mVectorAssociationMeasure->getRankerData()->hasRelevantTupleIdSet() &&
		mVectorAssociationMeasure->getRankerData()->hasMatrixTupleStorage(),
		"TupleFeatureGenerator::constructInstance(): Relevant tuple id set, matrix tuple storage or whole computation data not set.");

	size_t instanceClass = mVectorAssociationMeasure->getRankerData()->checkClass(pTupleId);
	Instance instance = Instance(mVectorAssociationMeasure->rank(pTupleId), instanceClass);
	XASSERT(
		instance.getFeatureVector().size() == mVectorAssociationMeasure->size() && instance.getFeatureVector().size() != 0,
		"TupleFeatureGenerator::constructInstance(): Instance construction failed for '" <<
			mVectorAssociationMeasure->getRankerData()->getMatrixTupleStorage()->createTupleReprezentation(pTupleId) << "'");
	return instance;
}


Instance TupleFeatureGenerator::constructInstance(
	TupleT const& 					pTupleT,
	MatrixTupleStoragePtrS const&	pTupleStorage) const
{
	TupleId tid = pTupleStorage->findTupleIdSilent(pTupleT);
	XASSERT(tid != nullptr, "TupleFeatureGenerator::constructInstance(): Cannot construct instance for " << pTupleT << ".");
	return constructInstance(tid, pTupleStorage);
}


	}
}
