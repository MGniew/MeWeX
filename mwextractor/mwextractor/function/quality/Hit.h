
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


class Hit : public QualityFunction
{
public:
	Hit(size_t pLength = std::numeric_limits<size_t>::max());

	Hit(Hit&&					pHit)	= default;
	Hit(Hit const& 				pHit) 	= default;
	Hit& operator=(Hit&& 		pHit)	= default;
	Hit& operator=(Hit const& 	pHit)	= default;

	virtual ~Hit() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;
};


	}
}
