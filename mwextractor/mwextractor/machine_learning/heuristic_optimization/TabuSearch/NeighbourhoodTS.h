#pragma once

#include "../HillClimbing/Neighbourhood.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace TabuSearch
		{


/**
* NeighbourhoodTS is the class template to store the neighbours of given Point. The class is used in
* TabuSearch algorithm.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam NeighbourhoodScheme Class provides algorithm to generate neighbours.
* @tparam TabuListType A tabu list class.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename NeighbourhoodSchemeType,
         typename TabuListType>
class NeighbourhoodTS : public HillClimbing::Neighbourhood<ArgumentsType, NeighbourhoodSchemeType>
{
public:
    /**
    * A default constructor. Creates object with neighbourhood size = 1.
    */
    NeighbourhoodTS(void) : HillClimbing::Neighbourhood<ArgumentsType, NeighbourhoodSchemeType>()
    {}

    /**
    * Creates Neighbourhood with a neighbourhood size returned by rArgs.getNeighbourhoodSize().
    *
    * @param rArgs Argument object.
    * @param rNeighbourhoodScheme Provides algorithm to generate a neighbours.
    */
    NeighbourhoodTS(const ArgumentsType& rArgs, NeighbourhoodSchemeType& rNeighbourhoodScheme)
        : HillClimbing::Neighbourhood<ArgumentsType, NeighbourhoodSchemeType>
        (rArgs, rNeighbourhoodScheme)
    {}

    /**
    * An object destructor.
    */
    ~NeighbourhoodTS(void)
    {}

    /**
    * Generates neighbourhood of the given point. Method skips points contained in <code>rTabuList</code>.
    *
    * @param[in] rPoint Point that is a base to generate the neighbourhood.
    * @param[in] rTabuList The list of the forbidden points.
    *
    * @see Point
    */
    void generate(Point& rPoint, TabuListType& rTabuList)
    {
        this->mNeighbours.clear();
        Point neighbour;
        while(this->mNeighbours.size() < this->getSize())
        {
            neighbour = this->mNeighbourhoodScheme.getNeighbour(rPoint);
            if(!rTabuList.contain(neighbour))
            {
                this->mNeighbours.push_back(neighbour);
            }
        }
    }
}; // class NeighbourhoodTS


		}
	} // namespace TabuSearch
} // namespace Optimizer
