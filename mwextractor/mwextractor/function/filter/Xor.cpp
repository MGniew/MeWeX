

#include "Xor.h"


namespace function
{
	namespace filter
	{


bool Xor::meets(TupleId pTupleId) const
{
	bool result = false;
	for (size_t i = 0; i < getFilterVector().size(); ++i)
	{
		result ^= getFilterVector()[i]->meets(pTupleId);
	}
	return result;
}


std::string Xor::name() const
{
	return "xor";
}


	}
}
