
#include "../../utils/Debug.h"

#include "RankerData.h"


namespace function
{
	namespace association
	{


RankerData::RankerData(
	MatrixTupleStoragePtrS const& 		pMatrixTupleStorage,
	ContingencyTableSourcePtrS const&	pContingencyTableSource,
	TupleFeatureSourcePtrS const&		pTupleFeatureSource,
	RelevantTupleIdSetPtrS const&		pRelevantTupleIdSet,
	FilterPtrS const&					pStatisticTupleFilter)
:
	mMatrixTupleStorage(pMatrixTupleStorage),
	mContingencyTableSource(pContingencyTableSource),
	mTupleFeatureSource(pTupleFeatureSource),
	mRelevantTupleIdSet(pRelevantTupleIdSet),
	mStatisticTupleFilter(pStatisticTupleFilter)
{

}


auto RankerData::getMatrixTupleStorage() const -> MatrixTupleStoragePtrS const&
{
	return mMatrixTupleStorage;
}


auto RankerData::getContingencyTableSource() const -> ContingencyTableSourcePtrS const&
{
	return mContingencyTableSource;
}


auto RankerData::getTupleFeatureSource() const -> TupleFeatureSourcePtrS const&
{
	return mTupleFeatureSource;
}


auto RankerData::getRelevantTupleIdSet() const -> RelevantTupleIdSetPtrS const&
{
	return mRelevantTupleIdSet;
}


auto RankerData::getStatisticTupleFilter() const -> FilterPtrS const&
{
	return mStatisticTupleFilter;
}


bool RankerData::hasMatrixTupleStorage() const
{
	return getMatrixTupleStorage() != nullptr;
}


bool RankerData::hasContingencyTableSource() const
{
	return getContingencyTableSource() != nullptr;
}


bool RankerData::hasTupleFeatureSource() const
{
	return getTupleFeatureSource() != nullptr;
}


bool RankerData::hasRelevantTupleIdSet() const
{
	return getRelevantTupleIdSet() != nullptr;
}


bool RankerData::hasStatisticTupleFilter() const
{
	return mStatisticTupleFilter != nullptr;
}


bool RankerData::isTupleIdValid(TupleId pTupleId) const
{
	return !hasStatisticTupleFilter() || getStatisticTupleFilter()->meets(pTupleId);
}


void RankerData::setMatrixTupleStorage(MatrixTupleStoragePtrS const& pMatrixTupleStorage)
{
	mMatrixTupleStorage = pMatrixTupleStorage;
}


void RankerData::setContingencyTableSource(ContingencyTableSourcePtrS const& pContingencyTableSource)
{
	mContingencyTableSource = pContingencyTableSource;
}


void RankerData::setTupleFeatureSource(TupleFeatureSourcePtrS const& pTupleFeatureSource)
{
	mTupleFeatureSource = pTupleFeatureSource;
}


void RankerData::setRelevantTupleIdSet(RelevantTupleIdSetPtrS const& pRelevantTupleIdSet)
{
	mRelevantTupleIdSet = pRelevantTupleIdSet;
}


void RankerData::setStatisticTupleFilter(FilterPtrS const& pStatisticTupleFilter)
{
	mStatisticTupleFilter = pStatisticTupleFilter;
}


auto RankerData::constructContingencyTable(TupleId pTupleId) const -> ContingencyTable
{
	XASSERT(
		hasContingencyTableSource(),
		"RankerData::constructContingencyTable(): No contingency table source set.");

	return getContingencyTableSource()->constructTable(pTupleId, getMatrixTupleStorage());
}


auto RankerData::constructContingencyTable(TupleT const& pTupleT) const -> ContingencyTable
{
	XASSERT(
		hasContingencyTableSource(),
		"RankerData::constructContingencyTable(): No contingency table source set.");

	return getContingencyTableSource()->constructTable(pTupleT, getMatrixTupleStorage());
}


auto RankerData::constructInstance(TupleId pTupleId) const -> Instance
{
	XASSERT(
		hasTupleFeatureSource(),
		"RankerData::constructInstance(): No tuple feature source set.");

	return getTupleFeatureSource()->constructInstance(pTupleId, getMatrixTupleStorage());
}


auto RankerData::constructInstance(TupleT const& pTupleT) const -> Instance
{
	XASSERT(
		hasTupleFeatureSource(),
		"RankerData::constructInstance(): No tuple feature source set.");

	return getTupleFeatureSource()->constructInstance(pTupleT, getMatrixTupleStorage());
}


int RankerData::checkClass(TupleId pTupleId) const
{
	return (hasRelevantTupleIdSet() && getRelevantTupleIdSet()->has(pTupleId)) ? 1 : 0;
}


int RankerData::checkClass(TupleT const& pTupleT) const
{
	return checkClass(getMatrixTupleStorage()->findTupleId(pTupleT));
}


std::ostream& operator<<(std::ostream& pStream, RankerData const& pData)
{
	return (pStream << "MatrixTupleStorage: " << pData.hasMatrixTupleStorage() << ", " <<
		"ContingencyTableSource: " << pData.hasContingencyTableSource() << ", " <<
		"TupleFeatureSource: " << pData.hasTupleFeatureSource() << ", " <<
		"RelevantTupleIdSet: " << pData.hasRelevantTupleIdSet());
}


	}
}
