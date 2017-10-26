

#include "And.h"


namespace function
{
	namespace filter
	{


bool And::meets(TupleId pTupleId) const
{
	bool result = false;
	for (size_t i = 0; (!result) && (i < getFilterVector().size()); ++i)
	{
		result = !getFilterVector()[i]->meets(pTupleId);
	}
	return !result;
}


std::string And::name() const
{
	return "and";
}


	}
}
