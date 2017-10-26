
#include "../utils/Debug.h"

#include "OptimizationFunction.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


auto OptimizationFunction::getLastOptimizationResultMap() const -> OptimizationResultMap const&
{
	return mOptimizationResultMap;
}


auto OptimizationFunction::getLastOptimizationResultMap() -> OptimizationResultMap&
{
	return mOptimizationResultMap;
}


auto OptimizationFunction::getBestLastOptimizationResult() const -> OptimizationResult
{
	return *(mOptimizationResultMap.rend());
}


	}
}
