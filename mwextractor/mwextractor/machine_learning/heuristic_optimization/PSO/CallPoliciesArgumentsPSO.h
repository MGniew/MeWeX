#pragma once

#include <string>

#include "../BaseCallPoliciesArguments.h"
#include "../Exception/Exception.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{


/**
* A class for call policies arguments used in random search algorithm. It holds the characteristic parameters for
* a call policies (also fields inherited from BaseCallPoliciesArguments).
*
* @see BaseCallPoliciesArguments
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class CallPoliciesArgumentsPSO : public BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values.
    */
    CallPoliciesArgumentsPSO(void);

    /**
    * The object destructor.
    */
    ~CallPoliciesArgumentsPSO(void);

    /**
    * Returns neighbourhood size.
    *
    * @return The neighbourhood size.
    */
    unsigned int getNeighbourhood(void) const;

     /**
    * Returns neighbourhood size.
    *
    * @return The neighbourhood size.
    */
    double getOmega(void) const;

     /**
    * Returns neighbourhood size.
    *
    * @return The neighbourhood size.
    */
    double getOmegaL(void) const;

    /**
    * Returns neighbourhood size.
    *
    * @return The neighbourhood size.
    */
    double getOmegaG(void) const;

    /**
    * Returns a value of the radius.
    *
    * @return The value of the radius.
    */
    unsigned int getSwarmSize(void) const;

    /**
    * Reads the characteristic parameters from a .ini <a href="optimizer.cfg">file</a>
    *
    * @param[in] rFileName The config file name.
    *
    * @see BaseCallPoliciesArguments
    */
    void readFromFile(const std::string& rFileName);

private:
    unsigned int mSwarmSize;
    double mOmega;
    double mOmegaL;
    double mOmegaG;
    unsigned int mNeighbourhood;

    static const std::string SECTION;
    static const std::string STEPS_KEY;
    static const std::string SWARM_SIZE_KEY;
    static const std::string OMEGA_KEY;
    static const std::string OMEGA_L_KEY;
    static const std::string OMEGA_G_KEY;
    static const std::string NEIGHBOURHOOD_KEY;
}; // class CallPoliciesArgumentsPSO


		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer

