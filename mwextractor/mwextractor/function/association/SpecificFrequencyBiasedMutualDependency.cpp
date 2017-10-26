
#include <cmath>

#include "SpecificFrequencyBiasedMutualDependency.h"


namespace function
{
	namespace association
	{


auto SpecificFrequencyBiasedMutualDependency::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new SpecificFrequencyBiasedMutualDependency(*this));
}


double SpecificFrequencyBiasedMutualDependency::rankUsingTable(
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

	//DEBUG_MESSAGE(nominator << ' ' << denominator << ' ' << (nominator * nominator * nominator / denominator) << ' ' << log2(nominator * nominator * nominator / denominator));

	return log2(nominator * nominator * nominator / denominator);
}


std::string SpecificFrequencyBiasedMutualDependency::name() const
{
	return "specific_frequency_biased_mutual_dependency";
}


	}
}
