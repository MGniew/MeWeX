
#include "Hit.h"


namespace function
{
	namespace quality
	{


Hit::Hit(size_t pLength)
:
	QualityFunction(pLength)
{

}


auto Hit::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(length);
	for(size_t k = 0; k < length; ++k)
	{
		mtx[k][0] = pRelevantSet.has(pKBest[k].element) ? 1 : 0;
	}

	return mtx;
}


std::string Hit::name() const
{
	return "hit";
}


	}
}
