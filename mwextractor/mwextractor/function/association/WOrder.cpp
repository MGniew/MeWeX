
#include <sstream>

#include "WOrder.h"


namespace function
{
	namespace association
	{


auto WOrder::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new WOrder(*this));
}


double WOrder::rank(TupleId pTupleId) const
{
	typedef structure::storage::RelationStorage::RelationId			RelationId;
	typedef structure::storage::RelationStorage::RelationIdVector 	RelationIdVector;

	auto const& 				storage 			= getRankerData()->getMatrixTupleStorage();
	MatrixTupleStorage::TupleT 	tuple 				= storage->findTuple(pTupleId);
	RelationId					relationId 			= tuple.getRelation();
	size_t						relationGroupIdx	= storage->findRelation(relationId).getGroup();

	auto schemeIter = getRelationScheme().find(relationGroupIdx);
	EXCEPTION(schemeIter != getRelationScheme().end(), "WOrder::rank(): No scheme for relation group '" << relationGroupIdx << "' and tuple '" << storage->createRelationReprezentation(relationId) << "' defined.");

	RelationIdVector const& relationGroup = schemeIter->second;

	double max = 0;
	std::vector<double> elements(relationGroup.size());
	for (size_t i = 0; i < relationGroup.size(); ++i)
	{
		tuple.setRelation(relationGroup[i]);
		TupleId tupleId = storage->findTupleIdSilent(tuple);

		if (tupleId == nullptr || !getRankerData()->isTupleIdValid(tupleId))
		{
			elements[i] = 0.0;
		}
		else
		{
			elements[i] = storage->findTuple(tupleId).getMetadata().getGlobalFrequency();
		}

		max = std::max(max, elements[i]);
	}

	double result = 1.0;
	for (size_t i = 0; i < elements.size(); ++i)
	{
		result *= 1.0 + (elements[i] / (max + 1.0));
	}

	return 1.0 / result;
}


std::string WOrder::name() const
{
	return "w_order";
}


	}
}
