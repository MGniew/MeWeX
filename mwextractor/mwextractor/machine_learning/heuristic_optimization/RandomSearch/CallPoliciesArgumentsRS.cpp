#include "CallPoliciesArgumentsRS.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace RandomSearch
		{


CallPoliciesArgumentsRS::CallPoliciesArgumentsRS(void) : BaseCallPoliciesArguments()
{}

CallPoliciesArgumentsRS::~CallPoliciesArgumentsRS(void)
{}

void CallPoliciesArgumentsRS::readFromFile(const std::string& rFileName)
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

const std::string CallPoliciesArgumentsRS::SECTION = "random_search";
const std::string CallPoliciesArgumentsRS::STEPS_KEY = "steps";


		}
	}
}
