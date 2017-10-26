
#include "PrecisionCurve.h"


namespace function
{
	namespace quality
	{


PrecisionCurve::PrecisionCurve(size_t pLength)
:
	QualityFunction(pLength)
{

}


auto PrecisionCurve::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(length);

	double rel = 0.0;
	for(size_t k = 0; k < length; ++k)
	{
		if (pRelevantSet.has(pKBest[k].element))
		{
			++rel;
		}
		mtx[k][0] = rel / (k + 1);
	}

	return mtx;
}


std::string PrecisionCurve::name() const
{
	return "precision_curve";
}


	}
}
