/*
 * VariationCoefficient.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "StandardDeviation.h"


namespace function
{
	namespace dispersion
	{


class VariationCoefficient : public StandardDeviation
{
public:
	VariationCoefficient()																= default;
	VariationCoefficient(VariationCoefficient&& 				pVariationCoefficient)	= default;
	VariationCoefficient(VariationCoefficient const& 			pVariationCoefficient)	= default;
	VariationCoefficient& operator=(VariationCoefficient&& 		pVariationCoefficient)	= default;
	VariationCoefficient& operator=(VariationCoefficient const& pVariationCoefficient)	= default;

	virtual ~VariationCoefficient() = default;


	virtual double disperse(TupleId pTupleId) const override;

	virtual std::string	name() const override;
};


	}
}
