
#pragma once

#include "RecallBasedQualityFunction.h"


namespace function
{
	namespace quality
	{


class RecallCurve : public RecallBasedQualityFunction
{
public:
	RecallCurve(
		bool 	pUseSourceSize	= true,
		size_t 	pLength 		= std::numeric_limits<size_t>::max());

	RecallCurve(RecallCurve&&					pRecallCurve)	= default;
	RecallCurve(RecallCurve const& 				pRecallCurve) 	= default;
	RecallCurve& operator=(RecallCurve&& 		pRecallCurve)	= default;
	RecallCurve& operator=(RecallCurve const& 	pRecallCurve)	= default;

	virtual ~RecallCurve() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
