
#pragma once

#include "AssociationFunction.h"


namespace function
{
	namespace association
	{


/**
 * Based on mwe by Mariusz Paradowski
 */
class OddsRatio : public AssociationFunction
{
public:
	virtual AssociationMeasurePtrS copy() const override;

	virtual double rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const override;

	virtual std::string	name() const override;
};


	}
}
