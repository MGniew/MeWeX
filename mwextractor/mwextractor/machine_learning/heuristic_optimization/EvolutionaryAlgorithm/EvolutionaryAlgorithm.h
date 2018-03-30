#pragma once

#include <string>

#include "Individual.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{
/**
* The evolutionary algorithm class template.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam Population A poulation class template.
* @tparam SelectionRule A selection rule class template
* @tparam MutationScheme Provides algorithm to mutate individuals.
* @tparam CrossoverScheme Provides algorithm to crossover individuals.
* @tparam StepType A algorithm step type. Could be int, double, etc.
* @tparam StepCounter A class template to counting steps.
* @tparam TimeType A time data type.
* @tparam Timer A class template to time countdown.
* @tparam Report A reporting class template.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         template<typename InnerArgumentsType, typename Mutation, typename Crossover> class Population,
         template<typename InnerArgumentsType, typename PopulationType> class SelectionRule,
         template<typename InnerArgumentsType> class MutationScheme,
         template<typename InnerArgumentsType> class CrossoverScheme,
         typename StepType,
         template<typename InnerArgumentsType, typename InnerStepType> class StepCounter,
         typename TimeType,
         template<typename InnerArgumentsType, typename InnerTimeType> class Timer,
         template<typename InnerArgumentsType, typename InnerTimeType, typename InnerStepType, typename PopulationType> class Report>
class EvolutionaryAlgorithm
{
public:
    /**
    * Creates algorithm object with given arguments.
    *
    * @param[in] rStartPoint First, based individual.
    * @param[in] pEvaluator Provides a mechanism to evaluate the individuals.
    * @param[in] rArgs The argument object. Contains the arguments for a call policy.
    */
    EvolutionaryAlgorithm(const Point& rStartPoint, Evaluator* pEvaluator, const ArgumentsType& rArgs)
    {
        this->callPoliciesArguments = rArgs;

        this->mNumberOfEvaluations = 0;

        this->mBest = rStartPoint;
        this->mpEvaluator = pEvaluator;

        this->mPopulation = Population<ArgumentsType, MutationScheme<ArgumentsType>, CrossoverScheme<ArgumentsType> >(this->mBest, rArgs, rArgs.getNumberOfClone());
    }

    /**
    * An object destructor.
    */
    ~EvolutionaryAlgorithm(void) {}

    /**
    * Solves the optimization problem. Result of optimization is saved in a file.
    */
    Point start()
    {
        Timer<ArgumentsType, TimeType> timer(callPoliciesArguments);
        StepCounter<ArgumentsType, StepType> step(callPoliciesArguments);
        SelectionRule<ArgumentsType, Population<ArgumentsType, MutationScheme<ArgumentsType>, CrossoverScheme<ArgumentsType> > > selection(callPoliciesArguments);
        MutationScheme<ArgumentsType> mutationScheme;
        CrossoverScheme<ArgumentsType> crossoverScheme;
        Report<ArgumentsType, TimeType, StepType, Population<ArgumentsType, MutationScheme<ArgumentsType>, CrossoverScheme<ArgumentsType> > > report(callPoliciesArguments);

        while(!step.isFinished())
        {
            mpEvaluator->evaluate(this->mPopulation.getIndividuals());
            this->mNumberOfEvaluations += this->mPopulation.getPopulationSize();
            this->mPopulation.computeStatistics();

            if(this->mPopulation.getBestIndividual().getEvaluationPerformance().isGreater(this->mBest.getEvaluationPerformance()))
            {
                this->mBest = this->mPopulation.getBestIndividual();
            }

            report.reportStep(step.getCurrentStep(), this->mBest, this->mPopulation);

            selection.select(this->mPopulation);
            this->mPopulation.crossover(crossoverScheme);
            this->mPopulation.mutate(mutationScheme);

            step.increase();
        }

        report.reportSummary(this->mNumberOfEvaluations, timer.getTime(), this->mBest);

        return this->mBest;
    }

private:
    EvolutionaryAlgorithm(void)
    {}

    Individual mBest;
    Evaluator* mpEvaluator;
    Population<ArgumentsType, MutationScheme<ArgumentsType>, CrossoverScheme<ArgumentsType> > mPopulation;
    int mNumberOfEvaluations;
    ArgumentsType callPoliciesArguments;

};


		}
	} // class EvolutionaryAlgorithm
} // namespace Optimizer


