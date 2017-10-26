
#include <sstream>

#include "../../utils/Textual.h"

#include "../../exception/Exception.h"

#include "../../structure/io/StreamingFileReader.h"

#include "AbstractOrderAssociationFunction.h"


namespace function
{
	namespace association
	{


void AbstractOrderAssociationFunction::initialize(RankerDataPtrS const& pRankerDataPtrS)
{
	AssociationFunction::initialize(pRankerDataPtrS);

	mRelationScheme = pRankerDataPtrS->getMatrixTupleStorage()->buildRelationScheme();
}


auto AbstractOrderAssociationFunction::getRelationScheme() const -> RelationScheme const&
{
	return mRelationScheme;
}


auto AbstractOrderAssociationFunction::getRelationScheme() -> RelationScheme&
{
	return mRelationScheme;
}


double AbstractOrderAssociationFunction::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	return rank(pTupleId);
}


	}
}
