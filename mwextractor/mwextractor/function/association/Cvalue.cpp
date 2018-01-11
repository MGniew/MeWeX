
#include <cmath>

#include "Cvalue.h"


namespace function
{
	namespace association
	{


auto Cvalue::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new Cvalue(*this));
}


/*
 * f(x) == 0: ok
 */
double Cvalue::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double LP = 0.0, LPsum = 0.0, rank;
	for(int i = 1; i < pContingencyTable.size() - 1;i++)
	{
		LPsum += pContingencyTable[i].observed;
		if(pContingencyTable[i].observed > 0)
			LP += 1.0;
	}
	double l = (log(pContingencyTable.tupleSize()) + 0.1);

	if(LP == 0)
	{
		rank = l * pContingencyTable[0].observed;
	}
	else
	{
		double l = (log(pContingencyTable.tupleSize()) + 0.1);
		rank = l * (pContingencyTable[0].observed - (LPsum/LP));
	}

	return rank;
}


std::string	Cvalue::name() const
{
	return "cvalue";
}


	}
}
