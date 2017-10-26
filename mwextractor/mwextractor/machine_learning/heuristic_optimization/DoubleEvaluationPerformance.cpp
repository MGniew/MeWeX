#include "DoubleEvaluationPerformance.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


DoubleEvaluationPerformance::DoubleEvaluationPerformance(void) : TEvaluationPerformance<double>()
{}

DoubleEvaluationPerformance::DoubleEvaluationPerformance(double evaluation) : TEvaluationPerformance<double>(evaluation)
{}

DoubleEvaluationPerformance::~DoubleEvaluationPerformance(void) throw()
{}

bool DoubleEvaluationPerformance::isEqual(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    DoubleEvaluationPerformance ep = dynamic_cast<const DoubleEvaluationPerformance&>(rEvaluationPerformance);
    return this->getEvaluation() == ep.getEvaluation();
}

bool DoubleEvaluationPerformance::isLess(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    DoubleEvaluationPerformance ep = dynamic_cast<const DoubleEvaluationPerformance&>(rEvaluationPerformance);
    return this->getEvaluation() < ep.getEvaluation();
}

bool DoubleEvaluationPerformance::isGreater(const BaseEvaluationPerformance& rEvaluationPerformance)
{
    DoubleEvaluationPerformance ep = dynamic_cast<const DoubleEvaluationPerformance&>(rEvaluationPerformance);
    return this->getEvaluation() > ep.getEvaluation();
}

BaseEvaluationPerformance* DoubleEvaluationPerformance::duplicate(void) const
{
    return new DoubleEvaluationPerformance(*this);
}

void DoubleEvaluationPerformance::setEvaluation(const Data& evaluation)
{
    double eval;
    evaluation.get(eval);
    TEvaluationPerformance<double>::setEvaluation(eval);
}

Data DoubleEvaluationPerformance::getEvaluation(void)
{
    Data ret = TEvaluationPerformance<double>::getEvaluation();
    return ret;
}

void DoubleEvaluationPerformance::clear(void)
{
    TEvaluationPerformance<double>::clear();
}

std::string DoubleEvaluationPerformance::toString(void)
{
    return TEvaluationPerformance<double>::toString();
}


	}
}
