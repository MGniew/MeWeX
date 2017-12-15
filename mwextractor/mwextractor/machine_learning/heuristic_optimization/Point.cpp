#include "Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


Point::Point(void)
{
    this->mpEvaluationPerformance = NULL;
}

Point::Point(const Point& rPoint)
{
    mParameters.reserve(rPoint.mParameters.size());
    for(unsigned int i=0; i<rPoint.mParameters.size(); i++)
    {
        this->mParameters.push_back(rPoint.mParameters[i]->duplicate());
    }
    this->mpEvaluationPerformance = rPoint.mpEvaluationPerformance->duplicate();
}

Point::~Point(void)
{
    for(unsigned int i=0; i<this->mParameters.size(); i++)
    {
        delete this->mParameters[i];
    }
    delete this->mpEvaluationPerformance;
}


Point& Point::operator=(Point rPoint)
{
    mParameters.swap(rPoint.mParameters);
    delete this->mpEvaluationPerformance;
    this->mpEvaluationPerformance = rPoint.mpEvaluationPerformance->duplicate();
    return *this;
}

bool Point::isEqual(const Point& rPoint)
{
    unsigned int size = this->mParameters.size();
    for(unsigned int i=0; i<size; i++)
    {
        if(! this->mParameters[i]->isEqual(*rPoint.mParameters[i]))
        {
            return false;
        }
    }
    return true;
}

BaseParameter& Point::getParameterAt(unsigned int index) const
{
    return *this->mParameters[index];
}

void Point::addParameter(const BaseParameter& rParameter)
{
    this->mParameters.push_back(rParameter.duplicate());
}

BaseEvaluationPerformance& Point::getEvaluationPerformance(void) const
{
    return *this->mpEvaluationPerformance;
}

void  Point::setEvaluationPerformance(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    this->mpEvaluationPerformance = rEvaluationPerformance.duplicate();
}

void Point::setRandomParameters(void)
{
    unsigned int sizeParam;
    for(unsigned int i=0; i<this->mParameters.size(); i++)
    {
        sizeParam = this->mParameters[i]->getSize();
        for(unsigned int j=0; j<sizeParam; j++)
        {
            this->mParameters[i]->setRandomValue(j);
        }
    }
    this->mpEvaluationPerformance->clear();
}

unsigned int Point::getNumberOfParameters(void) const
{
    return this->mParameters.size();
}

std::string Point::toString(void) const
{
    std::string ret = "Point{Parameters{";
    if(this->mParameters.size() > 0)
    {
        ret += mParameters[0]->toString();
        for(unsigned int i=1; i<mParameters.size(); i++)
        {
            ret += "; ";
            ret += mParameters[i]->toString();
        }
    }
    ret += "}; ";
    if(NULL != this->mpEvaluationPerformance)
    {
        ret += this->mpEvaluationPerformance->toString();
    }
    else
    {
        ret += "EvaluationPerformance";
    }
    ret += "}";
    return ret;
}


	}
}
