
#pragma once

#include "ScoreFunction.h"


namespace function
{
	namespace score
	{


class Centering : public ScoreFunction
{
public:
	double computeMean(KBestTupleList const& pKBest) const;


	virtual void scoreKBest(KBestTupleList& 		pKBest) 					const override;
	virtual void scoreFeatures(TupleFeatureStorage& pFeatureStorage)			const override;

	virtual void buildForFeatures(TupleFeatureStorage const& pFeatureStorage)	override;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);

	virtual std::string	name() 				const override;
	virtual std::string reprezentation() 	const override;

private:
	std::vector<double> mMeans;
};


	}
}
