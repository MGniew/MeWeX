
#pragma once

#include "AveragePrecisionRecallCurve.h"


namespace function
{
	namespace quality
	{


class MeanAveragePrecision : public AveragePrecisionRecallCurve
{
public:
	MeanAveragePrecision(
		size_t pLength = std::numeric_limits<size_t>::max(),
		double pFrom = 0.0,
		double pTo = 1.0);

	MeanAveragePrecision(MeanAveragePrecision&&					pMeanAveragePrecision) = default;
	MeanAveragePrecision(MeanAveragePrecision const& 				pMeanAveragePrecision) = default;
	MeanAveragePrecision& operator=(MeanAveragePrecision&& 		pMeanAveragePrecision) = default;
	MeanAveragePrecision& operator=(MeanAveragePrecision const& 	pMeanAveragePrecision) = default;

	virtual ~MeanAveragePrecision() = default;


	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() 				const override;
	virtual std::string reprezentation()	const override;

private:
	double mFrom;
	double mTo;
};


	}
}
