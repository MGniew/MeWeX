#pragma once

#include <ctime>


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* Timer is the class template to countdown time of the algorithm computing.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TimeType	A time data type.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename TimeType = time_t>
class Timer
{
public:
    /**
    * Creates Timer. Starts time counting.
    */
    Timer(void)
    {
        this->mStart = time(NULL);
    }

    /**
    * Creates Timer. Starts time counting.
    *
    * @param[in] rArgs Ignored parameter.
    */
    Timer(const ArgumentsType& rArgs)
    {
        this->mStart = time(NULL);
    }

    /**
    * The object destructor.
    */
    ~Timer(void) {}


    /**
    * Starts time counting.
    */
    void start(void)
    {
        this->mStart = time(NULL);
    }

    /**
    * Returns the computation time.
    *
    * @return The computation time.
    */
    TimeType getTime(void)
    {
        return time(NULL) - this->mStart;
    }

private:
    TimeType mStart;
}; // class Timer


	}
} // namespace Optimizer

