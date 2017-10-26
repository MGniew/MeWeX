/*
 * DistributionalConsistency.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "DispersionFunction.h"


namespace function
{
	namespace dispersion
	{


class DistributionalConsistency : public DispersionFunction
{
public:
	DistributionalConsistency()																		= default;
	DistributionalConsistency(DistributionalConsistency&& 					pDispersionFunction)	= default;
	DistributionalConsistency(DistributionalConsistency const& 				pDispersionFunction)	= default;
	DistributionalConsistency& operator=(DistributionalConsistency&& 		pDispersionFunction)	= default;
	DistributionalConsistency& operator=(DistributionalConsistency const& 	pDispersionFunction)	= default;

	virtual ~DistributionalConsistency() = default;


	virtual double disperse(TupleId pTupleId) const override;

	virtual std::string	name() const override;
};


	}
}
