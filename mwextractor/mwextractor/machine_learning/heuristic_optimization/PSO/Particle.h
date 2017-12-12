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
    Particle(void){}

    Particle(const Point& rPoint);
    Particle(const Particle& rPoint);
    //Particle& operator=(const Particle& rParticle);
    //bool isEqual(const Point& rPoint);
    void addParameter(const BaseParameter& rParameter);
    std::string toString(void) const
    {
        ;
    }

private:

    static std::vector<BaseParameter*> mGbest;// ofc it is tmp solution and it must be changed
    std::vector<BaseParameter*> mVelocity;
}; // class Particle


		}
	} // namespace particle_swarm_optimization
} // namespace Optimizer
