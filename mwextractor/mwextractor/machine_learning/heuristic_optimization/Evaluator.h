
#pragma once

#include <string>
#include <vector>


#include "Point.h"

#include "EvolutionaryAlgorithm/Individual.h"

#include "../../utils/Time.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


class Evaluator
{
public:
	typedef EvolutionaryAlgorithm::Individual Individual;

public:
	virtual ~Evaluator() = default;


    void evaluate(Point& pPoint);
    void evaluate(std::vector<Point>& pPoints);
    void evaluate(std::vector<Individual>& pIndividuals);


protected:
    virtual double evaluateIndividual(Point const& pPoint) = 0;
};


	}
}

