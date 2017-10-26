
#include "../../utils/Debug.h"
#include "../../exception/Exception.h"

#include "AssociationMeasure.h"


namespace function
{
	namespace association
	{


double AssociationMeasure::operator()(TupleId pTupleId) const
{
	return rank(pTupleId);
}


double AssociationMeasure::operator()(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return rankUsingTable(pTupleId, pContingencyTable);
}


	}
}
