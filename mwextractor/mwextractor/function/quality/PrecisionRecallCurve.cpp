
#include "PrecisionRecallCurve.h"


namespace function
{
	namespace quality
	{


PrecisionRecallCurve::PrecisionRecallCurve(
	bool 	pUseSourceSize,
	size_t 	pLength)
:
	RecallBasedQualityFunction(pUseSourceSize, pLength)
{

}


auto PrecisionRecallCurve::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(length, 2);

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
		double precision 	= rel / (k + 1);
		double recall		= rel / relevantSize;
		mtx[k][0] = precision;
		mtx[k][1] = recall;
	}

	return mtx;
}


std::string PrecisionRecallCurve::name() const
{
	return "precision_recall_curve";
}


	}
}
