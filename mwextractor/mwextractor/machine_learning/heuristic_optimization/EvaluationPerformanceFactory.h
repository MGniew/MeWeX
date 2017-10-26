#pragma once

#include "BaseEvaluationPerformance.h"
#include "IntEvaluationPerformance.h"
#include "DoubleEvaluationPerformance.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


class EvaluationPerformanceFactory
{
public:
    EvaluationPerformanceFactory(void);
    ~EvaluationPerformanceFactory(void);

    static BaseEvaluationPerformance* create(int type);

}; // class EvaluationPerformanceFactory


	}
} // namespace Optimizer

