
#include "../../structure/storage/FrequencyStorage.h"

#include "VariationCoefficient.h"


namespace function
{
	namespace dispersion
	{


double VariationCoefficient::disperse(TupleId pTupleId) const
{
	XASSERT(
		getDispersionData()->hasMatrixTupleStorage(),
		"DistributionalConsistency::disperse(): Matrix tuple storage not set.");

	structure::storage::FrequencyStorage storage =
		getDispersionData()->getMatrixTupleStorage()->findTuple(pTupleId).getMetadata();

	double stdev		= StandardDeviation::disperse(pTupleId);
	double sourceCount 	= static_cast<double>(storage.getSourceCount());

	return stdev * sourceCount / storage.sumLocalFrequencies();
}


std::string	VariationCoefficient::name() const
{
	return "variation_coefficient";
}


	}
}
