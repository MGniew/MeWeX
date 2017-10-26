#pragma once

#include <string>
#include <vector>

#include "BaseParameter.h"
#include "BaseEvaluationPerformance.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* A Point contain parameters and evaluation result for optimization task. Class is potential solution of given
* problem.
*
* @see BaseParameter
* @see BaseEvaluationPerformance
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class Point
{
public:
    /**
    * Creates Point with empty parameters list and <code>NULL</code> evaluation performance.
    */
    Point(void);

    /**
    * A copy constructor.
    *
    * @param[in] rPoint	A reference to copied Point object.
    */
    Point(const Point& rPoint);

    /**
    * The object destructor.
    */
    ~Point(void);

    /**
    * The assignment operator.
    *
    * @param[in] rPoint	A reference to copied Point object.
    */
    Point& operator=(const Point& rPoint);

    /**
    * Determines if <code>this</code> and rPoint objects are equal.
    *
    * @param[in] rPoint
    *
    * @return <code>true</code> if objects are equal, <code>false</code> otherwise.
    */
    bool isEqual(const Point& rPoint);

    /**
    * Returns a parameter specified by the index. Index must be less than size of that vector.
    *
    * @param[in] index The parameter position in the parameter vector.
    *
    * @return The parameter object.
    *
    * @see getNumberOfParameters
    * @see BaseParameter
    * @see IntParameter
    * @see DoubleParameter
    */
    BaseParameter& getParameterAt(unsigned int index) const;

    /**
    * Inserts new parameter at the end of the parameter list.
    *
    * @param[in] rParameter The parameter being added.
    *
    * @see BaseParameter
    * @see IntParameter
    * @see DoubleParameter
    */
    void addParameter(const BaseParameter& rParameter);

    /**
    * Returns a evaluation measure as a evaluation performance.
    *
    * @return The evaluation performance.
    *
    * @see BaseEvaluationPerformance
    * @see IntEvaluationPerformance
    * @see DoubleEvaluationPerformance
    */
    BaseEvaluationPerformance& getEvaluationPerformance(void) const;

    /**
    * Sets a evaluation performance as a evaluation measure of <code>this</code> parameters.
    *
    * @param[in] rEvaluationPerformance
    *
    * @see BaseEvaluationPerformance
    * @see IntEvaluationPerformance
    * @see DoubleEvaluationPerformance
    */
    void setEvaluationPerformance(const BaseEvaluationPerformance& rEvaluationPerformance);

    /**
    * Sets a random value for all parameters.
    */
    void setRandomParameters(void);

    /**
    * Returns a number of the optimized parameters.
    *
    * @return A number of the optimized parameters.
    */
    unsigned int getNumberOfParameters(void) const;

    /**
    * Converts this <code>this</code> object to its string representation.
    *
    * @return A string that describes this object.
    */
    std::string toString(void) const;

protected:
    /**
    * The vector with the optimized parameters.
    *
    * @see BaseParameter
    * @see IntParameter
    * @see DoubleParameter
    */
    std::vector<BaseParameter*> mParameters;

    /**
    * The evaluation measure result.
    *
    * @see BaseEvaluationPerformance
    * @see IntEvaluationPerformance
    * @see DoubleEvaluationPerformance
    */
    BaseEvaluationPerformance* mpEvaluationPerformance;
}; // class Point


	}
} // namespace Optimizer


