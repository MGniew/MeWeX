#include "IntEvaluationPerformance.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


IntEvaluationPerformance::IntEvaluationPerformance(void) : TEvaluationPerformance<int>()
{}

IntEvaluationPerformance::IntEvaluationPerformance(int evaluation) : TEvaluationPerformance<int>(evaluation)
{}

IntEvaluationPerformance::~IntEvaluationPerformance(void) throw()
{}

bool IntEvaluationPerformance::isEqual(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    IntEvaluationPerformance ep = dynamic_cast<const IntEvaluationPerformance&>(rEvaluationPerformance);
    return this->getEvaluation() == ep.getEvaluation();
}

bool IntEvaluationPerformance::isLess(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    IntEvaluationPerformance ep = dynamic_cast<const IntEvaluationPerformance&>(rEvaluationPerformance);
    return this->getEvaluation() < ep.getEvaluation();
}

bool IntEvaluationPerformance::isGreater(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    IntEvaluationPerformance ep = dynamic_cast<const IntEvaluationPerformance&>(rEvaluationPerformance);
    return this->getEvaluation() > ep.getEvaluation();
}

BaseEvaluationPerformance* IntEvaluationPerformance::duplicate(void) const
{
    return new IntEvaluationPerformance(*this);
}

void IntEvaluationPerformance::setEvaluation(const Data& evaluation)
{
    int eval;
    evaluation.get(eval);
    TEvaluationPerformance<int>::setEvaluation(eval);
}

Data IntEvaluationPerformance::getEvaluation(void)
{
    Data ret = TEvaluationPerformance<int>::getEvaluation();
    return ret;
}

void IntEvaluationPerformance::clear(void)
{
    TEvaluationPerformance<int>::clear();
}

std::string IntEvaluationPerformance::toString(void)
{
    return TEvaluationPerformance<int>::toString();
}


	}
}

