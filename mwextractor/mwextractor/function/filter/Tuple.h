
#pragma once

#include <unordered_set>

#include "FeatureFilter.h"

#include "../../structure/io/RelevantTupleSetLoader.h"


namespace function
{
	namespace filter
	{


class Tuple : public FeatureFilter
{
private:
	typedef structure::io::RelevantTupleSetLoader	Loader;
	typedef Loader::RelevantTupleIdSetPtrS			TupleIdSetPtrS;

public:
	typedef Loader::ElementOrder ElementOrder;

public:
	Tuple(
		OperatorType 					pOperatorType,
		StringParameterVector const&	pTuples,
		ElementOrder					pElementOrder);

	Tuple();
	Tuple(Tuple&& 					pFilter) 	= default;
	Tuple(Tuple const& 				pFilter) 	= default;
	Tuple& operator=(Tuple&& 		pFilter) 	= default;
	Tuple& operator=(Tuple const& 	pFilter) 	= default;

	virtual ~Tuple() = default;


	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual std::string name() 				const override;
	virtual std::string reprezentation() 	const override;

protected:
	virtual void construct() override;

	virtual bool in(TupleId pTupleId) const override;

private:
	TupleIdSetPtrS	mTupleIdSet;
	ElementOrder	mTupleElementOrder;
};


	}
}
