#include "DoubleParameter.h"

using std::string;
using std::vector;

namespace machine_learning
{
	namespace heuristic_optimization
	{


DoubleParameter::DoubleParameter(void) : TParameter<double>()
{}

DoubleParameter::DoubleParameter(const string& rName,
                                 const vector<double>& rMin,
                                 const vector<double>& rMax,
                                 const vector<double>& rParameter,
                                 const vector<double>& rStep)
    : TParameter<double>(rName, rMin, rMax, rParameter, rStep)
{}

DoubleParameter::DoubleParameter(const DoubleParameter& rParameter) : TParameter<double>(rParameter)
{}

DoubleParameter& DoubleParameter::operator=(const DoubleParameter& rParameter)
{
    this->TParameter<double>::operator=(rParameter);
    return *this;
}

DoubleParameter::~DoubleParameter(void) throw()
{}

BaseParameter* DoubleParameter::duplicate(void) const
{
    return new DoubleParameter(*this);
}

void DoubleParameter::setRandomValue(unsigned int index)
{
    if(index<this->mParameter.size())
    {
        this->mParameter[index] = this->mStep[index]*((int)(Random::random(this->mMin[index], this->mMax[index])/this->mStep[index]));
    }
}

bool DoubleParameter::isEqual(const BaseParameter& rParameter)
{
    const DoubleParameter* pParameter = dynamic_cast<const DoubleParameter*>(&rParameter);
    if(NULL == pParameter)
    {
        return false;
    }
    else
    {
        return this->TParameter<double>::isEqual(*pParameter);
    }
}

string DoubleParameter::getName(void)
{
    return TParameter<double>::getName();
}

Data DoubleParameter::getValueAt(unsigned int index)
{
    Data ret;
    ret.set(TParameter<double>::getParameterAt(index));
    return ret;
}

void DoubleParameter::setValueAt(unsigned int index, const Data& rData)
{
    double value;
    rData.get(value);
    TParameter<double>::setParameterAt(index, value);
}

unsigned int DoubleParameter::getSize(void) const
{
    return TParameter<double>::getSize();
}

string DoubleParameter::toString(void)
{
    return TParameter<double>::str();
}


	}
}
