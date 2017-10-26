
#include <cmath>

#include "SpecificMutualDependency.h"


namespace function
{
	namespace association
	{


auto SpecificMutualDependency::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new SpecificMutualDependency(*this));
}


double SpecificMutualDependency::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	size_t tupleSize	= pContingencyTable.tupleSize();
	double oneByDiv		= 1.0 / pContingencyTable.sumObserved();

	double nominator 	= pContingencyTable[0].observed * oneByDiv;
	double denominator	= 1.0;

	for (size_t i = 0; i < tupleSize; ++i)
	{
		double elementFrequency = pContingencyTable.gatherObservedNgramData(i, 1)[0].observed;
		denominator *= elementFrequency * oneByDiv;
	}

	return log2(nominator * nominator / denominator);
}


std::string SpecificMutualDependency::name() const
{
	return "specific_mutual_dependency";
}


	}
}
