#pragma once

#include "Data.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* A base evaluation performance class. It is an interface for a class that stores evaluation measure.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class BaseEvaluationPerformance
{
public:
	virtual ~BaseEvaluationPerformance() = default;

    /**
    * Determines if <code>this</code> and rEvaluationPerformance objects are equal.
    *
    * @param[in] rEvaluationPerformance
    *
    * @return <code>true</code> if objects are equal, <code>false</code> otherwise.
    */
    virtual bool isEqual(const BaseEvaluationPerformance& rEvaluationPerformance) = 0;

    /**
    * Determines if <code>this</code> evaluation is less than rEvaluationPerformance evaluation.
    *
    * @param[in] rEvaluationPerformance
    *
    * @return <code>true</code> if <code>this</code> is less, <code>false</code> otherwise.
    */
    virtual bool isLess(const BaseEvaluationPerformance& rEvaluationPerformance) = 0;

    /**
    * Determines if <code>this</code> evaluation is greater than rEvaluationPerformance evaluation.
    *
    * @param[in] rEvaluationPerformance
    *
    * @return <code>true</code> if <code>this</code> is greater, <code>false</code> otherwise.
    */
    virtual bool isGreater(const BaseEvaluationPerformance& rEvaluationPerformance) = 0;

    /**
    * Returns deep copy of <code>this</code> object.
    *
    * @return A deep copy of object.
    */
    virtual BaseEvaluationPerformance* duplicate(void) const = 0;

    /**
    * Sets evaluation measure. A value of the measure is forwarded as a Data object.
    *
    * @param[in] evaluation The evaluation measure.
    *
    * @see Data
    */
    virtual void setEvaluation(const Data& evaluation) = 0;

    /**
    * Returns evaluation measure. A value of the measure is returned as a Data object.
    *
    * @return The evaluation measure.
    *
    * @see Data
    */
    virtual Data getEvaluation(void) = 0;

    /**
    * Clears evaluation measure.
    */
    virtual void clear(void) = 0;

    /**
    * Converts this <code>this</code> object to its string representation.
    *
    * @return A string that describes this object.
    */
    virtual std::string toString(void) = 0;
}; // class BaseEvaluationPerformance


	}
} // namespace Optimizer
