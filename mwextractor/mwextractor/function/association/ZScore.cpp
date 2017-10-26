
#include <cmath>

#include "ZScore.h"


namespace function
{
	namespace association
	{


auto ZScore::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new ZScore(*this));
}


double ZScore::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double obs = pContingencyTable[0].observed;
	double exp = pContingencyTable[0].expected;
	double N = pContingencyTable.sumObserved();

	return (obs - exp) / sqrt(exp  * (1.0 - (exp / N)));
}


std::string	ZScore::name() const
{
	return "zscore";
}


	}
}
