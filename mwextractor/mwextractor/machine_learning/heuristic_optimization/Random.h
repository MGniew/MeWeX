#pragma once

#include <ctime>
#include <cstdlib>


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* Random is a helper class providing method to generate random numbers.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class Random
{
public:
    Random(void);

    ~Random(void);

    /**
    * Returns random number from the range [0, 1].
    *
#endif // INT_EVALUATION_PERFORMANCE_H

    *
    * @return The random number.
    */
    static double random(void);

    /**
    * Returns random number from the range [<code>minValue</code>, <code>maxValue</code>].
    *
    * @tparam T A data type of random number.
    *
    * @param[in] minValue The lower limit of the returned value.
    * @param[in] maxValue The upper limit of the returned value.
    *
    * @return The random number.
    */
    template<typename T>
    static T random(const T& minValue, const T& maxValue)
    {
        if(minValue >= maxValue)
        {
            return minValue;
        }
        else
        {
            return minValue+((maxValue - minValue)*Random::random());
        }
    }

private:
    static time_t been;
}; // class Random


	}
} // namespace Optimizer


