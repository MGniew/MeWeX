#include "CallPoliciesArgumentsHC.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace HillClimbing
		{


CallPoliciesArgumentsHC::CallPoliciesArgumentsHC(void) : BaseCallPoliciesArguments()
{
    this->mNeighbours = 3;
    this->mRadius = 1.0;
}

CallPoliciesArgumentsHC::~CallPoliciesArgumentsHC(void)
{}

void CallPoliciesArgumentsHC::readFromFile(const std::string& rFileName)
{
    CSimpleIniA configFile;
    SI_Error rc = configFile.LoadFile(rFileName.c_str());
    if(SI_OK != rc)
    {
        throw Exception::Exception("Could not load file \""+rFileName+"\".");
    }
    else
    {
        this->mSteps = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), STEPS_KEY.c_str(), 10));
        this->mNeighbours = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), NEIGHBOURS_KEY.c_str(), 3));
        this->mRadius = configFile.GetDoubleValue(SECTION.c_str(), RADIUS_KEY.c_str(), 1.0);
    }
}

unsigned int CallPoliciesArgumentsHC::getNeighbourhoodSize(void) const
{
    return this->mNeighbours;
}

void CallPoliciesArgumentsHC::setNeighbourhoodSize(unsigned int value)
{
    this->mNeighbours = value;
}

double CallPoliciesArgumentsHC::getRadius(void) const
{
    return this->mRadius;
}

void CallPoliciesArgumentsHC::setRadius(double value)
{
    this->mRadius = value;
}

const std::string CallPoliciesArgumentsHC::SECTION = "hill_climbing";
const std::string CallPoliciesArgumentsHC::STEPS_KEY = "steps";
const std::string CallPoliciesArgumentsHC::NEIGHBOURS_KEY = "neighbours";
const std::string CallPoliciesArgumentsHC::RADIUS_KEY = "radius";


		}
	}
}

