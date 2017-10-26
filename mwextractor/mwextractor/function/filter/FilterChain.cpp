
#include <sstream>

#include "FilterChain.h"
#include "../FunctionFactory.h"


namespace function
{
	namespace filter
	{


void FilterChain::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	FunctionFactory ff;
	for (auto i = pUnnamedParameters.begin(); i != pUnnamedParameters.end(); ++i)
	{
		addFilter(ff.createFilterFunction(i->second));
	}
}


void FilterChain::construct()
{
	for (size_t i = 0; i < mFilterVector.size(); ++i)
	{
		mFilterVector[i]->initialize(getMatrixTupleStorage());
	}
}


void FilterChain::addFilter(FilterPtrS const& pFilter)
{
	mFilterVector.push_back(pFilter);
}


auto FilterChain::getFilterVector() const -> FilterVector const&
{
	return mFilterVector;
}


auto FilterChain::getFilterVector() -> FilterVector&
{
	return mFilterVector;
}


std::string FilterChain::reprezentation() const
{
	std::stringstream str;
	str << name() << '(';

	for (size_t i = 0; i < mFilterVector.size(); ++i)
	{
		str << mFilterVector[i]->reprezentation();
		if (i < (mFilterVector.size() - 1))
		{
			str << ',';
		}
	}

	str << ')';
	return str.str();
}


std::string FilterChain::usage() const
{
	std::stringstream str;
	str << name() << "(<filter_definition>[,<filter_definition>][, ...])";
	return str.str();
}


	}
}
