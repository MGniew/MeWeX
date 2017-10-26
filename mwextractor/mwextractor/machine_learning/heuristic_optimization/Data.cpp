
//#include <boost/test/test_tools.hpp>
#include <boost/algorithm/string.hpp>

#include "Data.h"

using std::string;
using std::stringstream;

namespace machine_learning
{
	namespace heuristic_optimization
	{


Data::Data(void)
{
    this->mType = VOID;
}

Data::Data(int value)
{
    this->set(value);
}

Data::Data(double value)
{
    this->set(value);
}

Data::~Data(void) throw()
{}

Data Data::operator+(const Data& rData)
{
    if(rData.getType() != this->getType())
    {
        throw Exception::Exception("Incompatible types.");
    }

    Data ret;
    switch(this->getType())
    {
    case INT:
    {
        int iThis=0, iData=0;
        this->get(iThis);
        rData.get(iData);
        ret.set(iThis+iData);
    }
    break;
    case DOUBLE:
    {
        double dThis=0, dData=0;
        this->get(dThis);
        rData.get(dData);
        ret.set(dThis+dData);
    }
    break;
    default:
        throw Exception::Exception("Cannot operate on variables of type \"void\".");
    }

    return ret;
}

Data Data::operator-(const Data& rData)
{
    if(rData.getType() != this->getType())
    {
        throw Exception::Exception("Incompatible types.");
    }

    Data ret;
    switch(this->getType())
    {
    case INT:
    {
        int iThis=0, iData=0;
        this->get(iThis);
        rData.get(iData);
        ret.set(iThis-iData);
    }
    break;
    case DOUBLE:
    {
        double dThis=0, dData=0;
        this->get(dThis);
        rData.get(dData);
        ret.set(dThis-dData);
    }
    break;
    default:
        throw Exception::Exception("Cannot operate on variables of type \"void\".");
    }

    return ret;
}

Data Data::operator*(const Data& rData)
{
    if(rData.getType() != this->getType())
    {
        throw Exception::Exception("Incompatible types.");
    }

    Data ret;
    switch(this->getType())
    {
    case INT:
    {
        int iThis=0, iData=0;
        this->get(iThis);
        rData.get(iData);
        ret.set(iThis*iData);
    }
    break;
    case DOUBLE:
    {
        double dThis=0, dData=0;
        this->get(dThis);
        rData.get(dData);
        ret.set(dThis*dData);
    }
    break;
    default:
        throw Exception::Exception("Cannot operate on variables of type \"void\".");
    }

    return ret;
}


bool Data::operator==(const Data& rData) const
{
    if(rData.getType() != this->getType())
    {
        throw Exception::Exception("Incompatible types.");
    }

    switch(this->getType())
    {
    case INT:
        return this->mInt == rData.mInt;
    case DOUBLE:
    	// return boost::test_tools::check_is_small(this->mDouble - rData.mDouble, static_cast<double>(PRECISION));
    	// http://www.boost.org/doc/libs/1_34_0/boost/test/floating_point_comparison.hpp
    	return std::abs(this->mDouble - rData.mDouble) < std::abs(static_cast<double>(PRECISION));
    default:
        throw Exception::Exception("Cannot operate on variables of type \"void\".");
    }
}

bool Data::operator<(const Data& rData) const
{
    if(rData.getType() != this->getType())
    {
        throw Exception::Exception("Incompatible types.");
    }

    switch(this->getType())
    {
    case INT:
        return this->mInt < rData.mInt;
    case DOUBLE:
        return this->mDouble < rData.mDouble;
    default:
        throw Exception::Exception("Cannot operate on variables of type \"void\".");
    }
}

bool Data::operator>(const Data& rData) const
{
    if(rData.getType() != this->getType())
    {
        throw Exception::Exception("Incompatible types.");
    }

    switch(this->getType())
    {
    case INT:
        return this->mInt > rData.mInt;
    case DOUBLE:
        return this->mDouble > rData.mDouble;
    default:
        throw Exception::Exception("Cannot operate on variables of type \"void\".");
    }
}

void Data::get(int& rRet) const
{
    if(this->mType == INT)
    {
        rRet = this->mInt;
    }
    else
    {
        rRet = this->mDouble;
    }
}

void Data::get(double& rRet) const
{
    if(this->mType == DOUBLE)
    {
        rRet = this->mDouble;
    }
    else
    {
        rRet = this->mInt;
    }
}

int Data::getType(void) const
{
    return this->mType;
}

void Data::set(int value)
{
    this->mInt = value;
    this->mType = INT;
}

void Data::set(double value)
{
    this->mDouble = value;
    this->mType = DOUBLE;
}

int Data::toType(const std::string& rType)
{
    if(boost::iequals(rType, "int") || boost::iequals(rType, "integer") || boost::iequals(rType, "i"))
    {
        return INT;
    }
    if(boost::iequals(rType, "double") || boost::iequals(rType, "d"))
    {
        return DOUBLE;
    }
    return VOID;
}

string Data::toString(void)
{
    stringstream strs;
    switch(this->mType)
    {
    case INT:
        strs<<this->mInt;
        break;
    case DOUBLE:
        strs<<this->mDouble;
        break;
    }
    return strs.str();
}

const float Data::PRECISION = 1e-9;


	}
}

