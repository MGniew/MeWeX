
#include <sstream>

#include "../../utils/Textual.h"

#include "FeatureFilter.h"


namespace function
{
	namespace filter
	{


FeatureFilter::FeatureFilter(
	OperatorType 					pOperatorType,
	StringParameterVector const&	pParameters)
:
	mParameters(pParameters),
	mOperatorType(pOperatorType)
{
	assignOperator(pOperatorType);
}


FeatureFilter::FeatureFilter()
:
	mOperator(nullptr),
	mOperatorType(OperatorType::EQUAL)
{

}


auto FeatureFilter::retrieveFunctionParameters() const -> StringParameterMap
{
	return {{"file", "none"}};
}


void FeatureFilter::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	mParameters.resize(pUnnamedParameters.size() - 1);
	std::string operatorType;

	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		if (iter->first != "0")
		{
			mParameters[utils::toSizeT(iter->first) - 1] = iter->second;
		}
		else
		{
			operatorType = iter->second;
		}
	}

	{
		auto iter = pNamedParameters.find("file");
		if (iter != pNamedParameters.end())
		{
			mFile = iter->second;
		}
	}

	assignOperator(decodeOperatorName(operatorType));
}


bool FeatureFilter::meets(TupleId pTupleId) const
{
	return (this->*mOperator)(pTupleId);
}


auto FeatureFilter::getOperatorType() const -> OperatorType
{
	return mOperatorType;
}


std::string FeatureFilter::decodeOperatorType() const
{
	switch (mOperatorType)
	{
		case OperatorType::EQUAL:
		{
			return "==";
		}
		break;
		case OperatorType::LOWER:
		{
			return "<";
		}
		break;
		case OperatorType::GREATER:
		{
			return ">";
		}
		break;
		case OperatorType::LOWER_EQUAL:
		{
			return "<=";
		}
		break;
		case OperatorType::GREATER_EQUAL:
		{
			return ">=";
		}
		break;
		case OperatorType::IN:
		{
			return "^";
		}
		break;
		default:
		{
			XASSERT(false, std::string("FeatureFilter::decodeOperatorType(): Unknown operator type."));
		}
	}
	return "==";
}


std::vector<std::string> const& FeatureFilter::getParameters() const
{
	return mParameters;
}


std::vector<std::string>& FeatureFilter::getParameters()
{
	return mParameters;
}


std::string	const& FeatureFilter::getParameterFile() const
{
	return mFile;
}


std::string& FeatureFilter::getParameterFile()
{
	return mFile;
}


std::string FeatureFilter::reprezentation() const
{
	std::stringstream str;
	str << name() << '(' << decodeOperatorType();
	for (auto iter = mParameters.begin(); iter != mParameters.end(); ++iter)
	{
		str << ',' << (*iter);
	}
	if (!mFile.empty())
	{
		str << ",file=" << mFile;
	}
	str << ')';
	return str.str();
}


std::string FeatureFilter::usage() const
{
	std::stringstream str;
	str << name() << "(<operator_type>[,file=<path_to_file>][,<argument_1>][,<argument_2>][, ...])";
	return str.str();
}


bool FeatureFilter::equal(TupleId pTupleId) const
{
	EXCEPTION(false, "FeatureFilter::equal(): equal() not implemented for '" << name() << "'.");
	return false;
}


bool FeatureFilter::lower(TupleId pTupleId) const
{
	EXCEPTION(false, "FeatureFilter::lower(): lower() not implemented for '" << name() << "'.");
	return false;
}


bool FeatureFilter::greater(TupleId pTupleId) const
{
	EXCEPTION(false, "FeatureFilter::greater(): greater() not implemented for '" << name() << "'.");
	return false;
}


bool FeatureFilter::lowerEqual(TupleId pTupleId) const
{
	EXCEPTION(false, "FeatureFilter::lowerEqual(): lowerEqual() not implemented for '" << name() << "'.");
	return false;
}


bool FeatureFilter::greaterEqual(TupleId pTupleId) const
{
	EXCEPTION(false, "FeatureFilter::greaterEqual(): greaterEqual() not implemented for '" << name() << "'.");
	return false;
}


bool FeatureFilter::in(TupleId pTupleId) const
{
	EXCEPTION(false, "FeatureFilter::in(): in() not implemented for '" << name() << "'.");
	return false;
}


auto FeatureFilter::decodeOperatorName(std::string const& pOperatorType) const -> OperatorType
{
	if (pOperatorType == "==")
	{
		return OperatorType::EQUAL;
	}
	else if (pOperatorType == "<")
	{
		return OperatorType::LOWER;
	}
	else if (pOperatorType == ">")
	{
		return OperatorType::GREATER;
	}
	else if (pOperatorType == "<=")
	{
		return OperatorType::LOWER_EQUAL;
	}
	else if (pOperatorType == ">=")
	{
		return OperatorType::GREATER_EQUAL;
	}
	else if (pOperatorType == "^")
	{
		return OperatorType::IN;
	}

	EXCEPTION(false, "FeatureFilter::assignOperator(): Unknown operator type '" << pOperatorType << "'.");

	return OperatorType::EQUAL;
}


void FeatureFilter::assignOperator(OperatorType pOperatorType)
{
	mOperatorType = pOperatorType;
	switch (mOperatorType)
	{
		case OperatorType::EQUAL:
		{
			mOperator = &FeatureFilter::equal;
		}
		break;
		case OperatorType::LOWER:
		{
			mOperator = &FeatureFilter::lower;
		}
		break;
		case OperatorType::GREATER:
		{
			mOperator = &FeatureFilter::greater;
		}
		break;
		case OperatorType::LOWER_EQUAL:
		{
			mOperator = &FeatureFilter::lowerEqual;
		}
		break;
		case OperatorType::GREATER_EQUAL:
		{
			mOperator = &FeatureFilter::greaterEqual;
		}
		break;
		case OperatorType::IN:
		{
			mOperator = &FeatureFilter::in;
		}
		break;
		default:
		{
			XASSERT(false, std::string("FeatureFilter::assignOperator(): Unknown operator type."));
		}
	}
}


	}
}
