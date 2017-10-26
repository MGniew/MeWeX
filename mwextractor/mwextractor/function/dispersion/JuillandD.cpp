
#include <cmath>

#include "../../structure/storage/FrequencyStorage.h"

#include "JuillandD.h"


namespace function
{
	namespace dispersion
	{


double JuillandD::disperse(TupleId pTupleId) const
{
	XASSERT(
		getDispersionData()->hasMatrixTupleStorage(),
		"JuillandD::disperse(): Matrix tuple storage not set.");

	structure::storage::FrequencyStorage storage =
		getDispersionData()->getMatrixTupleStorage()->findTuple(pTupleId).getMetadata();

	double vc 			= VariationCoefficient::disperse(pTupleId);
	double denominator 	= std::sqrt(static_cast<double>(storage.getSourceCount() - 1));

	return 1.0 - (vc / denominator);
}


std::string	JuillandD::name() const
{
	return "juilland_d";
}


	}
}
