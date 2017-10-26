
#include <cmath>

#include "Sorgenfrei.h"


namespace function
{
	namespace association
	{


auto Sorgenfrei::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new Sorgenfrei(*this));
}


/*
 * f(x) == 0: ok
 */
double Sorgenfrei::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double nominator = std::pow(pContingencyTable[0].observed, pContingencyTable.tupleSize());
	double denominator = 1.0;

	for (size_t i = 1; i < pContingencyTable.size() - 1; ++i)
	{
		denominator *= (pContingencyTable[0].observed + pContingencyTable[i].observed);
	}

	return nominator / denominator;
}


std::string	Sorgenfrei::name() const
{
	return "sorgenfrei";
}


	}
}
