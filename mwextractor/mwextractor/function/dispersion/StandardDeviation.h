/*
 * StandardDeviation.h
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


class StandardDeviation : public DispersionFunction
{
public:
	StandardDeviation()															= default;
	StandardDeviation(StandardDeviation&& 					pStandardDeviation)	= default;
	StandardDeviation(StandardDeviation const& 				pStandardDeviation)	= default;
	StandardDeviation& operator=(StandardDeviation&& 		pStandardDeviation)	= default;
	StandardDeviation& operator=(StandardDeviation const& 	pStandardDeviation)	= default;

	virtual ~StandardDeviation() = default;


	virtual double disperse(TupleId pTupleId) const override;

	virtual std::string	name() const override;
};


	}
}
