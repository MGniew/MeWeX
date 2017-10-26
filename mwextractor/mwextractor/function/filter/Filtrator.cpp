
#include "Filtrator.h"


namespace function
{
	namespace filter
	{


auto Filtrator::operator()(
	TupleStorage const&	pStorage,
	FilterPtrS const& 	pFilter) const -> TupleIdVector
{
	TupleIdVector ids;

	for (auto iter = pStorage.beginTuples(); iter != pStorage.endTuples(); ++iter)
	{
		auto tid = pStorage.findTupleId(iter);
		if (pFilter->meets(tid))
		{
			ids.push_back(tid);
		}
	}

	return ids;
}


	}
}
