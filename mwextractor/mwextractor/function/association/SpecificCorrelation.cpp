
#include <cmath>

#include "SpecificCorrelation.h"


namespace function
{
	namespace association
	{


auto SpecificCorrelation::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new SpecificCorrelation(*this));
}


/*
 * f(x) == 0: ok
 */
double SpecificCorrelation::rankUsingTable(
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

	return log2(nominator / denominator);
	//return nominator * log2(nominator / denominator);
}


std::string SpecificCorrelation::name() const
{
	return "specific_correlation";
}


	}
}
