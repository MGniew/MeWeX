
#include <map>

#include "../../utils/Parallel.h"
#include "../../utils/Math.h"

#include "MaxSum.h"


namespace function
{
	namespace aggregation
	{


double MaxSum::compute(std::vector<double> const& pValues) const
{
	double res = 0.0;
	for (size_t i = 0; i < pValues.size(); ++i)
	{
		if(pValues[i] == pValues[i]) // check if value is not null
			res += pValues[i] * getWeightVector()[i];
	}
	return res;
}


std::string MaxSum::name() const
{
	return "max_sum";
}


	}
}
