/*
 * AssociationFunction.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "AssociationMeasure.h"


namespace function
{
	namespace association
	{


class AssociationFunction : public AssociationMeasure
{
public:
	AssociationFunction()																= default;
	AssociationFunction(AssociationFunction&& 					pAssociationFunction)	= default;
	AssociationFunction(AssociationFunction const& 				pAssociationFunction)	= default;
	AssociationFunction& operator=(AssociationFunction&& 		pAssociationFunction)	= default;
	AssociationFunction& operator=(AssociationFunction const& 	pAssociationFunction)	= default;

	virtual ~AssociationFunction() = default;


	virtual double rank(TupleId pTupleId) const override;
};


	}
}
