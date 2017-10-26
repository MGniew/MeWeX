
#include "../../utils/Math.h"

#include "../../structure/storage/FrequencyStorage.h"

#include "StandardDeviation.h"


namespace function
{
	namespace dispersion
	{


double StandardDeviation::disperse(TupleId pTupleId) const
{
	XASSERT(
		getDispersionData()->hasMatrixTupleStorage(),
		"DistributionalConsistency::disperse(): Matrix tuple storage not set.");

	structure::storage::FrequencyStorage storage =
		getDispersionData()->getMatrixTupleStorage()->findTuple(pTupleId).getMetadata();

	double mean = 0.0;
	for (size_t s = 0; s < storage.getSourceCount(); ++s)
	{
		mean += storage.getLocalFrequency(s);
	}
	mean /= static_cast<double>(storage.getSourceCount());

	double stddev = 0.0;
	for (size_t s = 0; s < storage.getSourceCount(); ++s)
	{
		double element = (mean - storage.getLocalFrequency(s));
		stddev += element * element;
	}
	stddev /= static_cast<double>(storage.getSourceCount());

	return std::sqrt(stddev);
}


std::string	StandardDeviation::name() const
{
	return "standard_deviation";
}


	}
}
