
#pragma once

#include "ScoreFunction.h"


namespace function
{
	namespace score
	{


/**
 * \brief Centrowanie danych do zera i wariancji jednostkowej.
 *
 *	Artykuł: "Combining Association Measures for Collocation Extraction Pavel Pecina and Pavel Schlesinger"
 *	Kod filtru Weka: Standarize.java
 */
class Standarization : public ScoreFunction
{
public:
	double computeVariance(
		KBestTupleList const& 	pKBest,
		double 					pMean) const;

	virtual void scoreKBest(KBestTupleList& 		pKBest) 					const override;
	virtual void scoreFeatures(TupleFeatureStorage& pFeatureStorage)			const override;

	virtual void buildForFeatures(TupleFeatureStorage const& pFeatureStorage)	override;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);

	virtual std::string	name() 				const override;
	virtual std::string reprezentation() 	const override;

public:
	std::vector<double> mMeans;
	std::vector<double> mStdDev;
};


	}
}
