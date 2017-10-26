
#pragma once

#include "OddsRatio.h"


namespace function
{
	namespace association
	{


/**
 * Based on mwe by Mariusz Paradowski
 */
class UnigramSubtuples : public OddsRatio
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
