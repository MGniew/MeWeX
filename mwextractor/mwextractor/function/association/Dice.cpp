
#include "Dice.h"


namespace function
{
	namespace association
	{


auto Dice::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new Dice(*this));
}


/*
 * f(x) == 0: ok
 */
double Dice::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	size_t tupleSize = pContingencyTable.tupleSize();

	double nominator 	= tupleSize * pContingencyTable[0].observed;
	double denominator 	= 0.0;
	for (size_t i = 0; i < tupleSize; ++i)
	{
		denominator += pContingencyTable.gatherObservedNgramData(i, 1)[0].observed;
	}

	return nominator / denominator;
}


std::string	Dice::name() const
{
	return "dice";
}


	}
}
