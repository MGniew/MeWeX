#include "IntParameter.h"

using std::string;
using std::vector;


namespace machine_learning
{
	namespace heuristic_optimization
	{


IntParameter::IntParameter(void) : TParameter<int>()
{}

IntParameter::IntParameter(const string& rName,
                           const std::vector<int>& rMin,
                           const std::vector<int>& rMax,
                           const std::vector<int>& rParameter,
                           const std::vector<int>& rStep)
    : TParameter<int>(rName, rMin, rMax, rParameter, rStep)
{}

IntParameter::IntParameter(const IntParameter& rParameter) : TParameter<int>(rParameter)
{}

IntParameter& IntParameter::operator=(const IntParameter& rParameter)
{
    TParameter<int>::operator=(rParameter);
    return *this;
}

IntParameter::~IntParameter(void) throw()
{}

BaseParameter* IntParameter::duplicate(void) const
{
    return new IntParameter(*this);
}

void IntParameter::setRandomValue(unsigned int index, Random::Distribution dist)
{
    if(index<this->mParameter.size())
    {
        this->mParameter[index] = this->mStep[index]*(Random::random(this->mMin[index], this->mMax[index])/this->mStep[index]);
    }
}

bool IntParameter::isEqual(const BaseParameter& rParameter)
{
    const IntParameter* pParameter = dynamic_cast<const IntParameter*>(&rParameter);
    if(NULL == pParameter)
    {
        return false;
    }
    else
    {
        return this->TParameter<int>::isEqual(*pParameter);
    }
}

string IntParameter::getName(void)
{
    return TParameter<int>::getName();
}

Data IntParameter::getValueAt(unsigned int index)
{
    Data ret;
    ret.set(TParameter<int>::getParameterAt(index));
    return ret;
}

void IntParameter::setValueAt(unsigned int index, const Data& rData)
{
    int value;
    rData.get(value);
    TParameter<int>::setParameterAt(index, value);
}

unsigned int IntParameter::getSize(void) const
{
    return TParameter<int>::getSize();
}

string IntParameter::toString(void)
{
    return TParameter<int>::str();
}


	}
}

