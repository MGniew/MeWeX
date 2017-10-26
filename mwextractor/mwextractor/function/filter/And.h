
#pragma once

#include "FilterChain.h"


namespace function
{
	namespace filter
	{


class And : public FilterChain
{
public:
	virtual bool meets(TupleId pTupleId) const override;

	virtual std::string name() const override;
};


	}
}
