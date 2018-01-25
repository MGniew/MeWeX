#pragma once

#include <string>

#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{


class Particle : public Point
{
public:
    Particle(void);
    ~Particle(void);

    Particle(const Point& rPoint);
    Particle(const Particle& rPoint);
    Particle& operator=(Particle rParticle);
    //bool isEqual(const Point& rPoint);
    void addParameter(const BaseParameter& rParameter);
    void setLocalBest(const Point& rPoint);
    const Point& getLocalBest() const;
    double getVelocityLengthSquared() const;
    void move(const Point& rBest, double w = 1.0, double wl = 0.2, double wg = 0.8);
    void setRandomParameters(void);
    std::string toString(void) const;

private:
    std::vector<BaseParameter*> mVelocity;
    Point* mBest;
}; // class Particle


		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer
