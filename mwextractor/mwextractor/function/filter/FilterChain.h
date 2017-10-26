
#pragma once

#include <vector>
#include <memory>

#include "Filter.h"


namespace function
{
	namespace filter
	{


class FilterChain : public Filter
{
public:
	typedef std::shared_ptr<Filter>	FilterPtrS;
	typedef std::vector<FilterPtrS> FilterVector;


public:
	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	void addFilter(FilterPtrS const& pFilter);

	FilterVector const& getFilterVector() const;
	FilterVector& 		getFilterVector();

	virtual std::string reprezentation() 	const override;
	virtual std::string usage() 			const override;

protected:
	virtual void construct() override;

private:
	FilterVector mFilterVector;
};


	}
}
