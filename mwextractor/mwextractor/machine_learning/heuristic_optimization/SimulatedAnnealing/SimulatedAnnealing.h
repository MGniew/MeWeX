#pragma once

#include "../Point.h"
#include "../Evaluator.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace SimulatedAnnealing
		{


/**
* The simulated annealing algorithm class template.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam NeighbourhoodScheme Provides algorithm to generate neighbours.
* @tparam TemperatureType A temperature type. Could be int, double, etc.
* @tparam TemperatureScheme A scheme of the temperature.
* @tparam SelectionRule A selection rule.
* @tparam StepType A algorithm step type. Could be int, double, etc.
* @tparam StepCounter A class template to counting steps.
* @tparam TimeType A time data type.
* @tparam Timer A class template to time countdown.
* @tparam Report A reporting class template.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename NeighbourhoodScheme,
         typename TemperatureType,
         template<typename ArgumentsType, typename StepType, typename TemperatureType> class TemperatureScheme,
         template<typename ArgumentsType, typename TemperatureType> class SelectionRule,
         typename StepType,
         template<typename ArgumentsType, typename StepType> class StepCounter,
         typename TimeType,
         template<typename ArgumentsType, typename TimeType> class Timer,
         template<typename ArgumentsType, typename TimeType, typename TemperatureType, typename StepType> class Report>
class SimulatedAnnealing
{
public:
    /**
    * Creates algorithm object with given arguments.
    *
    * @param[in] rStartPoint First, based point.
    * @param[in] pEvaluator Provides a mechanism to evaluate the points.
    * @param[in] rArgs The argument object. Contains the arguments for a call policy.
    */
    SimulatedAnnealing(const Point& rStartPoint, Evaluator* pEvaluator, const ArgumentsType& rArgs)
    {
        this->mCallPoliciesArguments = rArgs;
        this->mNumberOfEvaluations = 0;

        this->mCurrent = rStartPoint;
        this->mpEvaluator = pEvaluator;
    }

    /**
    * An object destructor.
    */
    ~SimulatedAnnealing(void) {}

    /**
    * Solves the optimization problem. Result of optimization is saved in a file.
    */
    Point start()
    {
        Timer<ArgumentsType, TimeType> timer(this->mCallPoliciesArguments);
        StepCounter<ArgumentsType, StepType> step(this->mCallPoliciesArguments);
        Report<ArgumentsType, TimeType, TemperatureType, StepType> report(this->mCallPoliciesArguments);
        TemperatureScheme<ArgumentsType, StepType, TemperatureType> temperatureScheme(this->mCallPoliciesArguments);
        SelectionRule<ArgumentsType, TemperatureType> selection(this->mCallPoliciesArguments);
        NeighbourhoodScheme neighbourhoodScheme(this->mCallPoliciesArguments);

        mpEvaluator->evaluate(this->mCurrent);
        this->mBest = this->mCurrent;
        this->mNumberOfEvaluations++;

        Point candidate;
        TemperatureType temperature;

        while(!step.isFinished())
        {
            temperature = temperatureScheme.getTemperature(step.getCurrentStep());
            report.reportStep(step.getCurrentStep(), temperature, this->mCurrent, this->mBest);

            candidate = neighbourhoodScheme.getNeighbour(this->mCurrent);
            mpEvaluator->evaluate(candidate);
            this->mNumberOfEvaluations++;

            if(selection.accept(temperature, this->mCurrent, candidate))
            {
                this->mCurrent = candidate;
                if(this->mCurrent.getEvaluationPerformance().isGreater(this->mBest.getEvaluationPerformance()))
                {
                    this->mBest = this->mCurrent;
                }
            }

            step.increase();
        }
        report.reportSummary(this->mNumberOfEvaluations, timer.getTime(), this->mBest);

        return this->mBest;
    }

private:
    SimulatedAnnealing(void)
    {}

    Point mBest;
    Point mCurrent;
    Evaluator* mpEvaluator;
    int mNumberOfEvaluations;
    ArgumentsType mCallPoliciesArguments;
}; // class SimulatedAnnealing


		}
	} // namespace SimulatedAnnealing
} // namespace Optimizer

