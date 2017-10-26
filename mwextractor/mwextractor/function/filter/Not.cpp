

#include "Not.h"


namespace function
{
	namespace filter
	{


bool Not::meets(TupleId pTupleId) const
{
	EXCEPTION(
		getFilterVector().size() == 1,
		"Not::meets(): Only single inner value is valid, passed " << getFilterVector().size() << '.');
	return !getFilterVector()[0]->meets(pTupleId);
}


std::string Not::name() const
{
	return "not";
}


	}
}
