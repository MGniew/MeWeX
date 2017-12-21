#pragma once

#include <string>

#include "Data.h"
#include "Random.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* A base parameter class. It is an interface for a class that represents a optimized parameter. The Parameter is
* represented as an array. A non-structural parameter is represented as a one field array. There is also possible
* to hold a few parameters or a structural parameter in one class. Then each parameter will be represented by a
* single array field.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class BaseParameter
{
public:
	virtual ~BaseParameter() = default;

    /**
    * Returns deep copy of <code>this</code> object.
    *
    * @return A deep copy of object.
    */
    virtual BaseParameter* duplicate(void) const = 0;

    /**
    * Sets random value for a parameter given by index.
    *
    * @param[in] index Index of a parameter.
    */
    virtual void setRandomValue(unsigned int index, Random::Distribution dist = Random::Distribution::UNIFORM) = 0;

    /**
    * Determines if <code>this</code> and rParameter objects are equal.
    *
    * @param[in] rParameter
    *
    * @return <code>true</code> if objects are equal, <code>false</code> otherwise.
    */
    virtual bool isEqual(const BaseParameter& rParameter) = 0;

    /**
    * Returns a string identifier of the parameter. This is the name of the parameter e.g. "alfa".
    *
    * @return The name of the parameter.
    */
    virtual std::string getName(void) = 0;

    /**
    * Returns a value of the parameter given by index. This index indicates to a parameter in array.
    *
    * @param[in] index Index of the parameter.
    *
    * @return A value of the parameter.
    *
    * @see setValueAt
    * @see Data
    */
    virtual Data getValueAt(unsigned int index) = 0;

    /**
    * Sets a value of the parameter given by index. This index indicates to a parameter in array.
    *
    * @param[in] index Index of the parameter.
    * @param[in] rData A value of the parameter.
    *
    * @see setValueAt
    * @see Data
    */
    virtual void setValueAt(unsigned int index, const Data& rData) = 0;

    /**
    * Returns size of the parameters array.
    *
    * @return The size of the parameters array.
    */
    virtual unsigned int getSize(void) const = 0;

    /**
    * Converts this <code>this</code> object to its string representation.
    *
    * @return A string that describes this object.
    */
    virtual std::string toString(void) = 0;
}; // class BaseParameter


	}
} // namespace Optimizer
