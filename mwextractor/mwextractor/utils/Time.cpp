
#include <time.h>

#include "Time.h"


namespace utils
{


Time::Time()
{
	update();
}


double Time::inSeconds() const
{
	return
		static_cast<double>(mTime.tv_sec) +
		1e-9 * static_cast<double>(mTime.tv_nsec);
}


double Time::difference(Time const& pTime) const
{
	return
		static_cast<double>(mTime.tv_sec - pTime.mTime.tv_sec) +
		1e-9 * static_cast<double>(mTime.tv_nsec - pTime.mTime.tv_nsec);
}


double Time::operator-(Time const& pTime) const
{
	return difference(pTime);
}


void Time::update()
{
	clock_gettime(CLOCK_MONOTONIC, &mTime);
}


}
