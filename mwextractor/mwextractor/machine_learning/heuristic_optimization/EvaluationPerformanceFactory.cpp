#include "EvaluationPerformanceFactory.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


EvaluationPerformanceFactory::EvaluationPerformanceFactory(void)
{}

EvaluationPerformanceFactory::~EvaluationPerformanceFactory(void)
{}


BaseEvaluationPerformance* EvaluationPerformanceFactory::create(int type)
{
    switch(type)
    {
    case INT:
    {
        return new IntEvaluationPerformance();
    }
    case DOUBLE:
    {
        return new DoubleEvaluationPerformance();
    }
    default:
        return NULL;
    }
}


	}
}
