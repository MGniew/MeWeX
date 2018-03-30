#pragma once

#include "../Point.h"
#include "../Evaluator.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace TabuSearch
		{


/**
* The tabu search algorithm class template.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam NeighbourhoodScheme Provides algorithm to generate neighbours.
* @tparam Neighbourhood A neighbourhood class template.
* @tparam TabuList A class of the tabu featurs.
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
         template<typename InnerArgumentsType, typename InnerNeighbourhoodSchemeType, typename TabuListType> class Neighbourhood,
         template<typename InnerArgumentsType> class TabuList,
         typename StepType,
         template<typename InnerArgumentsType, typename InnerStepType> class StepCounter,
         typename TimeType,
         template<typename InnerArgumentsType, typename InnerTimeType> class Timer,
         template<typename InnerArgumentsType, typename InnerTimeType, typename InnerStepType, typename NeighbourhoodType, typename TabuListType> class Report>
class TabuSearch
{
public:
    /**
    * Creates algorithm object with given arguments.
    *
    * @param[in] rStartPoint First, based point.
    * @param[in] pEvaluator Provides a mechanism to evaluate the points.
    * @param[in] rArgs The argument object. Contains the arguments for a call policy.
    */
    TabuSearch(const Point& rStartPoint, Evaluator* pEvaluator, const ArgumentsType& rArgs)
    {
        this->mCallPoliciesArguments = rArgs;
        this->mTabuList = TabuList<ArgumentsType>(this->mCallPoliciesArguments);
        this->mNumberOfEvaluations = 0;

        this->mBest = rStartPoint;
        this->mpEvaluator = pEvaluator;
    }

    /**
    * An object destructor.
    */
    ~TabuSearch(void)
    {}

    /**
    * Solves the optimization problem. Result of optimization is saved in a file.
    */
    Point start()
    {
        Timer<ArgumentsType, TimeType> timer(this->mCallPoliciesArguments);
        StepCounter<ArgumentsType, StepType> step(this->mCallPoliciesArguments);
        NeighbourhoodScheme neighbourhoodScheme(this->mCallPoliciesArguments);
        Neighbourhood<ArgumentsType, NeighbourhoodScheme, TabuList<ArgumentsType> > neighbourhood(this->mCallPoliciesArguments, neighbourhoodScheme);
        Report<ArgumentsType,
               TimeType,
               StepType,
               Neighbourhood<ArgumentsType, NeighbourhoodScheme, TabuList<ArgumentsType> >,
               TabuList<ArgumentsType> > report(this->mCallPoliciesArguments);

        mpEvaluator->evaluate(this->mBest);
        this->mNumberOfEvaluations++;
        this->mTabuList.add(this->mBest);

        Point candidate;
        Point current = this->mBest;

        while(!step.isFinished())
        {
            neighbourhood.generate(current, this->mTabuList);
            mpEvaluator->evaluate(neighbourhood.getNeighbours());
            candidate = neighbourhood.locateBest();
            this->mNumberOfEvaluations += neighbourhood.getSize();

            current = candidate;

            if(current.getEvaluationPerformance().isGreater(this->mBest.getEvaluationPerformance()))
            {
                this->mBest = candidate;
                if(! this->mTabuList.contain(current))
                {
                    this->mTabuList.add(current);
                }
            }

            report.reportStep(step.getCurrentStep(), current, this->mBest, neighbourhood, this->mTabuList);
            step.increase();
        }

        report.reportSummary(this->mNumberOfEvaluations, timer.getTime(), this->mBest);

        return this->mBest;
    }

private:
    TabuList<ArgumentsType> mTabuList;
    Point mBest;
    Evaluator* mpEvaluator;
    int mNumberOfEvaluations;
    ArgumentsType mCallPoliciesArguments;
}; // class TabuSearch


		}
	} // namespace TabuSearch
} // namespace Optimizer
