
#include "PearsonsChiSquare.h"


namespace function
{
	namespace association
	{


auto PearsonsChiSquare::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new PearsonsChiSquare(*this));
}


/*
 * f(x) == 0: ok ??
 */
double PearsonsChiSquare::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double x2 = 0.0;
	for (size_t i = 0; i < pContingencyTable.size(); ++i)
	{
		x2 += 	((pContingencyTable[i].expected - pContingencyTable[i].observed) *
				 (pContingencyTable[i].expected - pContingencyTable[i].observed)) /
				 (pContingencyTable[i].expected);
	}

	return x2;
}


std::string PearsonsChiSquare::name() const
{
	return "pearsons_chi_square";
}


	}
}
