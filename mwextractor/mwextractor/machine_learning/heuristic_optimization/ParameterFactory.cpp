#include "ParameterFactory.h"

using std::string;
using std::vector;


namespace machine_learning
{
	namespace heuristic_optimization
	{


ParameterFactory::ParameterFactory(void)
{}

ParameterFactory::~ParameterFactory(void)
{}

BaseParameter* ParameterFactory::create(int type, const string& rName,
                                        const string& rMin,
                                        const string& rMax,
                                        const string& rDefault,
                                        const string& rStep)
{
    switch(type)
    {
    case INT:
    {
        vector<int> minVec, maxVec, defaultVec, stepVec;
        minVec = toVector<int>(rMin);
        maxVec = toVector<int>(rMax);
        defaultVec = toVector<int>(rDefault);
        stepVec = toVector<int>(rStep);
        unsigned int defaultSize = defaultVec.size();
        if((minVec.size() != defaultSize) || (maxVec.size() != defaultSize) || (stepVec.size() != defaultSize))
        {
            throw std::length_error(" ");
        }
        return new IntParameter(rName, minVec, maxVec, defaultVec, stepVec);
    }
    case DOUBLE:
    {
        vector<double> minVec, maxVec, defaultVec, stepVec;
        minVec = toVector<double>(rMin);
        maxVec = toVector<double>(rMax);
        defaultVec = toVector<double>(rDefault);
        stepVec = toVector<double>(rStep);
        unsigned int defaultSize = defaultVec.size();
        if((minVec.size() != defaultSize) || (maxVec.size() != defaultSize) || (stepVec.size() != defaultSize))
        {
            throw std::length_error(" ");
        }
        return new DoubleParameter(rName, minVec, maxVec, defaultVec, stepVec);
    }
    default:
        return NULL;
    }
}


	}
}
