
#include <iostream>

#include "../../structure/io/StreamingFileReader.h"

#include "Relation.h"


namespace function
{
	namespace filter
	{


Relation::Relation(
	OperatorType 					pOperatorType,
	StringParameterVector const&	pRelationNames)
:
	FeatureFilter(pOperatorType, pRelationNames)
{

}


void Relation::construct()
{
	for (size_t i = 0; i < getParameters().size(); ++i)
	{
		mRelationIdSet.insert(getMatrixTupleStorage()->findRelationId(getParameters()[i]));
	}

	if (!getParameterFile().empty())
	{
		structure::io::StreamingFileReader reader(getParameterFile());
		std::string line;
		while (reader.readline(line))
		{
			mRelationIdSet.insert(getMatrixTupleStorage()->findRelationId(line));
		}
	}
}


bool Relation::in(TupleId pTupleId) const
{
	return mRelationIdSet.find(getMatrixTupleStorage()->findTuple(pTupleId).getRelation()) != mRelationIdSet.end();
}


std::string Relation::name() const
{
	return "relation";
}


	}
}
