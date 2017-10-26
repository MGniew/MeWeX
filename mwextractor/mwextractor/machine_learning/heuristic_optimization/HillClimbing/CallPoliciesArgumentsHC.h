#pragma once

#include <string>

#include "../BaseCallPoliciesArguments.h"
#include "../Exception/Exception.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace HillClimbing
		{


/**
* A class for call policies arguments used in hill climbing algorithm. It holds the characteristic parameters
* for a call policies (also fields inherited from BaseCallPoliciesArguments): a neighbourhood size, a radius of
* the hypersphere neighbourhood.
*
* @see BaseCallPoliciesArguments
* @see Neighbourhood
* @see HypersphereNeighbourhood
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class CallPoliciesArgumentsHC : public BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values:
    * <ul>
    * <li>neighbourhood size = 3,</li>
    * <li>radius = 1.0.</li>
    * </ul>
    */
    CallPoliciesArgumentsHC(void);

    /**
    * The object destructor.
    */
    ~CallPoliciesArgumentsHC(void);

    /**
    * Reads the characteristic parameters from a .ini <a href="optimizer.cfg">file</a>
    * (section "hill_climbing"). If one of the value (or key) is missing in file then method takes
    * default value for that key. Default values for keys are as follows:
    * <ul>
    * <li>steps = 10,</li>
    * <li>neighbours = 3,</li>
    * <li>radius = 1.0.</li>
    * </ul>
    *
    * @note See example in section "hill_climbing" in config <a href="optimizer.cfg">file</a>.
    *
    * @param[in] rFileName The config file name.
    *
    * @see BaseCallPoliciesArguments
    * @see HypersphereNeighbourhood
    * @see Neighbourhood
    */
    void readFromFile(const std::string& rFileName);

    /**
    * Returns neighbourhood size.
    *
    * @return The neighbourhood size.
    */
    unsigned int getNeighbourhoodSize(void) const;

    /**
    * Sets neighbourhood size.
    *
    * @param[in] value The neighbourhood size.
    */
    void setNeighbourhoodSize(unsigned int value);

    /**
    * Returns a value of the radius.
    *
    * @return The value of the radius.
    */
    double getRadius(void) const;

    /**
    * Sets a value of the radius.
    *
    * @param[in] value The value of the radius.
    */
    void setRadius(double value);

private:
    unsigned int mNeighbours;
    double mRadius;

    static const std::string SECTION;
    static const std::string STEPS_KEY;
    static const std::string NEIGHBOURS_KEY;
    static const std::string RADIUS_KEY;
}; // class CallPoliciesArgumentsHC


		}
	} // HillClimbing
} // namespace Optimizer
