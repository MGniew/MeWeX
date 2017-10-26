#include "CallPoliciesArgumentsTS.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace TabuSearch
		{


CallPoliciesArgumentsTS::CallPoliciesArgumentsTS(void) : BaseCallPoliciesArguments()
{
    this->mNeighbours = 3;
    this->mTabu = 5;
    this->mRadius = 1.0;
}

CallPoliciesArgumentsTS::~CallPoliciesArgumentsTS(void)
{}

void CallPoliciesArgumentsTS::readFromFile(const std::string& rFileName)
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
        this->mTabu = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), TABU_KEY.c_str(), 5));
        this->mRadius = configFile.GetDoubleValue(SECTION.c_str(), RADIUS_KEY.c_str(), 1.0);
    }
}

unsigned int CallPoliciesArgumentsTS::getNeighbourhoodSize(void) const
{
    return this->mNeighbours;
}

unsigned int CallPoliciesArgumentsTS::getTabuListSize(void) const
{
    return this->mTabu;
}

double CallPoliciesArgumentsTS::getRadius(void) const
{
    return this->mRadius;
}

void CallPoliciesArgumentsTS::setNeighbourhoodSize(unsigned int value)
{
    this->mNeighbours = value;
}

void CallPoliciesArgumentsTS::setTabuListSize(unsigned int value)
{
    this->mTabu = value;
}

void CallPoliciesArgumentsTS::setRadius(double value)
{
    this->mRadius = value;
}

const std::string CallPoliciesArgumentsTS::SECTION = "tabu_search";
const std::string CallPoliciesArgumentsTS::STEPS_KEY = "steps";
const std::string CallPoliciesArgumentsTS::NEIGHBOURS_KEY = "neighbours";
const std::string CallPoliciesArgumentsTS::TABU_KEY = "tabu";
const std::string CallPoliciesArgumentsTS::RADIUS_KEY = "radius";


		}
	}
}
