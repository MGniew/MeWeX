
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


class PrecisionCurve : public QualityFunction
{
public:
	PrecisionCurve(size_t pLength = std::numeric_limits<size_t>::max());

	PrecisionCurve(PrecisionCurve&&					pPrecisionCurve)	= default;
	PrecisionCurve(PrecisionCurve const& 			pPrecisionCurve) 	= default;
	PrecisionCurve& operator=(PrecisionCurve&& 		pPrecisionCurve)	= default;
	PrecisionCurve& operator=(PrecisionCurve const& pPrecisionCurve)	= default;

	virtual ~PrecisionCurve() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
