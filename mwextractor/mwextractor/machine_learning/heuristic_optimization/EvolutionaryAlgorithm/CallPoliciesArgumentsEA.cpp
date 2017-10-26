#include "CallPoliciesArgumentsEA.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


CallPoliciesArgumentsEA::CallPoliciesArgumentsEA(void) : BaseCallPoliciesArguments()
{
    this->mPopulationSize = 2;
    this->mTournamentSize = 1;
    this->mCrossoverProb = 0.6;
    this->mMutateProb = 0.05;
    this->mNumberOfClone = 1;
}

CallPoliciesArgumentsEA::~CallPoliciesArgumentsEA(void)
{
}

void CallPoliciesArgumentsEA::readFromFile(const std::string& rFileName)
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
        this->mPopulationSize = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), POPULATION_KEY.c_str(), 2));
        this->mTournamentSize = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), TOURNAMENT_KEY.c_str(), 1));
        this->mCrossoverProb = configFile.GetDoubleValue(SECTION.c_str(), CROSSOVER_KEY.c_str(), 0.6);
        this->mMutateProb = configFile.GetDoubleValue(SECTION.c_str(), MUTATE_KEY.c_str(), 0.05);
        this->mNumberOfClone = static_cast<unsigned int>(configFile.GetLongValue(SECTION.c_str(), CLONE_KEY.c_str(), 1));
    }
}

unsigned int CallPoliciesArgumentsEA::getPopulationSize(void) const
{
    return this->mPopulationSize;
}

unsigned int CallPoliciesArgumentsEA::getTournamentSize(void) const
{
    return this->mTournamentSize;
}

double CallPoliciesArgumentsEA::getCrossoverProbability(void) const
{
    return this->mCrossoverProb;
}

double CallPoliciesArgumentsEA::getMutateProbability(void) const
{
    return this->mMutateProb;
}

unsigned int CallPoliciesArgumentsEA::getNumberOfClone(void) const
{
    return this->mNumberOfClone;
}

void CallPoliciesArgumentsEA::setPopulationSize(unsigned int value)
{
    this->mPopulationSize = value;
}

void CallPoliciesArgumentsEA::setTournamentSize(unsigned int value)
{
    this->mTournamentSize = value;
}

void CallPoliciesArgumentsEA::setCrossoverProbability(double value)
{
    this->mCrossoverProb = value;
}

void CallPoliciesArgumentsEA::setMutateProbability(double value)
{
    this->mMutateProb = value;
}

void CallPoliciesArgumentsEA::setNumberOfClone(unsigned int value)
{
    this->mNumberOfClone = value;
}

const std::string CallPoliciesArgumentsEA::SECTION = "evolutionary_algorithm";
const std::string CallPoliciesArgumentsEA::STEPS_KEY = "steps";
const std::string CallPoliciesArgumentsEA::POPULATION_KEY = "population";
const std::string CallPoliciesArgumentsEA::TOURNAMENT_KEY = "tournament";
const std::string CallPoliciesArgumentsEA::CROSSOVER_KEY = "crossover";
const std::string CallPoliciesArgumentsEA::MUTATE_KEY = "mutate";
const std::string CallPoliciesArgumentsEA::CLONE_KEY = "clone";


		}
	}
}

