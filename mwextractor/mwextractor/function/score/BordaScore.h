
#pragma once

#include "ScoreFunction.h"


namespace function
{
	namespace score
	{


class BordaScore : public ScoreFunction
{
public:
	virtual void scoreKBest(KBestTupleList& 		pKBest) 			const override;
	virtual void scoreFeatures(TupleFeatureStorage& pFeatureStorage)	const override;

	virtual void buildForFeatures(TupleFeatureStorage const& pFeatureStorage) override;

	virtual std::string	name() const override;
};


	}
}
