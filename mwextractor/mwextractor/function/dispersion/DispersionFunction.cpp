
#include "DispersionFunction.h"


namespace function
{
	namespace dispersion
	{


DispersionFunction::DispersionFunction()
:
	mDispersionData(new DispersionData(nullptr))
{

}


double DispersionFunction::disperse(TupleT const& pTableT) const
{
	return disperse(getDispersionData()->getMatrixTupleStorage()->findTupleId(pTableT));
}


double DispersionFunction::operator()(TupleId pTableId) const
{
	return disperse(pTableId);
}


double DispersionFunction::operator()(TupleId const& pTableT) const
{
	return disperse(pTableT);
}


auto DispersionFunction::getDispersionData() const -> DispersionDataPtrS const&
{
	return mDispersionData;
}


auto DispersionFunction::getDispersionData() -> DispersionDataPtrS&
{
	return mDispersionData;
}


bool DispersionFunction::hasDispersionData() const
{
	return getDispersionData() != nullptr;
}


void DispersionFunction::setDispersionData(DispersionDataPtrS const& pDispersionData)
{
	mDispersionData = pDispersionData;
}


void DispersionFunction::initialize(DispersionDataPtrS const& pDispersionData)
{
	setDispersionData(pDispersionData);
}


	}
}
