/*
 * WOrder.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "WOrder.h"


namespace function
{
	namespace association
	{


class WTFOrder : public WOrder
{
public:
	virtual AssociationMeasurePtrS copy() const override;

	virtual double rank(TupleId pTupleId) const override;

	virtual std::string	name() const override;
};


	}
}
