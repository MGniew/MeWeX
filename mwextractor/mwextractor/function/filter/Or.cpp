

#include "Or.h"


namespace function
{
	namespace filter
	{


bool Or::meets(TupleId pTupleId) const
{
	bool result = false;
	for (size_t i = 0; (!result) && (i < getFilterVector().size()); ++i)
	{
		result = getFilterVector()[i]->meets(pTupleId);
	}
	return result;
}


std::string Or::name() const
{
	return "or";
}


	}
}
