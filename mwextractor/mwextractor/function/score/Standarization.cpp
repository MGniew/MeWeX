
#include <cmath>

#include "../../utils/Textual.h"

#include "Centering.h"
#include "Standarization.h"


namespace function
{
	namespace score
	{


double Standarization::computeVariance(
	KBestTupleList const& 	pKBest,
	double 					pMean) const
{
	double variance = 0.0;

	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		variance += (pKBest[i].score - pMean) * (pKBest[i].score - pMean);
	}

	return variance / static_cast<double>(pKBest.size());
}


void Standarization::scoreKBest(KBestTupleList& pKBest) const
{
	double mean = Centering().computeMean(pKBest);
	double stdDev = std::sqrt(computeVariance(pKBest, mean));

	/* Don't divde by zero coz of black holes */
	if (stdDev == 0.0)
	{
		stdDev = 1.0;
	}

	double oneByStdDev = 1.0 / stdDev;

	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		pKBest[i].score -= mean;
		pKBest[i].score *= oneByStdDev;
	}
}


void Standarization::scoreFeatures(TupleFeatureStorage& pFeatureStorage) const
{
	for (
		auto inst = pFeatureStorage.getInstanceMap().begin();
		inst != pFeatureStorage.getInstanceMap().end();
		++inst)
	{
		for (size_t f = 0; f < pFeatureStorage.getFeatureCount(); ++f)
		{
			inst->second.getFeatureVector()[f] -= mMeans[f];
			inst->second.getFeatureVector()[f] /= mStdDev[f];
		}
	}
}

void Standarization::buildForFeatures(TupleFeatureStorage const& pFeatureStorage)
{
	mMeans.resize(pFeatureStorage.getFeatureCount());
	mStdDev.resize(pFeatureStorage.getFeatureCount());
	for (size_t f = 0; f < pFeatureStorage.getFeatureCount(); ++f)
	{
		mMeans[f] = pFeatureStorage.computeFeatureMean(f);
		mStdDev[f] = pFeatureStorage.computeFeatureStandardDeviation(f, mMeans[f]);
	}
}


void Standarization::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	EXCEPTION(pUnnamedParameters.size() % 2 == 0, "Standarization::build(): Value count % 2 != 0.");

	mMeans.resize(pUnnamedParameters.size() >> 1);
	mStdDev.resize(mMeans.size());
	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		size_t idx = utils::toSizeT(iter->first);
		double val = utils::toDouble(iter->second);

		size_t idxb = idx >> 1;
		size_t offset = idx & 1;
		if (offset == 0)
		{
			mMeans[idxb] = val;
		}
		else
		{
			mStdDev[idxb] = val;
		}
	}
}


std::string	Standarization::name() const
{
	return "standarization";
}


std::string Standarization::reprezentation() const
{
	std::stringstream str;
	str << name() << '(';
	for (size_t i = 0; i < mMeans.size(); ++i)
	{
		str << mMeans[i] << ',' << mStdDev[i];
		if (i < mMeans.size() - 1)
		{
			str << ',';
		}
	}
	str << ')';
	return str.str();
}


	}
}
