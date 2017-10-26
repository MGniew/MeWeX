
#include <cmath>

#include "UnigramSubtuples.h"


namespace function
{
	namespace association
	{


auto UnigramSubtuples::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new UnigramSubtuples(*this));
}


double UnigramSubtuples::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	static const double MOD = 3.29;

	double oddsRatioLog = std::log(OddsRatio::rankUsingTable(pTupleId, pContingencyTable));

	double underSqrt = 0.0;
	for (size_t i = 0; i < pContingencyTable.size(); ++i)
	{
		/* do not divide by zero coz of black holes */
		underSqrt += 1.0 / (pContingencyTable[i].observed + 1.0);
	}

	return oddsRatioLog - MOD * std::sqrt(underSqrt);
}


std::string	UnigramSubtuples::name() const
{
	return "unigram_subtuples";
}


	}
}
