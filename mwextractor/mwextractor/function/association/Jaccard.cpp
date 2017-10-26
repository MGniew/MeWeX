
#include "Jaccard.h"


namespace function
{
	namespace association
	{


auto Jaccard::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new Jaccard(*this));
}


/*
 * f(x) == 0: ok
 */
double Jaccard::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	double nominator = pContingencyTable[0].observed;
	double denominator = (pContingencyTable.sumObserved() - pContingencyTable[pContingencyTable.size() - 1].observed);
	return nominator / denominator;
}


std::string	Jaccard::name() const
{
	return "jaccard";
}


	}
}
