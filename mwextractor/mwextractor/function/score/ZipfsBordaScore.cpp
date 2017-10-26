
#include "ZipfsBordaScore.h"


namespace function
{
	namespace score
	{


void ZipfsBordaScore::scoreKBest(KBestTupleList& pKBest) const
{
	for (size_t i = 0; i < pKBest.size(); ++i)
	{
		pKBest[i].score = 1.0 / static_cast<double>(i + 1);
	}
}


void ZipfsBordaScore::scoreFeatures(TupleFeatureStorage& pFeatureStorage) const
{
	EXCEPTION(false, "ZipfsBordaScore::score(): Not implemented yet.");
}


void ZipfsBordaScore::buildForFeatures(TupleFeatureStorage const& pFeatureStorage)
{
	EXCEPTION(false, "ZipfsBordaScore::buildForFeatures(): Not implemented");
}


std::string	ZipfsBordaScore::name() const
{
	return "zipfs_borda_score";
}


	}
}
