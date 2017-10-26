
#pragma once

#include "ScoreFunction.h"


namespace function
{
	namespace score
	{


class Normalization : public ScoreFunction
{
public:
	virtual void scoreKBest(KBestTupleList& 		pKBest) 					const override;
	virtual void scoreFeatures(TupleFeatureStorage& pFeatureStorage)			const override;

	virtual void buildForFeatures(TupleFeatureStorage const& pFeatureStorage)	override;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);

	virtual std::string	name() 				const override;
	virtual std::string reprezentation() 	const override;

private:
	std::vector<std::pair<double, double>> mMinMax;
};


	}
}
