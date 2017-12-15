#include "Random.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{

std::uniform_real_distribution<double> Random::distance(0.0, 1.0);
std::mt19937_64 Random::generator(time(nullptr));


double Random::random(void)
{
    return distance(generator);
}

	}
}
