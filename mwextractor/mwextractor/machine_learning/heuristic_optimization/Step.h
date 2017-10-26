#pragma once

#include <cmath>

#include <boost/type_traits/is_floating_point.hpp>


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* Step is the class template for counting steps of algorithm. The class determines stop condition.
*
* @param ArgumentsType A call policy argument type.
* @param StepType A step type. Could be int, double, etc.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename StepType = unsigned int>
class Step
{
public:
    /**
    *
    */
    Step(void)
    {}

    /**
    * Creates Step with start step returned by rArgs.getStartStep() and maximum step returned by rArgs.getSteps().
    *
    * @param[in] rArgs Argument object.
    */
    Step(const ArgumentsType& rArgs)
    {
        this->mStep = rArgs.getStartStep();
        this->mMaxSteps = rArgs.getSteps();
    }

    /**
    * The object destructor.
    */
    ~Step(void) {}

    /**
    * Increases the current step.
    */
    void increase(void)
    {
        if(this->mStep < this->mMaxSteps)
        {
            this->mStep++;
        }
    }

    /**
    * Determines if the algorithm is finished. Algorithm is finished if current step is equal with the number of
    * the total algorithm steps.
    *
    * @return <code>true</code> if the algorithm is finished; <code>false</code> otherwise.
    */
    bool isFinished(void) const
    {
        if(boost::is_floating_point<StepType>::value)
        {
            return fabs(this->mStep - this->mMaxSteps) < Step::PREC;
        }
        else
        {
            return this->mStep == this->mMaxSteps;
        }
    }

    /**
    * Returns the value of the current step.
    *
    * @return The value of the current step.
    */
    StepType getCurrentStep(void) const
    {
        return this->mStep;
    }

    /**
    * Returns the value of the total algorithm steps.
    *
    * @return The total algorithm steps.
    */
    StepType getMaxStep(void) const
    {
        return this->mMaxSteps;
    }

    /**
    * Sets the total algorithm steps.
    *
    * @param[in] rStep	The total algorithm steps.
    */
    void setMaxStep(const StepType& rStep)
    {
        this->mMaxSteps = rStep;
    }

private:
    StepType mMaxSteps;
    StepType mStep;
    static const double PREC;
}; // class Step

template<typename ArgumentsType, typename StepType> const double Step<ArgumentsType, StepType>::PREC = 0.000001;


	}
} // namespace Optimizer


