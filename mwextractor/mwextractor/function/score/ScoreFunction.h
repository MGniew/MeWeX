
#pragma once

#include "../../structure/storage/KBestTupleList.h"
#include "../../structure/storage/TupleFeatureStorage.h"

#include "../Function.h"


namespace function
{
	namespace score
	{


class ScoreFunction : public Function
{
public:
	typedef structure::storage::TupleFeatureStorage TupleFeatureStorage;
	typedef structure::storage::KBestTupleList 		KBestTupleList;

public:
	virtual void scoreKBest(KBestTupleList& 		pKBest) 			const = 0;
	virtual void scoreFeatures(TupleFeatureStorage& pFeatureStorage)	const = 0;

	virtual void operator()(KBestTupleList& 		pKBest) 			const;
	virtual void operator()(TupleFeatureStorage& 	pFeatureStorage) 	const;

	virtual void buildForFeatures(TupleFeatureStorage const& pFeatureStorage)	= 0;
};


	}
}
