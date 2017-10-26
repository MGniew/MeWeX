#include "CallPoliciesArgumentsSA.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace SimulatedAnnealing
		{


CallPoliciesArgumentsSA::CallPoliciesArgumentsSA(void) : BaseCallPoliciesArguments()
{
    this->mBase = 0.5;
    this->mRadius = 1.0;
}

CallPoliciesArgumentsSA::~CallPoliciesArgumentsSA(void)
{}

void CallPoliciesArgumentsSA::readFromFile(const std::string& rFileName)
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
        this->mBase = configFile.GetDoubleValue(SECTION.c_str(), BASE_KEY.c_str(), 0.5);
        this->mRadius = configFile.GetDoubleValue(SECTION.c_str(), RADIUS_KEY.c_str(), 1.0);
    }
}

double CallPoliciesArgumentsSA::getRadius(void) const
{
    return this->mRadius;
}

void CallPoliciesArgumentsSA::setRadius(double value)
{
    this->mRadius = value;
}


double CallPoliciesArgumentsSA::getBase(void) const
{
    return this->mBase;
}


void CallPoliciesArgumentsSA::setBase(double value)
{
    this->mBase = value;
}

const std::string CallPoliciesArgumentsSA::SECTION = "simulated_annealing";
const std::string CallPoliciesArgumentsSA::STEPS_KEY = "steps";
const std::string CallPoliciesArgumentsSA::BASE_KEY = "base";
const std::string CallPoliciesArgumentsSA::RADIUS_KEY = "radius";


		}
	}
}
