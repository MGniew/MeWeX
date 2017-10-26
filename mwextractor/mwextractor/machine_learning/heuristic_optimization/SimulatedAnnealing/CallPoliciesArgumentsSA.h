#pragma once

#include <string>

#include "../BaseCallPoliciesArguments.h"
#include "../Exception/Exception.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace SimulatedAnnealing
		{


/**
* A class for call policies arguments used in simulated annealing algorithm. It holds the characteristic
* parameters for a call policies (also fields inherited from BaseCallPoliciesArguments): base in geometric
* temperature scheme, a radius of the hypersphere neighbourhood.
*
* @see BaseCallPoliciesArguments
* @see Geometric
* @see HypersphereNeighbourhood
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class CallPoliciesArgumentsSA : public BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values:
    * <ul>
    * <li>base = 0.5,</li>
    * <li>radius = 1.0.</li>
    * </ul>
    */
    CallPoliciesArgumentsSA(void);

    /**
    * The object destructor.
    */
    ~CallPoliciesArgumentsSA(void);

    /**
    * Reads the characteristic parameters from a .ini <a href="optimizer.cfg">file</a>
    * (section "simulated_annealing"). If one of the value (or key) is missing in file then method takes
    * default value for that key. Default values for keys are as follows:
    * <ul>
    * <li>steps = 10,</li>
    * <li>base = 0.5,</li>
    * <li>radius = 1.0.</li>
    * </ul>
    *
    * @note See example in section "simulated_annealing" in config <a href="optimizer.cfg">file</a>.
    *
    * @param[in] rFileName The config file name.
    *
    * @see BaseCallPoliciesArguments
    * @see HypersphereNeighbourhood
    */
    void readFromFile(const std::string& rFileName);

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

    /**
    * Returns base used in geometric temperature scheme.
    *
    * @return The base (0, 1).
    *
    * @see Geometric
    */
    double getBase(void) const;

    /**
    * Sets base used in geometric temperature scheme.
    *
    * @param[in] value The base (0, 1).
    *
    * @see Geometric
    */
    void setBase(double value);

private:
    double mRadius;
    double mBase;

    static const std::string SECTION;
    static const std::string STEPS_KEY;
    static const std::string BASE_KEY;
    static const std::string RADIUS_KEY;
}; // class CallPoliciesArgumentsSA


		}
	} // namespace SimulatedAnnealing
} // namespace Optimizer
