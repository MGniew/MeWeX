
#include <sstream>

#include "../../utils/Debug.h"
#include "../../utils/Textual.h"

#include "../FunctionFactory.h"

#include "ScoreFunctionChain.h"


namespace function
{
	namespace score
	{


ScoreFunctionChain::ScoreFunctionChain(ScoreFunctionPtrSVector const& pScoreFunctionVector)
:
	mScoreFunctionVector(pScoreFunctionVector)
{

}


void ScoreFunctionChain::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	FunctionFactory ff;

	mScoreFunctionVector.resize(pUnnamedParameters.size());
	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		mScoreFunctionVector[utils::toSizeT(iter->first)] = ff.createScoreFunction(iter->second);
	}
}


void ScoreFunctionChain::buildForFeatures(TupleFeatureStorage const& pFeatureStorage)
{
	for (size_t i = 0; i < mScoreFunctionVector.size(); ++i)
	{
		mScoreFunctionVector[i]->buildForFeatures(pFeatureStorage);
	}
}


void ScoreFunctionChain::setScoreFunctionVector(ScoreFunctionPtrSVector const& pScoreFunctionVector)
{
	mScoreFunctionVector = pScoreFunctionVector;
}


auto ScoreFunctionChain::getScoreFunction(size_t pIndex) const -> ScoreFunctionPtrS const&
{
	XASSERT(pIndex < size(), "ScoreFunctionChain::getScoreFunction(): Index out of bounds.");
	return mScoreFunctionVector[pIndex];
}


auto ScoreFunctionChain::getScoreFunction(size_t pIndex) -> ScoreFunctionPtrS&
{
	XASSERT(pIndex < size(), "ScoreFunctionChain::getScoreFunction(): Index out of bounds.");
	return mScoreFunctionVector[pIndex];
}


auto ScoreFunctionChain::getScoreFunctionVector() const -> ScoreFunctionPtrSVector const&
{
	return mScoreFunctionVector;
}


auto ScoreFunctionChain::getScoreFunctionVector() -> ScoreFunctionPtrSVector&
{
	return mScoreFunctionVector;
}


size_t ScoreFunctionChain::size() const
{
	return mScoreFunctionVector.size();
}


std::string ScoreFunctionChain::name() const
{
	return "score_function_chain";
}


std::string ScoreFunctionChain::reprezentation() const
{
	std::stringstream str;
	str << name() << '(';
	for (size_t i = 0; i < size(); ++i)
	{
		str << getScoreFunction(i)->reprezentation();
		if ((i + 1) < size())
		{
			str << ',';
		}
	}
	str << ')';
	return str.str();
}


std::string ScoreFunctionChain::usage() const
{
	std::stringstream str;
	str << name() << "(<score_function_definition>[,<score_function_definition>][, ...])";
	return str.str();
}


void ScoreFunctionChain::scoreKBest(KBestTupleList& pKBest) const
{
	for (size_t i = 0; i < size(); ++i)
	{
		getScoreFunction(i)->scoreKBest(pKBest);
	}
}


void ScoreFunctionChain::scoreFeatures(TupleFeatureStorage& pFeatureStorage) const
{
	for (size_t i = 0; i < size(); ++i)
	{
		getScoreFunction(i)->scoreFeatures(pFeatureStorage);
	}
}


	}
}
