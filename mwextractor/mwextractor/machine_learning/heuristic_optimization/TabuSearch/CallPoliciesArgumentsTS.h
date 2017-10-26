#pragma once

#include <string>

#include "../BaseCallPoliciesArguments.h"
#include "../Exception/Exception.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace TabuSearch
		{


/**
* A class for call policies arguments used in tabu search algorithm. It holds the characteristic parameters for
* a call policies (also fields inherited from BaseCallPoliciesArguments): neighbourhood size, tabu list size, a
* radius of the hypersphere neighbourhood.
*
* @see BaseCallPoliciesArguments
* @see NeighbourhoodTS
* @see HypersphereNeighbourhood
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class CallPoliciesArgumentsTS : public BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values:
    * <ul>
    * <li>neighbourhood size = 3,</li>
    * <li>tabu list size = 5,</li>
    * <li>radius = 1.0.</li>
    * </ul>
    */
    CallPoliciesArgumentsTS(void);

    /**
    * The object destructor.
    */
    ~CallPoliciesArgumentsTS(void);

    /**
    * Reads the characteristic parameters from a .ini <a href="optimizer.cfg">file</a>
    * (section "tabu_search"). If one of the value (or key) is missing in file then method takes
    * default value for that key. Default values for keys are as follows:
    * <ul>
    * <li>steps = 10,</li>
    * <li>neighbours = 3,</li>
    * <li>tabu = 5,</li>
    * <li>radius = 1.0.</li>
    * </ul>
    *
    * @note See example in section "tabu_search" in config <a href="optimizer.cfg">file</a>.
    *
    * @param[in] rFileName The config file name.
    *
    * @see BaseCallPoliciesArguments
    * @see HypersphereNeighbourhood
    * @see NeighbourhoodTS
    */
    void readFromFile(const std::string& rFileName);

    /**
    * Returns neighbourhood size.
    *
    * @return The neighbourhood size.
    */
    unsigned int getNeighbourhoodSize(void) const;

    /**
    * Returns tabu list size.
    *
    * @return The tabu list size.
    */
    unsigned int getTabuListSize(void) const;

    /**
    * Returns a value of the radius.
    *
    * @return The value of the radius.
    */
    double getRadius(void) const;

    /**
    * Sets neighbourhood size.
    *
    * @param[in] value The neighbourhood size.
    */
    void setNeighbourhoodSize(unsigned int value);

    /**
    * Sets tabu list size.
    *
    * @param[in] value The tabu list size.
    */
    void setTabuListSize(unsigned int value);

    /**
    * Sets a value of the radius.
    *
    * @param[in] value The value of the radius.
    */
    void setRadius(double value);

private:
    unsigned int mNeighbours;
    unsigned int mTabu;
    double mRadius;

    static const std::string SECTION;
    static const std::string STEPS_KEY;
    static const std::string NEIGHBOURS_KEY;
    static const std::string TABU_KEY;
    static const std::string RADIUS_KEY;
}; // class CallPoliciesArgumentsTS


		}
	} // namespace TabuSearch
} // namespace Optimizer

