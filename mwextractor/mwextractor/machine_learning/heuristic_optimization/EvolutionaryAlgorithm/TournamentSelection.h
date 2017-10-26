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
* The tournament selection class template. The class is used in the evolutionary algorithm as selection rule.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam PopulationType	A poulation class.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename PopulationType>
class TournamentSelection
{
public:
    /**
    * Creates TournamentSelection with tournament size 1.
    */
    TournamentSelection(void)
    {
        msTournamentSize = 1;
    }

    /**
    * Creates TournamentSelection with tournament size returned by rArgs.getTournamentSize().
    *
    * @param[in] rArgs The argument object.
    **/
    TournamentSelection(const ArgumentsType& rArgs)
    {
        msTournamentSize = rArgs.getTournamentSize();
    }

    /**
    * The object destructor.
    */
    ~TournamentSelection(void)
    {}

    /**
    * Selects the population.
    *
    * @param[in, out] rPopulation
    */
    void select(PopulationType& rPopulation)
    {
        unsigned int popSize = rPopulation.getPopulationSize();
        double* rouletteArray = new double[popSize];
        rouletteArray[0] = rPopulation.getIndividualAt(0).getRelativeFitness();
        for(unsigned int i=1; i<popSize; i++)
        {
            rouletteArray[i] = rouletteArray[i-1] + rPopulation.getIndividualAt(i).getRelativeFitness();
        }

        PopulationType nextPopulation = rPopulation;
        unsigned int* tournament = new unsigned int[TournamentSelection::msTournamentSize];
        unsigned int winner;

        for(unsigned int i=0; i<popSize; i++)
        {
            for(unsigned int j=0; j<TournamentSelection::msTournamentSize; j++)
            {
                tournament[j] = TournamentSelection::getRandomIndividual(rPopulation, rouletteArray);
            }
            winner = TournamentSelection::findBest(rPopulation, tournament, TournamentSelection::msTournamentSize);
            nextPopulation.InsertIndividualAt(i, rPopulation.getIndividualAt(winner));
        }

        delete[] tournament;
        delete[] rouletteArray;
        rPopulation = nextPopulation;
    }

private:
    unsigned int  msTournamentSize;

    unsigned int getRandomIndividual(PopulationType& rPopulation, double* roulette)
    {
        double p = Random::random();
        unsigned int popSize = rPopulation.getPopulationSize();
        for(unsigned int i=0; i<popSize; i++)
        {
            if(p<roulette[i])
                return i;
        }
        return popSize-1;
    }

    unsigned int findBest(PopulationType& rPopulation, unsigned int* pTournament, int length)
    {
        unsigned int ret = pTournament[0];
        for(int i=1; i<length; i++)
        {
            if(rPopulation.getIndividualAt(pTournament[i-1]).getEvaluationPerformance().isLess(rPopulation.getIndividualAt(pTournament[i]).getEvaluationPerformance()))
            {
                ret = pTournament[i];
            }
        }
        return ret;
    }
}; // class TournamentSelection


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer


