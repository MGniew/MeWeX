
#include "../../utils/Debug.h"

#include "AbstractRanker.h"


namespace function
{
	namespace association
	{


auto AbstractRanker::getRankerData() const -> RankerDataPtrS const&
{
	return mRankerData;
}


bool AbstractRanker::hasRankerData() const
{
	return getRankerData() != nullptr;
}


void AbstractRanker::setRankerData(RankerDataPtrS const& pRankerData)
{
	mRankerData = pRankerData;
}


void AbstractRanker::initialize(RankerDataPtrS const& pRankerData)
{
	setRankerData(pRankerData);
}


	}
}
