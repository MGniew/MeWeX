#pragma once

#include <vector>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Data.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* Trim value.
*
* @tparam T A data type of trimed value.
*
* @param value The value to trim.
* @param minValue The minimum limit of trimmed value.
* @param maxValue The maximum limit of trimmed value.
*
* @return <code>value</code> if <code>minValue < value < maxValue</code>, otherwise: <code>minValue</code> if
* <code>value < minValue</code> or <code>maxValue</code> if <code>value > maxValue</code>
*/
template<typename T>
T trimValue(T value, T minValue, T maxValue)
{
    if(value<maxValue)
    {
        if(value>minValue)
        {
            return value;
        }
        else
        {
            return minValue;
        }
    }
    else
    {
        return maxValue;
    }
}

/**
* Converts string including array of number to a vector. The string has following format: [x0,...,xn].
* As can be see a array is represented as sequence of comma separated numbers e.g [1,8,6,10].
*
* @tparam T A data type of the vectors fields.
*
* @param[in] rString A string including array.
*
* @return A vector of the number.
*/
template<typename ArgT>
std::vector<ArgT> toVector(const std::string& rString)
{
    std::vector<ArgT> ret;
    std::string copyStr = rString;
    boost::algorithm::trim(copyStr);
    if(('[' == copyStr[0]) && (']' == copyStr[copyStr.size()-1]))
    {
        boost::algorithm::trim_left_if(copyStr, boost::is_any_of("["));
        boost::algorithm::trim_right_if(copyStr, boost::is_any_of("]"));

        std::vector<std::string> tokens;
        boost::algorithm::split(tokens, copyStr, boost::is_any_of(","));
        for(unsigned int i=0; i<tokens.size(); i++)
        {
            boost::algorithm::trim(tokens[i]);
            ret.push_back(boost::lexical_cast<ArgT>(tokens[i]));

        }
    }
    else
    {
        ret.push_back(boost::lexical_cast<ArgT>(copyStr));
    }
    return ret;
}


	}
}

