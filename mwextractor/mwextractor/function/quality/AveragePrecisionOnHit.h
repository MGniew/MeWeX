
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


/*
 * Based on Paradowski's program
 */
class AveragePrecisionOnHit : public QualityFunction
{
public:
	AveragePrecisionOnHit(size_t pLength = std::numeric_limits<size_t>::max());

	AveragePrecisionOnHit(AveragePrecisionOnHit&&					pAveragePrecisionOnHit)	= default;
	AveragePrecisionOnHit(AveragePrecisionOnHit const& 				pAveragePrecisionOnHit) = default;
	AveragePrecisionOnHit& operator=(AveragePrecisionOnHit&& 		pAveragePrecisionOnHit)	= default;
	AveragePrecisionOnHit& operator=(AveragePrecisionOnHit const& 	pAveragePrecisionOnHit)	= default;

	virtual ~AveragePrecisionOnHit() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
