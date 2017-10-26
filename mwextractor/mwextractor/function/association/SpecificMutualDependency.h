/*
 * NaiveMD.h
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
 * Mutual Dependency
 *
 * Based on:
 * Comparative Evaluation of Collocation Extraction Metrics
 * 	Aristomenis Thanopoulos,
 * 	Nikos Fakotakis,
 * 	George Kokkinakis
 *
 * 	Generalized using Total Correlation
 *
 * 	TODO: What if observed is equal to 0?
 */
class SpecificMutualDependency : public AssociationFunction
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
