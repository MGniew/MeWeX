
#include <cmath>

#include "SpecificInformation.h"


namespace function
{
	namespace association
	{


auto SpecificInformation::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new SpecificInformation(*this));
}


double SpecificInformation::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	size_t tupleSize 	= pContingencyTable.tupleSize();
	double oneByDiv 	= 1.0 / pContingencyTable.sumObserved();

	double nominator 	= 	pContingencyTable[0].observed * oneByDiv;
	double denominator	= 	(pContingencyTable[1].observed + pContingencyTable[0].observed) *	// frequency of: ...00001
							(pContingencyTable[2].observed + pContingencyTable[0].observed) *	// frequency of: ...00010
							oneByDiv * oneByDiv;

	double previousResult = 0.0;
	if (tupleSize > 2)
	{
		previousResult = (*this)(nullptr, pContingencyTable.gatherObservedNgramData(0, tupleSize - 1));
		nominator *= pContingencyTable.gatherObservedNgramData(2, tupleSize - 2)[0].observed * oneByDiv;
	}

	return log2(nominator / denominator) - previousResult; // consider sings
}


std::string SpecificInformation::name() const
{
	return "specific_information";
}


	}
}
