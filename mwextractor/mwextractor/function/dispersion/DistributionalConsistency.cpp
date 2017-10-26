
#include <cmath>

#include "../../structure/storage/FrequencyStorage.h"

#include "DistributionalConsistency.h"


namespace function
{
	namespace dispersion
	{


double DistributionalConsistency::disperse(TupleId pTupleId) const
{
	XASSERT(
		getDispersionData()->hasMatrixTupleStorage(),
		"DistributionalConsistency::disperse(): Matrix tuple storage not set.");

	structure::storage::FrequencyStorage storage =
		getDispersionData()->getMatrixTupleStorage()->findTuple(pTupleId).getMetadata();

	double ret = 0.0;

	for (size_t i = 0; i < storage.getSourceCount(); ++i)
	{
		ret += std::sqrt(storage.getLocalFrequency(i));
	}

	ret /= static_cast<double>(storage.getSourceCount());

	return ret * ret;
}


std::string	DistributionalConsistency::name() const
{
	return "distributional_consistency";
}


	}
}
