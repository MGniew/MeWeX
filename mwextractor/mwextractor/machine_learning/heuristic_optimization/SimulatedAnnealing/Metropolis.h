#pragma once

#include <cmath>

#include "../Random.h"
#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace SimulatedAnnealing
		{


/**
* The Metropolis selection rule used in simulated annealing algorithm.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TemperatureType A temperature data type.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename TemperatureType>
class Metropolis
{
public:
    /**
    * Creates Metropolis.
    */
    Metropolis(void)
    {}

    /**
    * Creates Metropolis.
    *
    * @param[in] rArgs Parameter is ignored.
    */
    Metropolis(const ArgumentsType& rArgs)
    {}

    /**
    * Determines if rCandidate could replace rCurrent point.
    *
    * @param[in] rTemperature The temperature in actual step.
    * @param[in] rCurrent The current point.
    * @param[in] rCandidate The candidate point.
    *
    * @return <code>true</code> if <code>rCandidate</code> replaces <code>rCurrent</code> point; <code>false</code> otherwise.
    */
    bool accept(const TemperatureType& rTemperature, const Point& rCurrent, const Point& rCandidate)
    {
        double p;
        if(rCandidate.getEvaluationPerformance().isGreater(rCurrent.getEvaluationPerformance()))
        {
            return true;
        }
        else
        {
            double evalDiv = dataCast<double>(rCurrent.getEvaluationPerformance().getEvaluation()-rCandidate.getEvaluationPerformance().getEvaluation());
            p = exp((0.0-fabs(evalDiv))/rTemperature);
            double pr = Random::random();
            return p>pr;
        }
    }
}; // class Metropolis


		}
	} // namespace SimulatedAnnealing
} // namespace Optimizer


