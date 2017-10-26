
#include <sstream>
#include <unordered_map>
#include <vector>

#include "../../utils/Time.h"
#include "../../utils/Parallel.h"
#include "../../utils/Textual.h"

#include "../FunctionFactory.h"
#include "AggregationFunction.h"


namespace function
{
	namespace aggregation
	{


auto AggregationFunction::retrieveFunctionParameters() const -> StringParameterMap
{
	return {{"score", "none"}};
}


void AggregationFunction::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	std::string scoreFunctionString = pNamedParameters.find("score")->second;
	if (!scoreFunctionString.empty())
	{
		mScoreFunction = FunctionFactory().createScoreFunction(scoreFunctionString);
	}

	mWeights.resize(pUnnamedParameters.size());
	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		mWeights[utils::toSizeT(iter->first)] = utils::toDouble(iter->second);
	}
}


std::vector<double> const& AggregationFunction::getWeightVector() const
{
	return mWeights;
}


std::vector<double>& AggregationFunction::getWeightVector()
{
	return mWeights;
}


auto AggregationFunction::getScoreFunction() const -> ScoreFunctionPtrS const&
{
	return mScoreFunction;
}


auto AggregationFunction::getScoreFunction() -> ScoreFunctionPtrS&
{
	return mScoreFunction;
}


auto AggregationFunction::aggregateKBestVector(
	KBestTupleListVector& 	pKBestTupleListVector,
	size_t					pThreadCount) const -> KBestTupleList
{
	if (mScoreFunction != nullptr)
	{
		utils::parallelFor(0, pKBestTupleListVector.size(),
			[&](size_t pThreadId, size_t pI)
		{
			(*mScoreFunction)(pKBestTupleListVector[pI]);
		}, pThreadCount);
	}

	/*if (mScoreFunction != nullptr)
	{
		for(size_t i = 0; i < pKBestTupleListVector.size(); ++i)
		{
			(*mScoreFunction)(pKBestTupleListVector[i]);
		}
	}*/

	std::unordered_map<TupleStorage::TupleId, std::vector<double>> aggregated;

	size_t measureCount = pKBestTupleListVector.size();
	for (size_t i = 0; i < measureCount; ++i)
	{
		for (size_t e = 0; e < pKBestTupleListVector[i].size(); ++e)
		{
			auto tid = pKBestTupleListVector[i][e].element;
			double s = pKBestTupleListVector[i][e].score;
			auto res = aggregated.insert(std::make_pair(tid, std::vector<double>(measureCount, 0.0)));
			res.first->second[i] = s;
		}
	}

	KBestTupleStructure structure(pKBestTupleListVector[0].size());
	for (auto i = aggregated.begin(); i != aggregated.end(); ++i)
	{
		double res = compute(i->second);
		structure.addElement(KBestTupleList::Element(i->first, res));
	}

	/*AggregatedMap aggregated;
	computeKBestVector(pKBestTupleListVector, aggregated);

	KBestTupleStructure structure(pKBestTupleListVector[0].size());
	for (auto i = aggregated.begin(); i != aggregated.end(); ++i)
	{
		structure.addElement(KBestTupleList::Element(i->first, i->second));
	}*/

	return structure.retrieveKBest();
}


auto AggregationFunction::aggregateVectorResult(
	VectorAssociationResult const& 	pVectorAssociationResult,
	TupleIdVector const&			pTupleIdVector,
	size_t							pKBestLength) const -> KBestTupleList
{
	KBestTupleStructure output(pKBestLength);

	std::vector<double> temp(pVectorAssociationResult.getRowSize());
	for (size_t i = 0; i < pVectorAssociationResult.size(); ++i)
	{
		for (size_t j = 0; j < temp.size(); ++j)
		{
			temp[j] = pVectorAssociationResult.getRowPart(i, j);
		}
		double res = compute(temp);
		output.addElement(KBestTupleList::Element(pTupleIdVector[i], res));
	}

	return output.retrieveKBest();
}


auto AggregationFunction::operator()(
	KBestTupleListVector& 	pKBestTupleListVector,
	size_t					pThreadCount) const -> KBestTupleList
{
	return aggregateKBestVector(pKBestTupleListVector, pThreadCount);
}



auto AggregationFunction::operator()(
	VectorAssociationResult const& 	pVectorAssociationResult,
	TupleIdVector const&			pTupleIdVector,
	size_t							pKBestLength) const -> KBestTupleList
{
	return aggregateVectorResult(pVectorAssociationResult, pTupleIdVector, pKBestLength);
}


std::string AggregationFunction::reprezentation() const
{
	std::stringstream str;
	utils::setStreamMaxDoublePrecision(str);

	str << name() << '(';

	if (mScoreFunction != nullptr)
	{
		str << "score=" << mScoreFunction->reprezentation();
		if (mWeights.size() > 0)
		{
			str << ',';
		}
	}

	for (size_t i = 0; i < mWeights.size(); ++i)
	{
		str << mWeights[i];
		if (i < mWeights.size() - 1)
		{
			str << ',';
		}
	}

	str << ')';

	return str.str();
}


std::string AggregationFunction::usage() const
{
	std::stringstream str;
	str << name();
	str << "(score=<score_function_definition>,<weight_for_first_ranking>[,<weight_for_next_ranking>][, ...])";
	return str.str();
}


	}
}
