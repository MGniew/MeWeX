/*
 * AverageBigram.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "AssociationFunctionBased.h"


namespace function
{
	namespace association
	{


/*
 *	Based on:
 *	Extending lexical association measures for collocation extraction
 *	G3 pattern
 */
class AverageBigram : public AssociationFunctionBased
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
