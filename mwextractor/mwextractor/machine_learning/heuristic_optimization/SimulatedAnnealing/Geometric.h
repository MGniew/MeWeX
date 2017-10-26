#pragma once

#include <cmath>

#include "../Optimizer.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace SimulatedAnnealing
		{


/**
* A geometric scheme of the temperature used in simulated annealing algorithm. Temperature is given by the
* equation: <code>a^k</code>. Where <code>a</code> is the constant base, <code>k</code> is the algorithm step.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam StepType A algorithm step type.
* @tparam TemperatuerType A temperature data type.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename StepType, typename TemperatuerType = double>
class Geometric
{
public:
    /**
    * Creates Geometric with base = 0.5.
    */
    Geometric(void)
    {
        this->setBase(0.5);
    }

    /**
    * Creates object with base returned by rArgs.getBase().
    *
    * @param rArgs The argument object.
    */
    Geometric(const ArgumentsType& rArgs)
    {
        this->setBase(rArgs.getBase());
    }

    /**
    * Returns the temperature value.
    *
    * @param[in] rStep The current step of the algorithm.
    *
    * @return The temperature value.
    */
    TemperatuerType getTemperature(const StepType& rStep) const
    {
        return pow(this->mBase, rStep);
    }

    /**
    * Returns the value of the base. The value is in the range <0.000001, 0.999999>.
    *
    * @return The value of the base.
    */
    TemperatuerType getBase(void) const
    {
        return this->mBase;
    }

    /**
    * Sets the value of the base. The value should be in the range <0.000001, 0.999999>.
    * The method sets 0.000001 if value is less than lower limit.
    *
    * param[in] value The value of the base.
    */
    void setBase(double value)
    {
        this->mBase = trimValue(value, MIN_BASE, MAX_BASE);
    }

private:
    double mBase;
    static const double MIN_BASE;
    static const double MAX_BASE;
}; // class Geometric

template<typename ArgumentsType, typename StepType, typename TemperatuerType> const double Geometric<ArgumentsType, StepType, TemperatuerType>::MIN_BASE = 0.000001;
template<typename ArgumentsType, typename StepType, typename TemperatuerType> const double Geometric<ArgumentsType, StepType, TemperatuerType>::MAX_BASE = 0.999999;


		}
	} // namespace SimulatedAnnealing
} // namespace Optimizer
