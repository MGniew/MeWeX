#pragma once

#include "../Random.h"
#include "Individual.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


template<typename ArgumentsType>
class UniformCrossover
{
public:
    UniformCrossover(void)
    {
        this->mCrossoverProbability = 0.8;
    }

    UniformCrossover(const ArgumentsType& rArgs)
    {
        this->mCrossoverProbability = rArgs.getCrossoverProbability();
    }

    ~UniformCrossover(void)
    {}

    void crossover(Individual& rFirstIndividual, Individual& rSecondIndividual)
    {
        const unsigned int nop = rFirstIndividual.getNumberOfParameters();
        bool* mask = NULL;
        this->makeMask(mask, rFirstIndividual);

        Data tmp;
        unsigned int gene = 0;
        bool modification = false;
        unsigned int paramSize;

        for(unsigned int i=0; i<nop; i++)
        {
            paramSize = rFirstIndividual.getParameterAt(i).getSize();
            for(unsigned int j=0; j<paramSize; j++)
            {
                if(mask[gene])
                {
                    tmp = rFirstIndividual.getParameterAt(i).getValueAt(j);
                    rFirstIndividual.getParameterAt(i).setValueAt(j, rSecondIndividual.getParameterAt(i).getValueAt(j));
                    rSecondIndividual.getParameterAt(i).setValueAt(j, tmp);
                    modification = true;
                }
                gene++;
            }
        }

        if(modification)
        {
            rFirstIndividual.getEvaluationPerformance().clear();
            rFirstIndividual.setRelativeFitness(rFirstIndividual.NO_VALUE);

            rSecondIndividual.getEvaluationPerformance().clear();
            rSecondIndividual.setRelativeFitness(rSecondIndividual.NO_VALUE);
        }

        delete[] mask;
    }

    double getCrossoverProbability(void) const
    {
        return this->mCrossoverProbability;
    }

private:
    unsigned int makeMask(bool*& pMask, const Individual& rIndividual)
    {
        const unsigned int nop = rIndividual.getNumberOfParameters();
        unsigned int size = 0;

        for(unsigned int i=0; i<nop; i++)
        {
            size += rIndividual.getParameterAt(i).getSize();
        }

        if(0 != size)
        {
            pMask = new bool[size];
            for(unsigned int i=0; i<size; i++)
            {
                pMask[i] = (Random::random() < 0.5) ? false : true;
            }
        }
        return size;
    }

    double mCrossoverProbability;

}; // class UniformCrossover


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer

