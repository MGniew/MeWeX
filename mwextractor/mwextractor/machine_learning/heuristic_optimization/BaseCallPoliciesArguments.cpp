#include "BaseCallPoliciesArguments.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


BaseCallPoliciesArguments::BaseCallPoliciesArguments(void)
{
    this->mStartStep = 0;
    this->mSteps = 10;
    this->mReportFileName = "report.txt";
}

BaseCallPoliciesArguments::~BaseCallPoliciesArguments(void)
{
}

unsigned int BaseCallPoliciesArguments::getStartStep(void) const
{
    return this->mStartStep;
}

unsigned int BaseCallPoliciesArguments::getSteps(void) const
{
    return this->mSteps;
}

std::string BaseCallPoliciesArguments::getReportFileName(void) const
{
    return this->mReportFileName;
}

std::string BaseCallPoliciesArguments::getTargetName(void) const
{
    return this->mTargetName;
}

void BaseCallPoliciesArguments::setStartStep(unsigned int value)
{
    this->mStartStep = value;
}

void BaseCallPoliciesArguments::setSteps(unsigned int value)
{
    this->mSteps = value;
}

void BaseCallPoliciesArguments::setReportFileName(const std::string& rFileName)
{
    this->mReportFileName = rFileName;
}

void BaseCallPoliciesArguments::setTargetName(const std::string& rTargetName)
{
    this->mTargetName = rTargetName;
}


	}
}
