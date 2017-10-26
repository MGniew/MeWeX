
#pragma once

#include "RecallBasedQualityFunction.h"


namespace function
{
	namespace quality
	{


class PrecisionRecallCurve : public RecallBasedQualityFunction
{
public:
	PrecisionRecallCurve(
		bool 	pUseSourceSize	= true,
		size_t 	pLength 		= std::numeric_limits<size_t>::max());

	PrecisionRecallCurve(PrecisionRecallCurve&&					pPrecisionRecallCurve)	= default;
	PrecisionRecallCurve(PrecisionRecallCurve const& 			pPrecisionRecallCurve) 	= default;
	PrecisionRecallCurve& operator=(PrecisionRecallCurve&& 		pPrecisionRecallCurve)	= default;
	PrecisionRecallCurve& operator=(PrecisionRecallCurve const& pPrecisionRecallCurve)	= default;

	virtual ~PrecisionRecallCurve() = default;

	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
