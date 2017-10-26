
#include <cmath>

#include "InversedExpectedFrequency.h"


namespace function
{
	namespace association
	{


auto InversedExpectedFrequency::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new InversedExpectedFrequency(*this));
}


/*
 * f(x) == 0: ok
 */
double InversedExpectedFrequency::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return 1.0 / pContingencyTable[0].expected;
}


std::string	InversedExpectedFrequency::name() const
{
	return "inversed_expected_frequency";
}


	}
}
