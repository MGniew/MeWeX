
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


class AveragePrecision : public QualityFunction
{
public:
	AveragePrecision(size_t pLength = std::numeric_limits<size_t>::max());

	AveragePrecision(AveragePrecision&&					pAveragePrecision)	= default;
	AveragePrecision(AveragePrecision const& 			pAveragePrecision) = default;
	AveragePrecision& operator=(AveragePrecision&& 		pAveragePrecision)	= default;
	AveragePrecision& operator=(AveragePrecision const& pAveragePrecision)	= default;

	virtual ~AveragePrecision() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
