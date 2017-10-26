
#include <cmath>

#include "ExpectedFrequency.h"


namespace function
{
	namespace association
	{


auto ExpectedFrequency::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new ExpectedFrequency(*this));
}


/*
 * f(x) == 0: ok
 */
double ExpectedFrequency::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return pContingencyTable[0].expected;
}


std::string	ExpectedFrequency::name() const
{
	return "expected_frequency";
}


	}
}
