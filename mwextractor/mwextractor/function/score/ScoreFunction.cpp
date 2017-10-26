
#include "ScoreFunction.h"


namespace function
{
	namespace score
	{


void ScoreFunction::operator()(KBestTupleList& pKBest) const
{
	return scoreKBest(pKBest);
}


void ScoreFunction::operator()(TupleFeatureStorage& pFeatureStorage) const
{
	return scoreFeatures(pFeatureStorage);
}


	}
}
