
#include <cmath>

#include "../../utils/Debug.h"
#include "LogLikelihood.h"


namespace function
{
	namespace association
	{


auto LogLikelihood::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new LogLikelihood(*this));
}


/*
 * f(x) == 0: ok
 */
double LogLikelihood::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double ll = 0.0;
	for (size_t i = 0; i < pContingencyTable.size(); ++i)
	{
		if (pContingencyTable[i].observed)
		{
			ll += pContingencyTable[i].observed * std::log2(pContingencyTable[i].observed / pContingencyTable[i].expected);
		}
	}

	return -2.0 * ll;
}


std::string	LogLikelihood::name() const
{
	return "loglikelihood";
}


	}
}
