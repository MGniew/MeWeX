
#pragma once

#include "FeatureFilter.h"


namespace function
{
	namespace filter
	{


class Relation : public FeatureFilter
{
private:
	typedef TupleStorage::RelationIdSet RelationIdSet;

public:
	Relation(
		OperatorType 					pOperatorType,
		StringParameterVector const&	pRelationNames);

	Relation()										= default;
	Relation(Relation&& 				pFilter) 	= default;
	Relation(Relation const& 			pFilter) 	= default;
	Relation& operator=(Relation&& 		pFilter) 	= default;
	Relation& operator=(Relation const& pFilter) 	= default;

	virtual ~Relation() = default;


	virtual std::string name() const override;

protected:
	virtual void construct() override;

	virtual bool in(TupleId pTupleId) const override;

private:
	RelationIdSet mRelationIdSet;
};


	}
}
