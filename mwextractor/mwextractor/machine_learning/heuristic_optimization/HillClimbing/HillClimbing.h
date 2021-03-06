#pragma once

#include "../Point.h"
#include "../Evaluator.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace HillClimbing
		{


/**
* The Hill Climbing algorithm class template.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam NeighbourhoodScheme Provides algorithm to generate neighbours.
* @tparam Neighbourhood A neighbourhood class template.
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
         template<typename InnerArgumentsType, typename InnerNeighbourhoodSchemeType> class Neighbourhood,
         typename StepType,
         template<typename InnerArgumentsType, typename InnerStepType> class StepCounter,
         typename TimeType,
         template<typename InnerArgumentsType, typename InnerTimeType> class Timer,
         template<typename InnerArgumentsType, typename InnerTimeType, typename InnerStepType, typename NeighbourhoodType> class Report>
class HillClimbing
{
public:
    /**
    * Creates algorithm object with given arguments.
    *
    * @param[in] rStartPoint First, based point.
    * @param[in] pEvaluator Provides a mechanism to evaluate the points.
    * @param[in] rArgs The argument object. Contains the arguments for a call policy.
    */
    HillClimbing(const Point& rStartPoint, Evaluator* pEvaluator, const ArgumentsType& rArgs)
    {
        this->mCallPoliciesArguments = rArgs;
        this->mNumberOfEvaluations = 0;

        this->mBest = rStartPoint;
        this->mpEvaluator = pEvaluator;
    }

    /**
    * An object destructor.
    */
    ~HillClimbing(void) {}

    /**
    * Solves the optimization problem. Result of optimization is saved in a file.
    */
    Point start()
    {
        Timer<ArgumentsType, TimeType> timer(this->mCallPoliciesArguments);
        StepCounter<ArgumentsType, StepType> step(this->mCallPoliciesArguments);
        Report<ArgumentsType, TimeType, StepType, Neighbourhood<ArgumentsType, NeighbourhoodScheme> > report(this->mCallPoliciesArguments);
        NeighbourhoodScheme neighbourhoodScheme(this->mCallPoliciesArguments);
        Neighbourhood<ArgumentsType, NeighbourhoodScheme > neighbourhood(this->mCallPoliciesArguments, neighbourhoodScheme);

        mpEvaluator->evaluate(this->mBest);
        this->mNumberOfEvaluations++;
        Point current = this->mBest;
        Point candidate;

        while(!step.isFinished())
        {
            neighbourhood.generate(current);
            mpEvaluator->evaluate(neighbourhood.getNeighbours());
            candidate = neighbourhood.locateBest();
            this->mNumberOfEvaluations += neighbourhood.getSize();

            if(candidate.getEvaluationPerformance().isGreater(current.getEvaluationPerformance()))
            {
                current = candidate;
                if(current.getEvaluationPerformance().isGreater(this->mBest.getEvaluationPerformance()))
                {
                    this->mBest = current;
                }
                report.reportStep(step.getCurrentStep(), candidate, current, this->mBest, neighbourhood);
            }
            else
            {
                report.reportStep(step.getCurrentStep(), candidate, current, this->mBest, neighbourhood);
                current.setRandomParameters();
                mpEvaluator->evaluate(current);
                this->mNumberOfEvaluations++;
            }

            step.increase();
        }

        report.reportSummary(this->mNumberOfEvaluations, timer.getTime(), this->mBest);

        return this->mBest;
    }

private:
    HillClimbing(void)
    {}

    Point mBest;
    Evaluator* mpEvaluator;
    int mNumberOfEvaluations;
    ArgumentsType mCallPoliciesArguments;
}; // class HillClimbing


		}
	} // namespace HillClimbing
} // namespace Optimizer

