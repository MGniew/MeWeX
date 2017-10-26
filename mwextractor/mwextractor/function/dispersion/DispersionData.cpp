
#include "../../utils/Debug.h"

#include "DispersionData.h"


namespace function
{
	namespace dispersion
	{


DispersionData::DispersionData(
	MatrixTupleStoragePtrS const& 		pMatrixTupleStorage,
	ContingencyTableSourcePtrS const&	pContingencyTableSource)
:
	mMatrixTupleStorage(pMatrixTupleStorage),
	mContingencyTableSource(pContingencyTableSource)
{

}


auto DispersionData::getMatrixTupleStorage() const -> MatrixTupleStoragePtrS const&
{
	return mMatrixTupleStorage;
}


auto DispersionData::getContingencyTableSource() const -> ContingencyTableSourcePtrS const&
{
	return mContingencyTableSource;
}


bool DispersionData::hasMatrixTupleStorage() const
{
	return getMatrixTupleStorage() != nullptr;
}


bool DispersionData::hasContingencyTableSource() const
{
	return getContingencyTableSource() != nullptr;
}


void DispersionData::setMatrixTupleStorage(MatrixTupleStoragePtrS const& pMatrixTupleStorage)
{
	mMatrixTupleStorage = pMatrixTupleStorage;
}


void DispersionData::setContingencyTableSource(ContingencyTableSourcePtrS const& pContingencyTableSource)
{
	mContingencyTableSource = pContingencyTableSource;
}


auto DispersionData::constructContingencyTable(TupleId pTupleId) const -> ContingencyTable
{
	XASSERT(
		hasContingencyTableSource(),
		"DispersionData::constructContingencyTable(): No contingency table source set.");

	return getContingencyTableSource()->constructTable(pTupleId, getMatrixTupleStorage());
}


auto DispersionData::constructContingencyTable(TupleT const& pTupleT) const -> ContingencyTable
{
	XASSERT(
		hasContingencyTableSource(),
		"DispersionData::constructContingencyTable(): No contingency table source set.");

	return getContingencyTableSource()->constructTable(pTupleT, getMatrixTupleStorage());
}


std::ostream& operator<<(std::ostream& pStream, DispersionData const& pData)
{
	return (pStream << "MatrixTupleStorage: " << pData.hasMatrixTupleStorage() << ", " <<
		"ContingencyTableSource: " << pData.hasContingencyTableSource());
}


	}
}
