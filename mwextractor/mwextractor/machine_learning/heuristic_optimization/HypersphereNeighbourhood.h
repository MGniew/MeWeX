#pragma once

#include <math.h>

#include "Point.h"
#include "Data.h"
#include "Random.h"
#include "Exception/Exception.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* The HypersphereNeighbourhood provides scheme of the neighbourhood generation.
* Given point P is in the centre of the hypersphere - the central point.
* All of the neighbours are inside the hypersphere, around the central point.
* The points are generated randomly. A other points (other features) do not belong
* to the neighbourhood of point P.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class HypersphereNeighbourhood
{
public:
    HypersphereNeighbourhood(void);

    template<typename ArgumentsType>
    HypersphereNeighbourhood(const ArgumentsType& rArgs)
    {
        this->mRadius = rArgs.getRadius();
    }

    HypersphereNeighbourhood(const HypersphereNeighbourhood& rHypersphereNeighbourhood);

    ~HypersphereNeighbourhood(void);

    double distance(const Point& rPoint1, const Point& rPoint2);

    Point getNeighbour(const Point& rPoint);

private:
    double mRadius;
    static const double COMPARE_PRECISION;
}; // class HypersphereNeighbourhood


	}
} // namespace Optimizer
