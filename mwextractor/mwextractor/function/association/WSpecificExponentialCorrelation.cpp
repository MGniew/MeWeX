
#include <cmath>

#include "WSpecificExponentialCorrelation.h"


namespace function
{
	namespace association
	{


auto WSpecificExponentialCorrelation::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new WSpecificExponentialCorrelation(*this));
}


WSpecificExponentialCorrelation::WSpecificExponentialCorrelation(double pExponent)
:
	SpecificExponentialCorrelation(pExponent)
{

}


double WSpecificExponentialCorrelation::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return (pContingencyTable[0].observed / pContingencyTable.sumObserved()) *
		SpecificExponentialCorrelation::rankUsingTable(pTupleId, pContingencyTable);
}


std::string	WSpecificExponentialCorrelation::name() const
{
	return "w_specific_exponential_correlation";
}


	}
}
