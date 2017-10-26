
#include "Classifier.h"


namespace machine_learning
{


auto Classifier::copy()	const -> AssociationMeasurePtrS
{
	return clone();
}


double Classifier::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return rank(pTupleId);
}


}
