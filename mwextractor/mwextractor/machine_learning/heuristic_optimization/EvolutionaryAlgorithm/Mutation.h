#pragma once

#include "../Random.h"
#include "Individual.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


/**
*
*
* @tparam ArgumentsType A call policy argument type.
*
* @see Individual
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType>
class Mutation
{
public:
    /**
    * Creates Mutation with mutate probability 0.2.
    */
    Mutation(void)
    {
        this->mMutateProbability = 0.2;
    }

    /**
    * Creates Mutation with mutate probability returned by rArgs.getMutateProbability().
    *
    * @param[in] rArgs The argument object.
    *
    * @see CallPoliciesArgumentsEA
    * @see BaseCallPoliciesArguments
    */
    Mutation(const ArgumentsType& rArgs)
    {
        this->mMutateProbability = rArgs.getMutateProbability();
    }

    /**
    * The object destructor.
    */
    ~Mutation(void)
    {}

    /**
    * A mutation operator. The method selects and modifies randomly a few genes (parameters). If parameter is
    * selected then setRandomValue method is called.
    *
    * @param[in] rIndividual The individual subjected to mutation.
    *
    * @see Individual
    * @see BaseParameter.setRandomValue
    */
    void mutate(Individual& rIndividual)
    {
        Individual copy = rIndividual;
        Data tmp;
        unsigned int paramSize;
        unsigned int nop = rIndividual.getNumberOfParameters();

        for(unsigned int i=0; i<nop; i++)
        {
            paramSize = rIndividual.getParameterAt(i).getSize();
            for(unsigned int j=0; j<paramSize; j++)
            {
                if(Random::random() < this->mMutateProbability)
                {
                    rIndividual.getParameterAt(i).setRandomValue(j);
                }
            }
        }

        if(!rIndividual.isEqual(copy)) // parameters compare
        {
            rIndividual.getEvaluationPerformance().clear();
            rIndividual.setRelativeFitness(rIndividual.NO_VALUE);
        }
    }
private:
    double mMutateProbability;

}; // class Mutation


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer

