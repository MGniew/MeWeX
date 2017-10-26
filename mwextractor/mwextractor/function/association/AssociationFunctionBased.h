/*
 * AssociationFunctionBased.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "AssociationFunction.h"


namespace function
{
	namespace association
	{


class AssociationFunctionBased : public AssociationFunction
{
public:
	typedef std::shared_ptr<AssociationFunction> AssociationFunctionPtrS;

public:
	AssociationFunctionBased()																		= default;
	AssociationFunctionBased(AssociationFunctionBased&& 				pAssociationFunctionBased)	= default;
	AssociationFunctionBased(AssociationFunctionBased const& 			pAssociationFunctionBased);
	AssociationFunctionBased& operator=(AssociationFunctionBased&& 		pAssociationFunctionBased)	= default;
	AssociationFunctionBased& operator=(AssociationFunctionBased const& pAssociationFunctionBased);

	virtual ~AssociationFunctionBased() = default;

	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual std::string reprezentation() const override;

	virtual std::string usage() const override;


	AssociationFunctionPtrS const& 	getInnerAssociationFunction() const;
	AssociationFunctionPtrS& 		getInnerAssociationFunction();

	bool							hasInnerAssociationFunction() const;

	void setInnerAssociationFunction(AssociationFunctionPtrS const& pInnerAssocitionFunction);


	virtual AssociationFunctionPtrS copyInnerAssociationFunction() const;


private:
	AssociationFunctionPtrS mInnerAssociationFunction;
};


	}
}
