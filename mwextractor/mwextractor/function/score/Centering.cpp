
#include "../../utils/Textual.h"

#include "Centering.h"


namespace function
{
	namespace score
	{


double Centering::computeMean(KBestTupleList const& pKBest) const
{
	double mean = 0.0;

	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		mean += pKBest[i].score;
	}

	return mean / static_cast<double>(pKBest.size());
}


void Centering::scoreKBest(KBestTupleList& pKBest) const
{
	double mean = computeMean(pKBest);

	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		pKBest[i].score -= mean;
	}
}


void Centering::scoreFeatures(TupleFeatureStorage& pFeatureStorage) const
{
	for (
		auto inst = pFeatureStorage.getInstanceMap().begin();
		inst != pFeatureStorage.getInstanceMap().end();
		++inst)
	{
		for (size_t f = 0; f < pFeatureStorage.getFeatureCount(); ++f)
		{
			inst->second.getFeatureVector()[f] -= mMeans[f];
		}
	}
}


void Centering::buildForFeatures(TupleFeatureStorage const& pFeatureStorage)
{
	mMeans.resize(pFeatureStorage.getFeatureCount());
	for (size_t f = 0; f < pFeatureStorage.getFeatureCount(); ++f)
	{
		mMeans[f] = pFeatureStorage.computeFeatureMean(f);
	}
}


void Centering::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	mMeans.resize(pUnnamedParameters.size());
	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		size_t idx = utils::toSizeT(iter->first);
		mMeans[idx] = utils::toSizeT(iter->second);
	}
}


std::string	Centering::name() const
{
	return "centering";
}


std::string Centering::reprezentation() const
{
	std::stringstream str;
	str << name() << '(';
	for (size_t i = 0; i < mMeans.size(); ++i)
	{
		str << mMeans[i];
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
