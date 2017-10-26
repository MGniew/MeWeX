/*
 * SpecificCorrelation.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "SpecificExponentialCorrelation.h"


namespace function
{
	namespace association
	{


/*
 * Based on my idea.
 * SEC extension with WSC modification
 */
class WSpecificExponentialCorrelation : public SpecificExponentialCorrelation
{
public:
	WSpecificExponentialCorrelation(double pExponent = 1.0);

	WSpecificExponentialCorrelation(WSpecificExponentialCorrelation&& 					pFunction) = default;
	WSpecificExponentialCorrelation(WSpecificExponentialCorrelation const& 				pFunction) = default;
	WSpecificExponentialCorrelation& operator=(WSpecificExponentialCorrelation&& 		pFunction) = default;
	WSpecificExponentialCorrelation& operator=(WSpecificExponentialCorrelation const& 	pFunction) = default;

	virtual ~WSpecificExponentialCorrelation() = default;

	virtual AssociationMeasurePtrS copy() const override;


	virtual double rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const override;

	virtual std::string	name() const override;
};


	}
}
