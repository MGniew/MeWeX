
#include <sstream>

#include "WTFOrder.h"


namespace function
{
	namespace association
	{


auto WTFOrder::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new WTFOrder(*this));
}


double WTFOrder::rank(TupleId pTupleId) const
{
	double worder = WOrder::rank(pTupleId);

	double frequency = getRankerData()->getMatrixTupleStorage()->
		findTuple(pTupleId).getMetadata().getGlobalFrequency();

	return frequency * worder;
}


std::string WTFOrder::name() const
{
	return "w_tf_order";
}


	}
}
