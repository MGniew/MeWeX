#include "Individual.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


Individual::Individual(void) : Point()
{
    this->mRelativeFitness = NO_VALUE;
}

Individual::Individual(const Individual& rIndividual) : Point(rIndividual)
{
    this->mRelativeFitness = rIndividual.mRelativeFitness;
}

Individual::~Individual(void)
{}

Individual Individual::operator=(const Individual& rIndividual)
{
    Point::operator=(rIndividual);
    this->mRelativeFitness = rIndividual.mRelativeFitness;
    return *this;
}

Individual Individual::operator=(const Point& rPoint)
{
    Point::operator=(rPoint);
    this->mRelativeFitness = Individual::NO_VALUE;
    return *this;
}

double Individual::getRelativeFitness(void) const
{
    return this->mRelativeFitness;
}

void Individual::setRandomParameters(void)
{
    Point::setRandomParameters();
    this->mRelativeFitness = NO_VALUE;
}

void Individual::setRelativeFitness(double relativeFitness)
{
    this->mRelativeFitness = relativeFitness;
}

std::string Individual::toString(void) const
{
    std::string ret = "Individual{Parameters{";
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
        ret += "; RelativeFitness=";
        ret += boost::lexical_cast<std::string>(this->mRelativeFitness);
    }
    else
    {
        ret += "EvaluationPerformance";
    }
    ret += "}";
    return ret;

}

const double Individual::NO_VALUE = -1.0;

		}
	}
}
