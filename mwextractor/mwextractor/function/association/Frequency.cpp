
#include <cmath>

#include "Frequency.h"


namespace function
{
	namespace association
	{


auto Frequency::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new Frequency(*this));
}


/*
 * f(x) == 0: ok
 */
double Frequency::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return pContingencyTable[0].observed;
}


std::string	Frequency::name() const
{
	return "frequency";
}


	}
}
