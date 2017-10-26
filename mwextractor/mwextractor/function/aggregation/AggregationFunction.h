
#pragma once

#include <map>
#include <memory>

#include "../../structure/storage/KBestTupleList.h"
#include "../../structure/storage/VectorAssociationResult.h"

#include "../score/ScoreFunction.h"


namespace function
{
	namespace aggregation
	{


class AggregationFunction : public Function
{
public:
	typedef std::shared_ptr<score::ScoreFunction>					ScoreFunctionPtrS;

	typedef structure::storage::KBestTupleStructure					KBestTupleStructure;
	typedef structure::storage::KBestTupleList						KBestTupleList;
	typedef structure::storage::KBestTupleListVector 				KBestTupleListVector;
	typedef structure::storage::VectorAssociationResult				VectorAssociationResult;
	typedef structure::storage::MatrixTupleStorage::TupleIdVector	TupleIdVector;

protected:
	typedef typename KBestTupleList::ScoreType 		_Score;
	typedef typename KBestTupleList::ElementType 	_Element;
	typedef std::pair<_Element, _Score>				_Insert;

public:
	typedef std::map<_Element, _Score> AggregatedMap;

public:
	virtual StringParameterMap retrieveFunctionParameters() const;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);


	std::vector<double> const&	getWeightVector() const;
	std::vector<double>&		getWeightVector();

	ScoreFunctionPtrS const&	getScoreFunction() const;
	ScoreFunctionPtrS&			getScoreFunction();


	virtual KBestTupleList aggregateKBestVector(
		KBestTupleListVector& 	pKBestTupleListVector,
		size_t					pThreadCount) const;

	virtual KBestTupleList aggregateVectorResult(
		VectorAssociationResult const& 	pVectorAssociationResult,
		TupleIdVector const&			pTupleIdVector,
		size_t							pKBestLength) const;

	KBestTupleList operator()(
		KBestTupleListVector& 	pKBestTupleListVector,
		size_t					pThreadCount) const;

	KBestTupleList operator()(
		VectorAssociationResult const& 	pVectorAssociationResult,
		TupleIdVector const&			pTupleIdVector,
		size_t							pKBestLength) const;


	virtual std::string reprezentation() const override;

	virtual std::string usage() const override;

protected:
	virtual double compute(std::vector<double> const& pValues) const = 0;

private:
	std::vector<double>	mWeights;
	ScoreFunctionPtrS 	mScoreFunction;
};


	}
}
