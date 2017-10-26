/*
 * SpecificCorrelation.h
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


/*
 * Based on observation of pmi variations (p(xy), p(xy)^2, p(xy)^3).
 * Function is similar to FSCP introduced by Buczy�ski.
 */
class SpecificExponentialCorrelation : public AssociationFunction
{
public:
	SpecificExponentialCorrelation(double pExponent = 1.0);

	SpecificExponentialCorrelation(SpecificExponentialCorrelation&& 				pFunction) = default;
	SpecificExponentialCorrelation(SpecificExponentialCorrelation const& 			pFunction) = default;
	SpecificExponentialCorrelation& operator=(SpecificExponentialCorrelation&& 		pFunction) = default;
	SpecificExponentialCorrelation& operator=(SpecificExponentialCorrelation const& pFunction) = default;

	virtual ~SpecificExponentialCorrelation() = default;

	virtual AssociationMeasurePtrS copy() const override;


	double getExponent() const;

	virtual double rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const override;

	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual std::string	name() 				const override;
	virtual std::string reprezentation() 	const override;
	virtual std::string usage() 			const override;


private:
	double mExponent;
};


	}
}
