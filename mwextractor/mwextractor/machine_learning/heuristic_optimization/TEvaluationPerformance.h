#pragma once

#include <string>
#include <sstream>

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* TEvaluationPerformance is a template to hold evaluation measure. Class is used as a base class in concrete
* evaluation objects such as IntEvaluationPerformance and DoubleEvaluationPerformance.
*
* The TEvaluationPerformance object could be in two states. First is when evaluation is not set. Object is
* cleared and there is no possible to read a value of a measure. Second one is when a value of a measure is set.
*
* @tparam T A evaluation measure %data type.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename T>
class TEvaluationPerformance
{
public:
    /**
    * Creates cleared TEvaluationPerformance.
    */
    TEvaluationPerformance(void)
    {
        this->mCleared = true;
    }

    /**
    * Creates TEvaluationPerformance with given evaluation value.
    *
    * @param[in] evaluation The evaluation value.
    */
    TEvaluationPerformance(T evaluation)
    {
        this->setEvaluation(evaluation);
    }

    /**
    * The object destructor.
    */
    ~TEvaluationPerformance(void)
    {}

    /**
    * Sets evaluation measure.
    *
    * @param[in] evaluation The evaluation measure.
    */
    void setEvaluation(T evaluation)
    {
        this->mEvaluation = evaluation;
        this->mCleared = false;
    }

    /**
    * Returns evaluation measure.
    *
    * @return The evaluation measure.
    */
    T getEvaluation(void)
    {
        return this->mEvaluation;
    }

    /**
    * Determines if TEvaluationPerformance is cleared.
    *
    * @return <code>true</code> if TEvaluationPerformance is cleared, <code>false</code> otherwise.
    */
    bool isCleared(void)
    {
        return this->mCleared;
    }

    /**
    * Clears evaluation measure.
    */
    void clear(void)
    {
        this->mCleared = true;
    }

    /**
    * Converts this <code>this</code> object to its string representation.
    *
    * @return A string that describes this object.
    */
    std::string toString(void)
    {
        std::stringstream ret;
        ret<<"EvaluationPerformance[Cleared=";
        ret<<this->mCleared;
        ret<<"; Evaluation=";
        ret<<this->mEvaluation;
        ret<<"]";
        return ret.str();
    }

private:
    bool mCleared;
    T mEvaluation;
}; // class TEvaluationPerformance


	}
} // namespace Optimizer


