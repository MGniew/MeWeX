/*
 * JuillandD.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "VariationCoefficient.h"


namespace function
{
	namespace dispersion
	{


class JuillandD : public VariationCoefficient
{
public:
	JuillandD()														= default;
	JuillandD(JuillandD&& 					pDispersionFunction)	= default;
	JuillandD(JuillandD const& 				pDispersionFunction)	= default;
	JuillandD& operator=(JuillandD&& 		pDispersionFunction)	= default;
	JuillandD& operator=(JuillandD const& 	pDispersionFunction)	= default;

	virtual ~JuillandD() = default;


	virtual double disperse(TupleId pTupleId) const override;

	virtual std::string	name() const override;
};


	}
}
