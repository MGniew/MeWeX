
#include "Parallel.h"


namespace utils
{


size_t maxThreads()
{
	return std::thread::hardware_concurrency();
}


}
