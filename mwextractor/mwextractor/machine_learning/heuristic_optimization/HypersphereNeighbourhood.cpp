#include "HypersphereNeighbourhood.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


HypersphereNeighbourhood::HypersphereNeighbourhood(void)
{
    this->mRadius = 1.0;
}

HypersphereNeighbourhood::HypersphereNeighbourhood(const HypersphereNeighbourhood& rHypersphereNeighbourhood)
{
    this->mRadius = rHypersphereNeighbourhood.mRadius;
}

HypersphereNeighbourhood::~HypersphereNeighbourhood(void)
{}

double HypersphereNeighbourhood::distance(const Point& rPoint1, const Point& rPoint2)
{
    double distance = 0.0;
    Data tmp1, tmp2, diff;
    unsigned int size = rPoint1.getNumberOfParameters();
    if(rPoint2.getNumberOfParameters() != size)
    {
        throw Exception::Exception("Incompatible Points.");
    }
    unsigned int sizeParam;
    for(unsigned int i=0; i<size; i++)
    {
        sizeParam = rPoint2.getParameterAt(i).getSize();
        for(unsigned int j=0; j<sizeParam; j++)
        {
            tmp1 = rPoint1.getParameterAt(i).getValueAt(j);
            tmp2 = rPoint2.getParameterAt(i).getValueAt(j);
            diff = tmp1 - tmp2;
            distance += dataCast<double>(diff*diff);
        }
    }
    return sqrt(distance);
}

Point HypersphereNeighbourhood::getNeighbour(const Point& rPoint)
{
    unsigned int size = rPoint.getNumberOfParameters();
    unsigned int sizeParam;
    double p;
    Point neighbour;
    double dist;
    do
    {
        neighbour = rPoint;
        for(unsigned int i=0; i<size; i++)
        {
            sizeParam = rPoint.getParameterAt(i).getSize();
            for(unsigned int j=0; j<sizeParam; j++)
            {
                if(Random::random() > 0.5)
                {
                    neighbour.getParameterAt(i).setRandomValue(j);
                }
            }
        }
        dist = this->distance(rPoint, neighbour);
    }
    while((dist > this->mRadius) || (dist < COMPARE_PRECISION));
    neighbour.getEvaluationPerformance().clear();
    return neighbour;
}

const double HypersphereNeighbourhood::COMPARE_PRECISION = 1e-6;

	}
}
