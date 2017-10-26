
#include <cmath>

#include "ConsonniT2.h"


namespace function
{
	namespace association
	{


auto ConsonniT2::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new ConsonniT2(*this));
}


/*
 * f(x) == 0: ok
 */
double ConsonniT2::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double sum = pContingencyTable.sumObserved() + 1.0;

	double secondElement = 1.0;
	for (size_t i = 1; i < pContingencyTable.size() - 1; ++i)
	{
		secondElement += pContingencyTable[i].observed;
	}

	return (log(sum) - log(secondElement)) / log(sum);
}


std::string	ConsonniT2::name() const
{
	return "consonni_t2";
}


	}
}
