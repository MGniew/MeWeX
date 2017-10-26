#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#include "../Random.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


/**
* Population is the class template to store the individuals. The class is used in evolutionary algorithm.
* Population contains a group of a individuals in the one generation.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam MutationScheme Provides algorithm to mutate individuals.
* @tparam CrossoverScheme Provides algorithm to crossover individuals.
*
* @see Individual
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename MutationScheme,
         typename CrossoverScheme>
class Population
{
public:
    /**
    * Creates population with size 0.
    */
    Population(void)
    {
        this->mPopulationSize = 0;
        this->mBest = 0;
        this->mWorst = 0;
        this->mAverageFitness = 0.0;
        this->mStdDev = 0.0;
    }

    /**
    * Creates population with given size. The numberOfClones parameter determines how many individuals in
    * population are copy of <code>rIndividual</code>. If numberOfClones is less than the population size then
    * the rest of individuals are randomly.
    *
    * @param[in] rIndividual The base individual.
    * @param[in] popSize Size of population.
    * @param[in] numberOfClones The number of pre-initialized individuals.
    */
    Population(const Individual& rIndividual, unsigned int popSize, unsigned int numberOfClones = 0)
    {
        this->mPopulationSize = popSize;
        this->mBest = 0;
        this->mWorst = 0;
        this->mAverageFitness = 0.0;
        this->mStdDev = 0.0;

        for(unsigned int i=0; i<popSize; i++)
        {
            this->mIndividuals.push_back(rIndividual);
            if(i>=numberOfClones)
            {
                this->mIndividuals[i].setRandomParameters();
            }
        }
    }

    /**
    * Creates population with size returned by rArgs.getPopulationSize(). The numberOfClones parameter determines
    * how many individuals in population are copy of <code>rIndividual</code>. If numberOfClones is less than the
    * population size then the rest of individuals are randomly.
    *
    * @param[in] rIndividual The base individual.
    * @param[in] rArgs The argument object.
    * @param[in] numberOfClones The number of pre-initialized individuals.
    */
    Population(const Individual& rIndividual, const ArgumentsType& rArgs, unsigned int numberOfClones = 0)
    {
        this->mPopulationSize = rArgs.getPopulationSize();
        this->mBest = 0;
        this->mWorst = 0;
        this->mAverageFitness = 0.0;
        this->mStdDev = 0.0;

        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            this->mIndividuals.push_back(rIndividual);
            if(i>=numberOfClones)
            {
                this->mIndividuals[i].setRandomParameters();
            }
        }
    }


    /**
    * The copy constructor.
    *
    * @param rPopularion Reference to copied Population.
    */
    Population(const Population& rPopularion)
    {
        this->mPopulationSize = rPopularion.mPopulationSize;
        this->mBest = rPopularion.mBest;
        this->mWorst = rPopularion.mWorst;
        this->mAverageFitness = rPopularion.mAverageFitness;
        this->mStdDev = rPopularion.mStdDev;

        this->mIndividuals = rPopularion.mIndividuals;
    }

    /**
    * The object destructor.
    */
    ~Population(void) {}

    /**
    * The assignment operator.
    *
    * @param[in] rPopulation A reference to copied Population object.
    */
    Population& operator=(const Population& rPopulation)
    {
        this->mPopulationSize = rPopulation.mPopulationSize;
        this->mBest = rPopulation.mBest;
        this->mWorst = rPopulation.mWorst;
        this->mAverageFitness = rPopulation.mAverageFitness;
        this->mStdDev = rPopulation.mStdDev;

        this->mIndividuals = rPopulation.mIndividuals;

        return *this;
    }

    /**
    * Computes average and relative fitness, standard deviation, the best and the worst individual in population.
    */
    void computeStatistics(void)
    {
        double fitnessSum = 0.0;
        unsigned int best = 0;
        unsigned int worst = 0;
        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            fitnessSum += dataCast<double>(this->mIndividuals[i].getEvaluationPerformance().getEvaluation());

            if(this->mIndividuals[best].getEvaluationPerformance().isLess(this->mIndividuals[i].getEvaluationPerformance()))
            {
                best = i;
            }

            if(this->mIndividuals[worst].getEvaluationPerformance().isGreater(this->mIndividuals[i].getEvaluationPerformance()))
            {
                worst = i;
            }
        }
        double eval;
        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            eval = dataCast<double>(this->mIndividuals[i].getEvaluationPerformance().getEvaluation());
            this->mIndividuals[i].setRelativeFitness(eval/fitnessSum);
        }

        this->mAverageFitness = fitnessSum/this->mPopulationSize;

        this->mBest = best;
        this->mWorst = worst;
        this->stdDeviation();
    }

    /**
    * Mutates population.
    *
    * @param[in] rMutationScheme Provides algorithm to mutate individuals.
    */
    void mutate(MutationScheme& rMutationScheme)
    {
        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            rMutationScheme.mutate(this->mIndividuals[i]);
        }

        this->mBest = 0;
        this->mWorst = 0;
        this->mAverageFitness = -1.0;
        this->mStdDev = -1.0;
    }

    /**
    * Crossover population.
    *
    * @param[in] rCrossoverScheme Provides algorithm to crossover individuals.
    */
    void crossover(CrossoverScheme& rCrossoverScheme)
    {
        std::vector<std::vector<unsigned int> > pairs;
        this->selectPair(rCrossoverScheme.getCrossoverProbability(), pairs);

        for(unsigned int i=0; i<pairs.size(); i++)
        {
            rCrossoverScheme.crossover(this->mIndividuals[pairs[i][0]], this->mIndividuals[pairs[i][1]]);
        }
    }

    /**
    * Returns individual at the given position.
    *
    * @param[in] position The index of the returned individual.
    *
    * @return The individual at the given position.
    */
    Individual getIndividualAt(unsigned int position) const
    {
        return this->mIndividuals[position];
    }

    /**
    * Returns the individual with the highest fitness in population.
    *
    * @return The individual with the highest fitness.
    */
    Individual getBestIndividual(void) const
    {
        return this->mIndividuals[this->mBest];
    }

    /**
    * Returns the individual with the lowest fitness in population.
    *
    * @return The individual with the lowest fitness.
    */
    Individual getWorstIndividual(void) const
    {
        return this->mIndividuals[this->mWorst];
    }

    /**
    * Returns size of population.
    *
    * @return Size of population.
    */
    unsigned int getPopulationSize(void) const
    {
        return this->mPopulationSize;
    }

    /**
    * Inserts individual at the given position.
    *
    * @param[in] position The position of the inserted individual.
    * @param[in] rIndividual The inserted individual.
    */
    void InsertIndividualAt(unsigned int position, const Individual& rIndividual)
    {
        this->mIndividuals[position] = rIndividual;
    }

    /**
    * Sets size of population.
    *
    * @param[in] popSize Size of population.
    */
    void setPopulationSize(unsigned int popSize)
    {
        this->mPopulationSize = popSize;
    }

    /**
    * Returns reference to individuals vector.
    *
    * @return The reference to individuals vector.
    *
    * @see Individual
    */
    std::vector<Individual>& getIndividuals(void)
    {
        return this->mIndividuals;
    }

    /**
    * Converts this Population object to its string representation.
    *
    * @return A string that describes this object.
    */
    std::string toString() const
    {
        std::stringstream strs;
        strs<<"Population[PopulationSize=";
        strs<<this->mPopulationSize;
        strs<<", AverageFitness=";
        strs<<this->mAverageFitness;
        strs<<", StandardDeviation=";
        strs<<this->mStdDev;
        strs<<","<<std::endl;
        strs<<"\tBestIndividual=";
        strs<<this->getBestIndividual().toString();
        strs<<","<<std::endl;
        strs<<"\tWorstIndividual=";
        strs<<this->getWorstIndividual().toString();
        strs<<","<<std::endl;
        strs<<"\tIndividuals="<<std::endl;
        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            strs<<"\t\t";
            strs<<this->mIndividuals[i].toString();
            strs<<std::endl;
        }

        strs<<"]";
        return strs.str();
    }

