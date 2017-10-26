#pragma once

#include <boost/lexical_cast.hpp>

#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


/**
* A Individual is a class for a single individual in the evolutionary algorithm. It represents a potential solution
* of the optimization problem. Class contains the optimized parameters and the evaluation measure.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class Individual : public Point
{
public:
    /**
    * Creates Individual with empty parameters list and <code>NULL</code> evaluation performance..
    */
    Individual(void);

    /**
    * A copy constructor.
    *
    * @param[in] rIndividual A reference to copied Individual object.
    */
    Individual(const Individual& rIndividual);

    /**
    * The object destructor.
    */
    ~Individual(void);

    /**
    * The assignment operator.
    *
    * @param[in] rIndividual A reference to copied Individual object.
    */
    Individual operator=(const Individual& rIndividual);

    /**
    * The assignment operator.
    *
    * @param[in] rPoint	A reference to copied Point object.
    */
    Individual operator=(const Point& rPoint);

    /**
    * Returns relative fitness of <code>this</code> Individual.
    *
    * @return The relative fitness.
    */
    double getRelativeFitness(void) const;

    /**
    * {@inheritDoc}
    */
    void setRandomParameters(void);

    /**
    * Sets relative fitness of <code>this</code> Individual.
    *
    * @param[in] relativeFitness The relative fitness.
    */
    void setRelativeFitness(double relativeFitness);

    /**
    * {@inheritDoc}
    */
    std::string toString(void) const;

    /**
    * A constant used to mark empty variable.
    */
    static const double NO_VALUE;

private:
    double mRelativeFitness;
}; // class Individual


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer

