
#include "../../utils/Textual.h"

#include "Normalization.h"


namespace function
{
	namespace score
	{


void Normalization::scoreKBest(KBestTupleList& pKBest) const
{
	double max = pKBest[0].score;
	double min = pKBest[pKBest.size() - 1].score;
	double diff	= max - min;
	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		pKBest[i].score -= min;
		pKBest[i].score /= diff;
	}
}


void Normalization::scoreFeatures(TupleFeatureStorage& pFeatureStorage) const
{
	for (
		auto inst = pFeatureStorage.getInstanceMap().begin();
		inst != pFeatureStorage.getInstanceMap().end();
		++inst)
	{
		for (size_t f = 0; f < pFeatureStorage.getFeatureCount(); ++f)
		{
			inst->second.getFeatureVector()[f] -= mMinMax[f].first;

			double diff = mMinMax[f].second - mMinMax[f].first;
			inst->second.getFeatureVector()[f] /= (diff != 0.0 ? diff : 1.0);
		}
	}
}


void Normalization::buildForFeatures(TupleFeatureStorage const& pFeatureStorage)
{
	TupleFeatureStorage::MinMeanMaxVector stats = pFeatureStorage.computeMinMeanMax();
	mMinMax.resize(stats.size());

	for (size_t i = 0; i < stats.size(); ++i)
	{
		mMinMax[i].first = stats[i].min;
		mMinMax[i].second = stats[i].max;
	}
}


void Normalization::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	EXCEPTION(pUnnamedParameters.size() % 2 == 0, "Normalization::build(): Value count % 2 != 0.");

	mMinMax.resize(pUnnamedParameters.size() >> 1);
	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		size_t idx = utils::toSizeT(iter->first);
		double val = utils::toDouble(iter->second);

		size_t idxb = idx >> 1;
		size_t offset = idx & 1;
		if (offset == 0)
		{
			mMinMax[idxb].first = val;
		}
		else
		{
			mMinMax[idxb].second = val;
		}
	}
}


std::string	Normalization::name() const
{
	return "normalization";
}


std::string Normalization::reprezentation() const
{
	std::stringstream str;
	str << name() << '(';
	for (size_t i = 0; i < mMinMax.size(); ++i)
	{
		str << mMinMax[i].first << ',' << mMinMax[i].second;
		if (i < (mMinMax.size() - 1))
		{
			str << ',';
		}
	}
	str << ')';
	return str.str();
}


	}
}
