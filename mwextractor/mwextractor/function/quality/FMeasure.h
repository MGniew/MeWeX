
#pragma once

#include "RecallBasedQualityFunction.h"


namespace function
{
	namespace quality
	{


class FMeasure : public RecallBasedQualityFunction
{
public:
	FMeasure(
		double 	pBeta			= 1.0,
		bool	pUseSourceSize	= true,
		size_t 	pLength 		= std::numeric_limits<size_t>::max());

	FMeasure(FMeasure&&					pFMeasure)	= default;
	FMeasure(FMeasure const& 			pFMeasure) 	= default;
	FMeasure& operator=(FMeasure&& 		pFMeasure)	= default;
	FMeasure& operator=(FMeasure const& pFMeasure)	= default;

	virtual ~FMeasure() = default;


	virtual StringParameterMap retrieveFunctionParameters() const;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);


	double valueFor(
		double pPrecision,
		double pRecall) const;

	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;


	virtual std::string	name() 				const;
	virtual std::string	reprezentation() 	const;

private:
	double 	mBeta;
};


	}
}
