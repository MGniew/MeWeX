
#include "Function.h"


namespace function
{


auto Function::retrieveFunctionParameters() const -> StringParameterMap
{
	return {};
}


void Function::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{

}


std::string Function::reprezentation() const
{
	return name() + "()";
}


std::string Function::usage() const
{
	return name() + "()";
}


}
