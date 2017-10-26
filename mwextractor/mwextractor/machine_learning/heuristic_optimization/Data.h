#pragma once

#include <string>
#include <sstream>

#include "Exception/Exception.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* Represents fundamental data types.
*/
enum TYPE
{
    VOID, /**< Void (empty), unsupported or unknown type. */
    INT, /**< Integer type. */
    DOUBLE /**< Real type. */
}; // enum TYPE

/**
* Data is a container storing integer or real variable. The class provides an interface for a basic arithmetic
* operations.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class Data
{
public:
    /**
    * Creates Data with type void. Object is empty, without a value.
    */
    Data(void);

    /**
    * Creates Data with given <code>int</code> value.
    *
    * @param[in] value The integer value.
    */
    Data(int value);

    /**
    * Creates Data with given <code>double</code> value.
    *
    * @param[in] value The real value.
    */
    Data(double value);

    /**
    * The object destructor.
    */
    ~Data(void) throw();

    /**
    * The addition operator. Returns sum of <code>this</code> and rData. Both objects must have the same type.
    *
    * @param[in] rData
    *
    * @return The sum.
    *
    * @exception Exception Thrown if one of Data objects is empty or if held types are different e.g. int and
    * double.
    */
    Data operator+(const Data& rData);

    /**
    * The subtraction operator. Returns difference of <code>this</code> and rData. Both objects must have the
    * same type.
    *
    * @param[in] rData
    *
    * @return The difference.
    *
    * @exception Exception Thrown if one of Data objects is empty or if held types are different e.g. int and
    * double.
    */
    Data operator-(const Data& rData);

    /**
    * The product operator. Returns product of <code>this</code> and rData. Both objects must have the same type.
    *
    * @param[in] rData
    *
    * @return The product.
    *
    * @exception Exception Thrown if one of Data objects is empty or if held types are different e.g. int and
    * double.
    */
    Data operator*(const Data& rData);

    /**
    * Determines if <code>this</code> and rData objects are equal.
    *
    * @param[in] rData
    *
    * @return <code>true</code> if objects are equal, <code>false</code> otherwise.
    *
    * @exception Exception Thrown if one of Data objects is empty or if held types are different e.g. int and
    * double.
    */
    bool operator==(const Data& rData) const;

    /**
    * Determines if <code>this</code> object is less than rData.
    *
    * @param[in] rData
    *
    * @return <code>true</code> if <code>this</code> object is less than rData, <code>false</code> otherwise.
    *
    * @exception Exception Thrown if one of Data objects is empty or if held types are different e.g. int and
    * double.
    */
    bool operator<(const Data& rData) const;

    /**
    * Determines if <code>this</code> object is greater than rData.
    *
    * @param[in] rData
    *
    * @return <code>true</code> if <code>this</code> object is greater than rData, <code>false</code> otherwise.
    *
    * @exception Exception Thrown if one of Data objects is empty or if held types are different e.g. int and
    * double.
    */
    bool operator>(const Data& rData) const;

    /**
    * Returns contained value.
    *
    * @param[out] rRet The output variable.
    */
    void get(int& rRet) const;

    /**
    * Returns contained value.
    *
    * @param[out] rRet The output variable.
    */
    void get(double& rRet) const;

    /**
    * Returns a type of contained value.
    *
    * @return %Data type described by #TYPE.
    *
    * @see TYPE
    */
    int getType(void) const;

    /**
    * Sets a integer value.
    *
    * @param[in] value The integer value.
    */
    void set(int value);

    /**
    * Sets a real value.
    *
    * @param[in] value The real value.
    */
    void set(double value);

    /**
    * Converts string to type value. For integer type, parameter rType could be one of: "int", "integer" or "i".
    * For real type, parameter rType could be one of: "double" or "d".
    *
    * @param rType A string with type.
    *
    * @return %Data type described by #TYPE.
    *
    * @see TYPE
    */
    static int toType(const std::string& rType);

    /**
    * Converts this <code>this</code> object to its string representation.
    *
    * @return A string that describes this object.
    */
    std::string toString(void);

private:
    int mType;
    int mInt;
    double mDouble;
    static const float PRECISION;
}; // class Data

/**
* The casting operator for extracting a value of a given type from a Data type.
*
* @tparam T A destination %data type.
*
* @param[in] rData A source %data.
*
* @return A copy of the value in rData.
*
* @exception Exception Thrown if cast from source type to destination type could not be done.
*
* @see Data
*/
template<typename T>
T dataCast(const Data& rData)
{
    switch(rData.getType())
    {
    case INT:
    {
        int ret;
        rData.get(ret);
        return static_cast<T>(ret);
    }
    case DOUBLE:
    {
        double ret;
        rData.get(ret);
        return static_cast<T>(ret);
    }
    default:
        throw Exception::Exception("Cannot cast from source type to destination type.");
    }
} // dataCast


	}
} // namespace Optimizer


