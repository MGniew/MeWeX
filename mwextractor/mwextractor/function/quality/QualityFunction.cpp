
#include "../../utils/Textual.h"

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


QualityFunction::QualityFunction(size_t pLength)
:
	mLength(pLength)
{

}


auto QualityFunction::retrieveFunctionParameters() const -> StringParameterMap
{
	return {{"length", std::to_string(std::numeric_limits<size_t>::max())}};
}


void QualityFunction::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	mLength = utils::toSizeT(pNamedParameters.find("length")->second);
}


std::string QualityFunction::reprezentation() const
{
	std::stringstream str;
	str << name() << "(length=" << getLength() << ")";
	return str.str();
}


std::string QualityFunction::usage() const
{
	std::stringstream str;
	str << name() << "(length=<kbest_list_length_to_score>)";
	return str.str();
}


size_t QualityFunction::getLength() const
{
	return mLength;
}


size_t QualityFunction::getResultRowSize() const
{
	return 1;
}


	}
}
