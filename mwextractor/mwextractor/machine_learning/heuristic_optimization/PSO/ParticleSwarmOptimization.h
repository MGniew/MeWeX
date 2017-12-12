#pragma once

#include <string>

#include "../Point.h"
#include "../Evaluator.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{

/**
* The random search algorithm class template.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam StepType A algorithm step type. Could be int, double, etc.
* @tparam StepCounter A class template to counting steps.
* @tparam TimeType A time data type.
* @tparam Timer A class template to time countdown.
* @tparam Report A reporting class template.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename StepType,
         template<typename ArgumentsType, typename StepType> class StepCounter,
         typename TimeType,
         template<typename ArgumentsType, typename TimeType> class Timer,
         template<typename ArgumentsType, typename TimeType, typename StepType> class Report>
class ParticleSwarmOptimization
{
public:
    /**
    * Creates algorithm object with given arguments.
    *
    * @param[in] rStartPoint First, based point.
    * @param[in] pEvaluator Provides a mechanism to evaluate the points.
    * @param[in] rArgs The argument object. Contains the arguments for a call policy.
    */
    ParticleSwarmOptimization(const Point& rStartPoint, Evaluator* pEvaluator, const ArgumentsType& rArgs)
    {
        this->mCallPoliciesArguments = rArgs;
        this->mNumberOfEvaluations = 0;

        this->mBest = rStartPoint;
        this->mpEvaluator = pEvaluator;
    }

    /**
    * An object destructor.
    */
    ~ParticleSwarmOptimization(void) {}

    /**
    * Solves the optimization problem. Result of optimization is saved in a file.
    */
    Point start();

private:
    ParticleSwarmOptimization(void){}

    Point mBest;
    Evaluator* mpEvaluator;
    int mNumberOfEvaluations;
    ArgumentsType mCallPoliciesArguments;
}; // class ParticleSwarmOptimization


		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer
