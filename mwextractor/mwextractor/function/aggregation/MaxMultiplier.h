
#pragma once

#include "AggregationFunction.h"


namespace function
{
	namespace aggregation
	{


class MaxMultiplier : public AggregationFunction
{
public:
	virtual std::string name() const override;

protected:
	virtual double compute(std::vector<double> const& pValues) const override;
};


	}
}
