
#include "../../utils/Debug.h"

#include "AssociationFunction.h"


namespace function
{
	namespace association
	{


double AssociationFunction::rank(TupleId pTupleId) const
{
	return rankUsingTable(
		pTupleId,
		getRankerData()->constructContingencyTable(pTupleId));
}


	}
}
