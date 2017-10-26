
#include <sstream>

#include "../FunctionFactory.h"
#include "AssociationFunctionBased.h"


namespace function
{
	namespace association
	{


AssociationFunctionBased::AssociationFunctionBased(AssociationFunctionBased const& pAssociationFunctionBased)
{
	if (pAssociationFunctionBased.hasInnerAssociationFunction())
	{
		setInnerAssociationFunction(copyInnerAssociationFunction());
	}
}


AssociationFunctionBased& AssociationFunctionBased::operator=(AssociationFunctionBased const& pAssociationFunctionBased)
{
	if (pAssociationFunctionBased.hasInnerAssociationFunction())
	{
		setInnerAssociationFunction(copyInnerAssociationFunction());
	}
	return (*this);
}


auto AssociationFunctionBased::retrieveFunctionParameters() const -> StringParameterMap
{
	return {{"inner", ""}};
}


void AssociationFunctionBased::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	mInnerAssociationFunction = FunctionFactory().createAssociationFunction(
		pNamedParameters.find("inner")->second);
}


std::string AssociationFunctionBased::reprezentation()	const
{
	std::stringstream str;
	str << name() << "(inner=" << mInnerAssociationFunction->reprezentation() << ')';
	return str.str();
}


std::string AssociationFunctionBased::usage() const
{
	std::stringstream str;
	str << name() << "(inner=<association_function_definition>)";
	return str.str();
}


auto AssociationFunctionBased::getInnerAssociationFunction() const -> AssociationFunctionPtrS const&
{
	return mInnerAssociationFunction;
}


auto AssociationFunctionBased::getInnerAssociationFunction() -> AssociationFunctionPtrS&
{
	return mInnerAssociationFunction;
}


bool AssociationFunctionBased::hasInnerAssociationFunction() const
{
	return getInnerAssociationFunction() != nullptr;
}


void AssociationFunctionBased::setInnerAssociationFunction(AssociationFunctionPtrS const& pInnerAssocitionFunction)
{
	mInnerAssociationFunction = pInnerAssocitionFunction;
}


auto AssociationFunctionBased::copyInnerAssociationFunction() const -> AssociationFunctionPtrS
{
	return std::static_pointer_cast<AssociationFunction>(mInnerAssociationFunction->copy());
}


	}
}
