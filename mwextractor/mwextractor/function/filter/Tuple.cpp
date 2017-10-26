
#include <sstream>

#include "../../utils/Textual.h"
#include "../../structure/io/StreamingFileReader.h"

#include "Tuple.h"


namespace function
{
	namespace filter
	{


Tuple::Tuple(
	OperatorType 					pOperatorType,
	StringParameterVector const&	pTuples,
	ElementOrder					pElementOrder)
:
	FeatureFilter(pOperatorType, pTuples),
	mTupleElementOrder(pElementOrder)
{

}

Tuple::Tuple()
:
	FeatureFilter(),
	mTupleElementOrder(ElementOrder::FIXED)
{

}


auto Tuple::retrieveFunctionParameters() const -> StringParameterMap
{
	return {{"file", "none"}, {"fixed", "1"}};
}


void Tuple::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	FeatureFilter::build(pNamedParameters, pUnnamedParameters);

	mTupleElementOrder = utils::toBool(pNamedParameters.find("fixed")->second) ?
		ElementOrder::FIXED : ElementOrder::FLEXIBLE;
}


void Tuple::construct()
{
	Loader loader;

	if (!getParameterFile().empty())
	{
		Loader::RelevantTupleSet set = loader.readTuples(getParameterFile());
		for (size_t i = 0; i < getParameters().size(); ++i)
		{
			set.insert(loader.parseLine(getParameters()[i]));
		}

		mTupleIdSet = loader.buildSet(*getMatrixTupleStorage(), set, mTupleElementOrder);
	}
}


bool Tuple::in(TupleId pTupleId) const
{
	return mTupleIdSet->has(pTupleId);
}


std::string Tuple::name() const
{
	return "tuple";
}


std::string Tuple::reprezentation() const
{
	std::stringstream str;
	str << name() << '(' << decodeOperatorType();
	for (auto iter = getParameters().begin(); iter != getParameters().end(); ++iter)
	{
		str << ',' << (*iter);
	}
	if (!getParameterFile().empty())
	{
		str << ",file=" << getParameterFile();
	}
	str << ",fixed=" << (mTupleElementOrder == ElementOrder::FIXED ? '1' : '0') << ')';
	return str.str();
}


	}
}
