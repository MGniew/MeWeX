#pragma once

#include <string>

#include "SimpleIni/SimpleIni.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* A base class for call policies arguments. It holds the characteristic parameters for a call policies, such as:
* start and maximum steps of algorithm, report file name.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values:
    * <ul>
    * <li>start step = 0,</li>
    * <li>maximum steps = 10,</li>
    * <li>report file name = "report.txt".</li>
    * </ul>
    */
    BaseCallPoliciesArguments(void);

    /**
    * An object destructor.
    */
    ~BaseCallPoliciesArguments(void);

    /**
    * Returns a value of start step. This is the value of the beginning algorithm step.
    *
    * @return Value of start step.
    */
    unsigned int getStartStep(void) const;

    /**
    * Returns a value of maximum step. This is the value of the last algorithm step.
    *
    * @return Value of maximum step.
    */
    unsigned int getSteps(void) const;

    /**
    * Returns a report file name. The optimization results are saved to this file.
    *
    * @return The report file name.
    */
    std::string getReportFileName(void) const;

    /**
    * Returns a name of the optimization task.
    *
    * @return A name of the optimization task.
    */
    std::string getTargetName(void) const;

    /**
    * Sets a value of start step. This is the value of the beginning algorithm step.
    *
    * @param[in] value Value of start step.
    */
    void setStartStep(unsigned int value);

    /**
    * Sets a value of maximum step. This is the value of the last algorithm step.
    *
    * @param[in] value Value of maximum step.
    */
    void setSteps(unsigned int value);

    /**
    * Sets a report file name. The optimization results are saved to this file.
    *
    * @param[in] rFileName The report file name.
    */
    void setReportFileName(const std::string& rFileName);

    /**
    * Sets a name of the optimization task.
    *
    * @param[in] rTargetName A name of the optimization task.
    */
    void setTargetName(const std::string& rTargetName);

protected:
    /**
    * The value of start step.
    */
    unsigned int mStartStep;

    /**
    * The value of maximum step.
    */
    unsigned int mSteps;

    /**
    * The report file name.
    */
    std::string mReportFileName;

    /**
    * The name of the optimization task.
    */
    std::string mTargetName;

}; // class BaseCallPoliciesArguments

	}
}
