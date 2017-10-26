
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


class AveragePrecisionRecallCurve : public QualityFunction
{
public:
	AveragePrecisionRecallCurve(size_t pLength = std::numeric_limits<size_t>::max());

	AveragePrecisionRecallCurve(AveragePrecisionRecallCurve&&					pAveragePrecisionRecallCurve) = default;
	AveragePrecisionRecallCurve(AveragePrecisionRecallCurve const& 				pAveragePrecisionRecallCurve) = default;
	AveragePrecisionRecallCurve& operator=(AveragePrecisionRecallCurve&& 		pAveragePrecisionRecallCurve) = default;
	AveragePrecisionRecallCurve& operator=(AveragePrecisionRecallCurve const& 	pAveragePrecisionRecallCurve) = default;

	virtual ~AveragePrecisionRecallCurve() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
