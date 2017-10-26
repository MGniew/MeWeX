/*
 * WOrder.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "AbstractOrderAssociationFunction.h"


namespace function
{
	namespace association
	{


class WOrder : public AbstractOrderAssociationFunction
{
public:
	virtual AssociationMeasurePtrS copy() const override;


	virtual double rank(TupleId pTupleId) const override;


	virtual std::string	name() const override;
};


	}
}
