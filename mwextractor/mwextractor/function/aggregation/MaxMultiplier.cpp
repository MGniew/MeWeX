
#include <map>

#include "MaxMultiplier.h"


namespace function
{
	namespace aggregation
	{


double MaxMultiplier::compute(std::vector<double> const& pValues) const
{
	double res = 1.0;
	for (size_t i = 0; i < pValues.size(); ++i)
	{
		res *= pValues[i] * getWeightVector()[i];
	}
	return res;
}


std::string MaxMultiplier::name() const
{
	return "max_multiplier";
}


	}
}
