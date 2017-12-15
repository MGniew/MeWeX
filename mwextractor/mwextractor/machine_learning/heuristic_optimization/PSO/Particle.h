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

    Particle(const Point& rPoint);
    Particle(const Particle& rPoint);
    //Particle& operator=(const Particle& rParticle);
    //bool isEqual(const Point& rPoint);
    void addParameter(const BaseParameter& rParameter);
    void setLocalBest(const Point& rPoint);
    const Point& getLocalBest();
    void move(const Point& rBest);
    std::string toString(void) const;

private:
    std::vector<BaseParameter*> mVelocity;
    Point mBest;
}; // class Particle


		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer
