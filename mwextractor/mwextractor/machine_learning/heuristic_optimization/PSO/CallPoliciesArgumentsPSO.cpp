#include "CallPoliciesArgumentsPSO.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{


CallPoliciesArgumentsPSO::CallPoliciesArgumentsPSO(void) : BaseCallPoliciesArguments()
{;}

CallPoliciesArgumentsPSO::~CallPoliciesArgumentsPSO(void)
{;}

unsigned int CallPoliciesArgumentsPSO::getSwarmSize(void) const
{
    return mSwarmSize;
}

double CallPoliciesArgumentsPSO::getOmega(void) const
{
    return mOmega;
}

double CallPoliciesArgumentsPSO::getOmegaL(void) const
{
    return mOmegaL;
}

double CallPoliciesArgumentsPSO::getOmegaG(void) const
{
    return mOmegaG;
}

void CallPoliciesArgumentsPSO::readFromFile(const std::string& rFileName)
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
        this->mNeighbourhood = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), NEIGHBOURHOOD_KEY.c_str(), 1));
        this->mSwarmSize = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), SWARM_SIZE_KEY.c_str(), 5));
        this->mOmega = static_cast<double>(configFile.GetDoubleValue(SECTION.c_str(), OMEGA_KEY.c_str()));
        this->mOmegaL = static_cast<double>(configFile.GetDoubleValue(SECTION.c_str(), OMEGA_L_KEY.c_str()));
        this->mOmegaG = static_cast<double>(configFile.GetDoubleValue(SECTION.c_str(), OMEGA_G_KEY.c_str()));
    }
}

const std::string CallPoliciesArgumentsPSO::SECTION = "particle_swarm_optimization";
const std::string CallPoliciesArgumentsPSO::STEPS_KEY = "steps";
const std::string CallPoliciesArgumentsPSO::SWARM_SIZE_KEY = "swarm_size";
const std::string CallPoliciesArgumentsPSO::NEIGHBOURHOOD_KEY = "neighbourhood";
const std::string CallPoliciesArgumentsPSO::OMEGA_KEY = "omega";
const std::string CallPoliciesArgumentsPSO::OMEGA_L_KEY = "omega_l";
const std::string CallPoliciesArgumentsPSO::OMEGA_G_KEY = "omega_g";


		}
	}
}
