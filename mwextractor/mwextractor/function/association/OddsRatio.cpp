
#include "OddsRatio.h"


namespace function
{
	namespace association
	{


auto OddsRatio::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new OddsRatio(*this));
}


/*
 * f(x) == 0: ok
 */
double OddsRatio::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double nominator =
		pContingencyTable[0].observed *
		pContingencyTable[pContingencyTable.size() - 1].observed;

	double denominator = 1.0;
	for (size_t i = 1; i < pContingencyTable.size() - 1; ++i)
	{
		denominator *= (1.0 + pContingencyTable[i].observed);
	}

	return nominator / denominator;
}


std::string	OddsRatio::name() const
{
	return "odds_ratio";
}


	}
}
