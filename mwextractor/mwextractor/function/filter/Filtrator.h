
#pragma once

#include <memory>

#include "Filter.h"


namespace function
{
	namespace filter
	{


class Filtrator
{
public:
	typedef Filter::TupleStorage 		TupleStorage;
	typedef TupleStorage::TupleIdVector	TupleIdVector;
	typedef std::shared_ptr<Filter>		FilterPtrS;

public:
	TupleIdVector operator()(
		TupleStorage const&	pStorage,
		FilterPtrS const& 	pFilter) const;

	template <typename C>
	TupleIdVector operator()(
		C const&			pContainer,
		FilterPtrS const& 	pFilter) const;
};


template <typename C>
auto Filtrator::operator()(
	C const&			pContainer,
	FilterPtrS const& 	pFilter) const -> TupleIdVector
{
	TupleIdVector ids;

	for (auto iter = pContainer.begin(); iter != pContainer.end(); ++iter)
	{
		if (pFilter->meets(*iter))
		{
			ids.push_back(*iter);
		}
	}

	return ids;
}


	}
}
