
#include "BordaScore.h"


namespace function
{
	namespace score
	{


void BordaScore::scoreKBest(KBestTupleList& pKBest) const
{
	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		pKBest[i].score = static_cast<double>(pKBest.size() - i);
	}
}


void BordaScore::scoreFeatures(TupleFeatureStorage& pFeatureStorage) const
{
	EXCEPTION(false, "BordaScore::score(): Not implemented yet.");
}


void BordaScore::buildForFeatures(TupleFeatureStorage const& pFeatureStorage)
{
	EXCEPTION(false, "BordaScore::buildForFeatures(): Not implemented");
}


std::string	BordaScore::name() const
{
	return "borda_score";
}


	}
}
