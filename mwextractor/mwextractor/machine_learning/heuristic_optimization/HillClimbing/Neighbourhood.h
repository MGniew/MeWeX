#pragma once

#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace HillClimbing
		{


/**
* Neighbourhood is the class template to store the neighbours of given Point. The class is used in
* HillClimbing algorithm.
*
* @tparam ArgumentsType  A call policy argument type.
* @tparam NeighbourhoodScheme Class provides algorithm to generate neighbours.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename NeighbourhoodScheme>
class Neighbourhood
{
public:
    /**
    * A default constructor. Creates object with neighbourhood size = 1.
    */
    Neighbourhood(void)
    {
        this->mSize = 1;
    }

    /**
    * Creates Neighbourhood with a neighbourhood size returned by rArgs.getNeighbourhoodSize().
    *
    * @param rArgs Argument object.
    * @param rNeighbourhoodScheme Provides algorithm to generate a neighbours.
    */
    Neighbourhood(const ArgumentsType& rArgs, NeighbourhoodScheme& rNeighbourhoodScheme)
    {
        this->mSize = rArgs.getNeighbourhoodSize();
        this->mNeighbourhoodScheme = rNeighbourhoodScheme;
    }

    /**
    * An object destructor.
    */
    ~Neighbourhood(void) {}

    /**
    * Generates neighbourhood of the given point.
    *
    * @param[in] rPoint	Point that is a base to generate the neighbourhood.
    *
    * @see Point
    */
    void generate(Point& rPoint)
    {
        this->mNeighbours.clear();
        Point neighbour;
        while(this->mNeighbours.size() < this->mSize)
        {
            neighbour = this->mNeighbourhoodScheme.getNeighbour(rPoint);
            this->mNeighbours.push_back(neighbour);
        }
    }

    /**
    * Returns Point from neighbourhood with the highest evaluation.
    *
    * @return The best point.
    *
    * @see Point
    */
    Point locateBest(void)
    {
        unsigned int best = 0;
        for(unsigned int i=0; i<this->mSize; i++)
        {
            //this->mNeighbours[i].evaluate();
            if(this->mNeighbours[i].getEvaluationPerformance().isGreater(this->mNeighbours[best].getEvaluationPerformance()))
            {
                best = i;
            }
        }

        return this->mNeighbours[best];
    }

    /**
    * Sets size of the neighbourhood.
    *
    * @param[in] value Size of the neighbourhood.
    */
    void setSize(unsigned int value)
    {
        this->mSize = value;
    }

    /**
    * Returns size of the neighbourhood.
    *
    * @return Size of the neighbourhood.
    */
    unsigned int getSize()
    {
        return this->mSize;
    }

    /**
    * Returns reference to points vector.
    *
    * @return The reference to points vector.
    *
    * @see Point
    */
    std::vector<Point>& getNeighbours(void)
    {
        return this->mNeighbours;
    }

    /**
    * Converts this Neighbourhood object to its string representation.
    *
    * @return A string that describes this object.
    */
    std::string toString(void)
    {
        std::string ret = "Neighbourhood[Size=";
        ret += boost::lexical_cast<std::string>(this->mSize);
        ret += ",\n";
        for(unsigned int i=0; i<mSize; i++)
        {
            ret += '\t';
            ret += this->mNeighbours[i].toString();
            ret += ",\n";
        }
        ret += ']';

        return ret;
    }

protected:
    /**
    * The vector of stored neighbours.
    */
    std::vector<Point> mNeighbours;

    /**
    * Size of the neighbourhood. Determines how many neighbours could be stored in <code>this</code> object.
    */
    unsigned int mSize;

    /**
    * Provides algorithm to generate neighbours. mNeighbourhoodScheme is used to create mNeighbours vector.
    */
    NeighbourhoodScheme mNeighbourhoodScheme;
}; // class Neighbourhood


		}
	} // namespace HillClimbing
} // namespace Optimizer
