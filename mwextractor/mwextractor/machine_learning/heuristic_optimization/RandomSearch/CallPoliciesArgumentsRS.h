#pragma once

#include <string>

#include "../BaseCallPoliciesArguments.h"
#include "../Exception/Exception.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace RandomSearch
		{


/**
* A class for call policies arguments used in random search algorithm. It holds the characteristic parameters for
* a call policies (also fields inherited from BaseCallPoliciesArguments).
*
* @see BaseCallPoliciesArguments
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class CallPoliciesArgumentsRS : public BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values.
    */
    CallPoliciesArgumentsRS(void);

    /**
    * The object destructor.
    */
    ~CallPoliciesArgumentsRS(void);

    /**
    * Reads the characteristic parameters from a .ini <a href="optimizer.cfg">file</a>
    * (section "random_search"). If one of the value (or key) is missing in file then method takes
    * default value for that key. Default values for keys are as follows:
    * <ul>
    * <li>steps = 10.</li>
    * </ul>
    *
    * @note See example in section "random_search" in config <a href="optimizer.cfg">file</a>.
    *
    * @param[in] rFileName The config file name.
    *
    * @see BaseCallPoliciesArguments
    */
    void readFromFile(const std::string& rFileName);

private:
    static const std::string SECTION;
    static const std::string STEPS_KEY;
}; // class CallPoliciesArgumentsRS


		}
	} // namespace RandomSearch
} // namespace Optimizer

