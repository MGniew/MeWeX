
#include <cmath>

#include "../../structure/storage/FrequencyStorage.h"

#include "TermFrequencyInverseDocumentFrequency.h"


namespace function
{
	namespace dispersion
	{


double TermFrequencyInverseDocumentFrequency::disperse(TupleId pTupleId) const
{
	XASSERT(
		getDispersionData()->hasMatrixTupleStorage(),
		"DistributionalConsistency::disperse(): Matrix tuple storage not set.");

	FrequencyStorage storage = getDispersionData()->
		getMatrixTupleStorage()->findTuple(pTupleId).getMetadata();

	double idf = std::log10(
		static_cast<double>(storage.getSourceCount()) /
		static_cast<double>(storage.countNonZeroSources()));

	return storage.sumLocalFrequencies() * idf;
}


std::string	TermFrequencyInverseDocumentFrequency::name() const
{
	return "term_frequency_inverse_document_frequency";
}


	}
}
