#include "CallPoliciesArgumentsPSO.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimalization
		{


CallPoliciesArgumentsPSO::CallPoliciesArgumentsPSO(void) : BaseCallPoliciesArguments()
{;}

CallPoliciesArgumentsPSO::~CallPoliciesArgumentsPSO(void)
{;}

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
    }
}

const std::string CallPoliciesArgumentsPSO::SECTION = "random_search";
const std::string CallPoliciesArgumentsPSO::STEPS_KEY = "steps";


		}
	}
}
