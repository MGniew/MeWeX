#pragma once

#include "TEvaluationPerformance.h"
#include "BaseEvaluationPerformance.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* IntEvaluationPerformance stores evaluation measure. Class is a variant of the integer data type measure.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class IntEvaluationPerformance : protected TEvaluationPerformance<int>, public BaseEvaluationPerformance
{
public:
    /**
    * Creates cleared IntEvaluationPerformance.
    */
    IntEvaluationPerformance(void);

    /**
    * Creates IntEvaluationPerformance with given evaluation value.
    *
    * @param[in] evaluation The evaluation value.
    */
    IntEvaluationPerformance(int evaluation);

    /**
    * The object destructor.
    */
    virtual ~IntEvaluationPerformance(void) throw();

    /**
    * {@inheritDoc}
    */
    virtual bool isEqual(const BaseEvaluationPerformance& rEvaluationPerformance);

    /**
    * {@inheritDoc}
    */
    virtual bool isLess(const BaseEvaluationPerformance& rEvaluationPerformance);

    /**
    * {@inheritDoc}
    */
    virtual bool isGreater(const BaseEvaluationPerformance& rEvaluationPerformance);

    /**
    * {@inheritDoc}
    */
    virtual BaseEvaluationPerformance* duplicate(void) const;

    /**
    * Sets evaluation measure. A value of the measure is forwarded as a Data object with type <code>int</code>.
    *
    * @param[in] evaluation The evaluation measure.
    *
    * @see Data
    */
    virtual void setEvaluation(const Data& evaluation);

    /**
    * Returns evaluation measure. A value of the measure is returned as a Data object with type <code>int</code>.
    *
    * @return The evaluation measure.
    *
    * @see Data
    */
    virtual Data getEvaluation(void);

    /**
    * {@inheritDoc}
    */
    virtual void clear(void);

    /**
    * {@inheritDoc}
    */
    virtual std::string toString(void);
};


	}
}
