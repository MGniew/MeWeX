
#include <cmath>

#include "TScore.h"


namespace function
{
	namespace association
	{


auto TScore::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new TScore(*this));
}


double TScore::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double obs = pContingencyTable[0].observed;
	double exp = pContingencyTable[0].expected;
	double N = pContingencyTable.sumObserved();

	return (obs - exp) / sqrt(obs  * (1.0 - (obs / N)));
}


std::string	TScore::name() const
{
	return "tscore";
}


	}
}
