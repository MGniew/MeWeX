
#include <sstream>

#include "../../utils/Textual.h"

#include "RecallBasedQualityFunction.h"


namespace function
{
	namespace quality
	{


RecallBasedQualityFunction::RecallBasedQualityFunction(
	bool 	pUseSourceSize,
	size_t 	pLength)
:
	QualityFunction(pLength),
	mUseSourceSize(pUseSourceSize)
{

}


bool RecallBasedQualityFunction::getUseSourceSize() const
{
	return mUseSourceSize;
}


void RecallBasedQualityFunction::setUseSourceSize(bool pUseSourceSize)
{
	mUseSourceSize = pUseSourceSize;
}


auto RecallBasedQualityFunction::retrieveFunctionParameters() const -> StringParameterMap
{
	return {
		{"length", std::to_string(std::numeric_limits<size_t>::max())},
		{"use_source_size", "1"}
	};
}


void RecallBasedQualityFunction::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	QualityFunction::build(pParameters, pUnnamedParameters);
	mUseSourceSize = utils::toBool(pParameters.find("use_source_size")->second);
}


std::string RecallBasedQualityFunction::reprezentation() const
{
	std::stringstream str;
	str << name() << "(length=" << getLength() << ",use_source_size=" << (mUseSourceSize ? '1' : '0') << ')';
	return str.str();
}


std::string RecallBasedQualityFunction::usage() const
{
	std::stringstream str;
	str << name() << "(use_source_size=<if_use_item_count_from_file_instead_of_read_item_count>,length=<kbest_list_length_to_score>)";
	return str.str();
}


	}
}
