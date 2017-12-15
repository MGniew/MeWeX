#include "Particle.h"
#include "../Random.h"
#include "../DoubleParameter.h"
#include "../Evaluator.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{

Particle::Particle(void)
{
    this->mpEvaluationPerformance = NULL;
}

Particle::Particle(const Point& rPoint) : Point(rPoint), mBest(rPoint)
{
    mVelocity.resize(rPoint.getNumberOfParameters());
    if(rPoint.getNumberOfParameters() > 0)
        for(auto velocity : mVelocity)
        {
            velocity = rPoint.getParameterAt(0).duplicate();
            velocity->getValueAt(0).set(0);
        }
}

Particle::Particle(const Particle& rParticle) : Point(rParticle), mBest(rParticle), mVelocity(rParticle.mVelocity)
{}

//Particle& operator=(const Particle& rParticle);
//bool isEqual(const Point& rPoint);

void Particle::addParameter(const BaseParameter& rParameter)
{
    Point::addParameter(rParameter);
    mVelocity.emplace_back();
}

void Particle::move(const Point& rBest)
{
    double c1 = 1.0, c2 = 1.0, c3 = 1.0;
    double r1 = Random::random(), r2 = Random::random(), r3 = Random::random();
    for(int i = 0; i < mVelocity.size(); i++)
    {
        double v,mX,rX,cX;
        mVelocity[i]->getValueAt(0).get(v);
        mBest.getParameterAt(i).getValueAt(0).get(mX);
        mParameters[i]->getValueAt(0).get(cX);
        rBest.getParameterAt(i).getValueAt(0).get(rX);
        v = (c1 * r1 * v) + (c2 * r2 * (mX - cX)) + (c2 * r2 * (rX - cX));
        mVelocity[i]->getValueAt(0).set(v);
        mParameters[i]->getValueAt(0).set(cX + v);
    }
}

void Particle::setLocalBest(const Point& rPoint)
{
    mBest = rPoint;
}

const Point& Particle::getLocalBest()
{
    return mBest;
}

std::string Particle::toString(void) const
{
    return Point::toString();
}

		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer
