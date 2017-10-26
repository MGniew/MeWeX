
#include "RecallCurve.h"


namespace function
{
	namespace quality
	{


RecallCurve::RecallCurve(
	bool 	pUseSourceSize,
	size_t 	pLength)
:
	RecallBasedQualityFunction(pUseSourceSize, pLength)
{

}


auto RecallCurve::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(length);

	double relevantSize = getUseSourceSize() ?
		pRelevantSet.sourceSize() :
		pRelevantSet.size();

	double rel = 0.0;
	for(size_t k = 0; k < length; ++k)
	{
		if (pRelevantSet.has(pKBest[k].element))
		{
			++rel;
		}
		mtx[k][0] = rel / relevantSize;
	}

	return mtx;
}


std::string RecallCurve::name() const
{
	return "recall_curve";
}


	}
}
