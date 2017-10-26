
#include <cmath>

#include "WSpecificCorrelation.h"


namespace function
{
	namespace association
	{


auto WSpecificCorrelation::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new WSpecificCorrelation(*this));
}


double WSpecificCorrelation::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	size_t tupleSize	= pContingencyTable.tupleSize();
	double oneByDiv		= 1.0 / pContingencyTable.sumObserved();

	double nominator 	= pContingencyTable[0].observed * oneByDiv;
	double denominator	= 1.0;

	for (size_t i = 0; i < tupleSize; ++i)
	{
		double elementFrequency = pContingencyTable.gatherObservedNgramData(i, 1)[0].observed;
		denominator *= elementFrequency * oneByDiv;
	}

	return nominator * log2(nominator / denominator);
}


std::string WSpecificCorrelation::name() const
{
	return "w_specific_correlation";
}


	}
}
