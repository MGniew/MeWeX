#include "Random.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{

std::uniform_real_distribution<double> Random::distance(0.0, 1.0);
std::normal_distribution<double> Random::normal(0.0, 0.25);
std::mt19937_64 Random::generator(time(nullptr));


double Random::random(void)
{
    return distance(generator);
}

double Random::random_inv_normal(void)
{
    double val = normal(generator);
    if(val < 0.5)
    {
        val += 0.5;
        if(val < 0)
            val = 0;
    }
    else
    {
        val -= 0.5;
        if(val > 1)
            val = 1;
    }
    return val;
}

	}
}
