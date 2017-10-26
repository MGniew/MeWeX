/*
 * ZScore.h
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


/**
 * KBest based on tuples frequency
 */
class ZScore : public AssociationFunction
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
