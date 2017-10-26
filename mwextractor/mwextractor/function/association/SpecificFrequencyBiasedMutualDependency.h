/*
 * NaiveFBMD.h
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
 * Log Frequency Biased Mutual Dependency
 *
 * Based on:
 * Comparative Evaluation of Collocation Extraction Metrics
 * 	Aristomenis Thanopoulos,
 * 	Nikos Fakotakis,
 * 	George Kokkinakis
 *
 * 	Generalized by me using Total Correlation
 *
 * 	TODO: What if observed is equal to 0?
 */
class SpecificFrequencyBiasedMutualDependency : public AssociationFunction
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
