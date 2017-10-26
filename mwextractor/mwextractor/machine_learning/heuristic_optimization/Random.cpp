#include "Random.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


Random::Random(void)
{}

Random::~Random(void)
{}

double Random::random(void)
{
    if(0 == been)
    {
        been = time(NULL);
        srand(static_cast<unsigned int>(been));
    }

    double ret = static_cast<double>(rand())/static_cast<double>(RAND_MAX);
    return ret;
}

time_t Random::been = 0;


	}
}
