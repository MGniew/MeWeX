
#include <cmath>

#include "ConsonniT1.h"


namespace function
{
	namespace association
	{


auto ConsonniT1::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new ConsonniT1(*this));
}


/*
 * f(x) == 0: ok
 */
double ConsonniT1::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double nominator =
		1.0 +
		pContingencyTable[0].observed +
		pContingencyTable[pContingencyTable.size() - 1].observed;

	double denominator = pContingencyTable.sumObserved() + 1.0;

	return log(nominator) - log(denominator);
}


std::string	ConsonniT1::name() const
{
	return "consonni_t1";
}


	}
}
