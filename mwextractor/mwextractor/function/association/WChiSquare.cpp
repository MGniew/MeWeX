
#include "WChiSquare.h"


namespace function
{
	namespace association
	{


auto WChiSquare::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new WChiSquare(*this));
}


double WChiSquare::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double wx2 = 0.0;

	for (size_t i = 0; i < pContingencyTable.size(); ++i)
	{
		double element =
			((pContingencyTable[i].expected - pContingencyTable[i].observed) *
			 (pContingencyTable[i].expected - pContingencyTable[i].observed)) /
			 (pContingencyTable[i].expected);

		if (pContingencyTable[i].observed < pContingencyTable[i].expected)
		{
			element = -element;
		}

		wx2 += element;
	}

	return wx2;
}


std::string WChiSquare::name() const
{
	return "w_chi_square";
}


	}
}
