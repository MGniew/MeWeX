
#include "MutualExpectation.h"


namespace function
{
	namespace association
	{


auto MutualExpectation::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new MutualExpectation(*this));
}


/*
 * f(x) == 0: ok
 */
double MutualExpectation::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	size_t tupleSize = pContingencyTable.tupleSize();

	double probability	= pContingencyTable[0].observed / pContingencyTable.sumObserved();
	double nominator 	= probability * tupleSize * pContingencyTable[0].observed;

	if (nominator == 0.0)
	{
		return 0.0;
	}

	double denominator 	= 0.0;
	for (size_t i = 0; i < tupleSize; ++i)
	{
		denominator += pContingencyTable.gatherObservedNgramData(i, 1)[0].observed;
	}

	return nominator / denominator;
}


std::string	MutualExpectation::name() const
{
	return "mutual_expectation";
}


	}
}
