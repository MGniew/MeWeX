
#include <iostream>

#include "Evaluator.h"

#include "Data.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


void Evaluator::evaluate(Point& pPoint)
{
	utils::Time evaluationBeginTime;

	double score = evaluateIndividual(pPoint);
	pPoint.getEvaluationPerformance().setEvaluation(Data(score));

	utils::Time evaluationEndTime;

	std::cerr << "Evaluation done in " << (evaluationEndTime - evaluationBeginTime) << 's' << std::endl;
}

void Evaluator::evaluate(std::vector<Point>& pPoints)
{
    for(size_t point = 0; point < pPoints.size(); ++point)
    {
        this->evaluate(pPoints[point]);
    }
}

void Evaluator::evaluate(std::vector<Individual>& rIndividuals)
{
    for(unsigned int individual = 0; individual < rIndividuals.size(); ++individual)
    {
        this->evaluate(rIndividuals[individual]);
    }
}


	}
}
