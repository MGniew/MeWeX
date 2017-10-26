#pragma once

#include <string>

#include "../BaseCallPoliciesArguments.h"
#include "../Exception/Exception.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{
/**
* A class for call policies arguments used in evolutionary algorithm. It holds the characteristic parameters for
* a call policies, such as: population size, tournament size, probability of crossover and mutation, number of
* pre-initialized individuals (clones).
*
* @see BaseCallPoliciesArguments
* @see TournamentSelection
* @see UniformCrossover
* @see Mutation
* @see Population
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class CallPoliciesArgumentsEA : public BaseCallPoliciesArguments
{
public:
    /**
    * Creates object with default values:
    * <ul>
    * <li>population size = 2,</li>
    * <li>tournament size = 1,</li>
    * <li>probability of crossover = 0.6,</li>
    * <li>probability of mutation = 0.05,</li>
    * <li>clones = 1.</li>
    * </ul>
    */
    CallPoliciesArgumentsEA(void);

    /**
    * The object destructor.
    */
    ~CallPoliciesArgumentsEA(void);

    /**
    * Reads the characteristic parameters from a .ini <a href="optimizer.cfg">file</a>
    * (section "evolutionary_algorithm"). If one of the value (or key) is missing in file then method takes
    * default value for that key. Default values for keys are as follows:
    * <ul>
    * <li>steps = 10,</li>
    * <li>population = 2,</li>
    * <li>tournament = 1,</li>
    * <li>crossover = 0.6,</li>
    * <li>mutation = 0.05,</li>
    * <li>clones = 1.</li>
    * </ul>
    *
    * @note See example in section "evolutionary_algorithm" in config <a href="optimizer.cfg">file</a>.
    *
    * @param[in] rFileName The config file name.
    *
    * @see BaseCallPoliciesArguments
    * @see TournamentSelection
    * @see UniformCrossover
    * @see Mutation
    * @see Population
    */
    void readFromFile(const std::string& rFileName);

    /**
    * Returns population size.
    *
    * @return The population size.
    */
    unsigned int getPopulationSize(void) const;

    /**
    * Returns tournament size.
    *
    * @return The tournament size.
    */
    unsigned int getTournamentSize(void) const;

    /**
    * Returns probability of crossover.
    *
    * @return The probability of crossover <0, 1>.
    */
    double getCrossoverProbability(void) const;

    /**
    * Returns probability of mutation.
    *
    * @return The probability of  mutation <0, 1>.
    */
    double getMutateProbability(void) const;

    /**
    * Returns number of pre-initialized individuals in first population.
    *
    * @return The number of pre-initialized individuals.
    */
    unsigned int getNumberOfClone(void) const;

    /**
    * Sets population size.
    *
    * @param[in] value The population size.
    */
    void setPopulationSize(unsigned int value);

    /**
    * Sets tournament size.
    *
    * @param[in] value The tournament size.
    */
    void setTournamentSize(unsigned int value);

    /**
    * Sets probability of crossover.
    *
    * @param[in] value The probability of crossover <0, 1>.
    */
    void setCrossoverProbability(double value);

    /**
    * Sets probability of mutation.
    *
    * @param[in] value The probability of mutation <0, 1>.
    */
    void setMutateProbability(double value);

    /**
    * Sets number of pre-initialized individuals in first population.
    *
    * @param[in] value The number of pre-initialized individuals.
    */
    void setNumberOfClone(unsigned int value);

private:
    unsigned int mPopulationSize;
    unsigned int mTournamentSize;
    double mCrossoverProb;
    double mMutateProb;
    unsigned int mNumberOfClone;

    static const std::string SECTION;
    static const std::string STEPS_KEY;
    static const std::string POPULATION_KEY;
    static const std::string TOURNAMENT_KEY;
    static const std::string CROSSOVER_KEY;
    static const std::string MUTATE_KEY;
    static const std::string CLONE_KEY;
}; // class CallPoliciesArgumentsEA


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer

