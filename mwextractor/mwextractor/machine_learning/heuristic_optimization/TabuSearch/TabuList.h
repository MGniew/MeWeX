#pragma once

#include <list>
#include <string>

#include <boost/lexical_cast.hpp>

#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace TabuSearch
		{


/**
* TabuList is the class template to store the points. It contain forbidden set of the points. The class is
* used in the tabu search algorithm. TabuList is realized as a FIFO queue.
*
* @tparam ArgumentsType A call policy argument type.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType>
class TabuList
{
public:
    /**
    * The default constructor. Creates TabuList with tabu list size = 1.
    */
    TabuList(void)
    {
        this->mSize = 1;
    }

    /**
    * Creates TabuList with tabu list size returned by rArgs.getTabuListSize().
    *
    * @param[in] rArgs Argument object.
    */
    TabuList(const ArgumentsType& rArgs)
    {
        this->mSize = rArgs.getTabuListSize();
    }

    /**
    * The object destructor.
    */
    ~TabuList(void)
    {}

    /**
    * Adds Point to tabu list. If the list is full the oldest element is removed.
    *
    * @param[in] rPoint	A point being inserted.
    */
    void add(Point& rPoint)
    {
        if(this->mTabu.size() < this->mSize)
        {
            this->mTabu.push_front(rPoint);
        }
        else
        {
            this->mTabu.pop_back();
            this->mTabu.push_front(rPoint);
        }
    }

    /**
    * Determines if the tabu list contain the given Point.
    *
    * @param[in] rPoint	A feature being tested.
    *
    * @return <code>true</code> if the tabu list contain rPoint; <code>false</code> otherwise.
    */
    bool contain(Point& rPoint)
    {
        typename std::list<Point>::iterator it;
        for(it=this->mTabu.begin(); it!=this->mTabu.end(); ++it)
        {
            if(rPoint.isEqual(*it))
            {
                return true;
            }
        }

        return false;
    }

    /**
    * Sets size of the tabu list.
    *
    * @param[in] value A size of the tabu list.
    */
    void setSize(unsigned int value)
    {
        mSize = value;
    }

    /**
    * Returns size of the tabu list.
    *
    * @return A size of the tabu list.
    */
    unsigned int getSize() const
    {
        return this->mSize;
    }


    /**
    * Converts this TabuList object to its string representation.
    *
    * @return A string that describes this TabuList object.
    */
    std::string toString(void)
    {
        typename std::list<Point>::iterator it;
        std::string ret = "TabuList[Size=";
        ret += boost::lexical_cast<std::string>(this->mSize);
        ret += ",\n";
        for(it=this->mTabu.begin(); it!=this->mTabu.end(); ++it)
        {
            ret += '\t';
            ret += it->toString();
            ret += ",\n";
        }
        ret += ']';

        return ret;
    }

private:
    std::list<Point> mTabu;
    unsigned int mSize;
}; // class TabuList


		}
	} // namespace TabuSearch
} // namespace Optimizer

