/*
 * PearsonsChiSquare.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "AssociationFunction.h"


namespace function
{
	namespace association
	{


/*
 * one-tiled chi^2 by me
 *
 * TODO: What if expected is equal to 0?
 */
class WChiSquare : public AssociationFunction
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
