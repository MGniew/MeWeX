
#include "Filter.h"


namespace function
{
	namespace filter
	{


auto Filter::getMatrixTupleStorage() const -> TupleStoragePtrS const&
{
	return mTupleStorage;
}


bool Filter::operator()(TupleId pTupleId) const
{
	return meets(pTupleId);
}


void Filter::initialize(TupleStoragePtrS const& pStorage)
{
	mTupleStorage = pStorage;
	construct();
}


	}
}