private:
    std::vector<Individual> mIndividuals;
    unsigned int mPopulationSize;
    unsigned int mBest;
    unsigned int mWorst;
    double mAverageFitness;
    double mStdDev;

    void selectPair(double crossoverProbability, std::vector<std::vector<unsigned int> >& rPairs)
    {
        bool* aux = new bool[this->mPopulationSize];
        unsigned int l = 0;
        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            if(Random::random() < crossoverProbability)
            {
                aux[i] = true;
                l++;
            }
            else
            {
                aux[i] = false;
            }
        }

        if((l%2) != 0)
        {
            --l;
        }

        rPairs.clear();
        for(unsigned int i=0; i<l/2; i++)
        {
            std::vector<unsigned int> pair(2, 0);
            rPairs.push_back(pair);
        }
        unsigned int first=0, second, j=0;

        while((first < this->mPopulationSize) && (j<l/2))
        {
            if(aux[first]==true)
            {
                rPairs[j][0] = first;
                aux[first]=false;

                second = Random::random<unsigned int>(0, this->mPopulationSize);
                while(!aux[second])
                {
                    second++;
                    second = second%this->mPopulationSize;
                }

                rPairs[j][1] = second;
                aux[second] = false;
                j++;
            }
            first++;
        }
        delete[] aux;

    }

    void stdDeviation()
    {
        double aux = 0.0;
        double fit;
        for(unsigned int i=0; i<this->mPopulationSize; i++)
        {
            fit = dataCast<double>(this->mIndividuals[i].getEvaluationPerformance().getEvaluation());
            aux += pow(fit - this->mAverageFitness, 2);
        }
        this->mStdDev = sqrt(aux/this->mAverageFitness);
    }
}; // class Population


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer
