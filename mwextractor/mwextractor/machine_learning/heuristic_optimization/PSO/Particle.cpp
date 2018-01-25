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
    this->mpEvaluationPerformance = nullptr;
    this->mBest = nullptr;
}

Particle::~Particle(void)
{
    if(mBest != nullptr)
        delete mBest;
    for(auto& velocity : mVelocity)
    {
        delete velocity;
    }
}

Particle::Particle(const Point& rPoint) : Point(rPoint)
{
    mBest = new Point(rPoint);
    mVelocity.resize(rPoint.getNumberOfParameters());
    if(rPoint.getNumberOfParameters() > 0)
        for(auto& velocity : mVelocity)
        {
            velocity = rPoint.getParameterAt(0).duplicate();
            velocity->getValueAt(0).set(0);
        }
}

Particle::Particle(const Particle& rParticle) : Point(rParticle), mVelocity(rParticle.mVelocity)
{
    mBest = new Point(rParticle.getLocalBest());
    if(rParticle.getNumberOfParameters() > 0)
        for(auto& velocity : mVelocity)
        {
            velocity = velocity->duplicate();
        }
}

Particle& Particle::operator=(Particle rParticle)
{
    mVelocity.swap(rParticle.mVelocity);
    mParameters.swap(rParticle.mParameters);
    auto tmpBest = mBest;
    mBest = rParticle.mBest;
    rParticle.mBest = tmpBest;
    auto tmp = mpEvaluationPerformance;
    mpEvaluationPerformance = rParticle.mpEvaluationPerformance;
    rParticle.mpEvaluationPerformance = tmp;
    return *this;
}

void Particle::addParameter(const BaseParameter& rParameter)
{
    Point::addParameter(rParameter);
    mVelocity.emplace_back();
}

void Particle::move(const Point& rBest, double w, double wl, double wg)
{
    double r1 = Random::random(), r2 = Random::random(), r3 = Random::random();
    for(int i = 0; i < mVelocity.size(); i++)
    {
        double v,mX,rX,cX;
        auto data = mVelocity[i]->getValueAt(0);
        mVelocity[i]->getValueAt(0).get(v);
        mBest->getParameterAt(i).getValueAt(0).get(mX);
        mParameters[i]->getValueAt(0).get(cX);
        rBest.getParameterAt(i).getValueAt(0).get(rX);
        v = (w * r1 * v) + (wl * r2 * (mX - cX)) + (wg * r3 * (rX - cX));
        data.set(v);
        mVelocity[i]->setValueAt(0, data);
        data.set(cX + v);
        mParameters[i]->setValueAt(0, data);
    }
}

void Particle::setRandomParameters(void)
{
    unsigned int sizeParam;
    for(unsigned int i=0; i<this->mParameters.size(); i++)
    {
        sizeParam = this->mParameters[i]->getSize();
        for(unsigned int j=0; j<sizeParam; j++)
        {
            this->mParameters[i]->setRandomValue(j,Random::Distribution::INV_NORMAL);
        }
    }
    this->mpEvaluationPerformance->clear();
}

void Particle::setLocalBest(const Point& rPoint)
{
    if(mBest == nullptr)
        mBest = new Point(rPoint);
    else
        *mBest = rPoint;
}

const Point& Particle::getLocalBest() const
{
    return *mBest;
}

double Particle::getVelocityLengthSquared() const
{
    double sum = 0.0, val;
    for(auto& elem : mVelocity)
    {
        elem->getValueAt(0).get(val);
        sum += val * val;
    }
    return sum;
}

std::string Particle::toString(void) const
{
    return Point::toString();
}

		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer
