#pragma once

#include "ParticleSwarmOptimization.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{
	template<typename ArgumentsType,
	typename StepType,
	template<typename ArgumentsType, typename StepType> class StepCounter,
	typename TimeType,
	template<typename ArgumentsType, typename TimeType> class Timer,
	template<typename ArgumentsType, typename TimeType, typename StepType> class Report>
    /**
    * Solves the optimization problem. Result of optimization is saved in a file.
    */
    Point ParticleSwarmOptimization::start()
    {
        Timer<ArgumentsType, TimeType> timer(this->mCallPoliciesArguments);

        StepCounter<ArgumentsType, StepType> step(this->mCallPoliciesArguments);
        Report<ArgumentsType, TimeType, StepType> report(this->mCallPoliciesArguments);

        Point candidate = this->mBest;

        mpEvaluator->evaluate(this->mBest);
        this->mNumberOfEvaluations++;

        while(!step.isFinished())
        {
            candidate.setRandomParameters();
            mpEvaluator->evaluate(candidate);
            this->mNumberOfEvaluations++;

            if(candidate.getEvaluationPerformance().isGreater(this->mBest.getEvaluationPerformance()))
            {
                this->mBest = candidate;
            }

            report.reportStep(step.getCurrentStep(), candidate, this->mBest);
            step.increase();
        }

        report.reportSummary(this->mNumberOfEvaluations, timer.getTime(), this->mBest);

        return this->mBest;
    }

		} // namespace particle_swarm_optimization
	} // namespace heuristic_optimization
} // namespace machine_learning
