
#include "AveragePrecisionRecallCurve.h"


namespace function
{
	namespace quality
	{


AveragePrecisionRecallCurve::AveragePrecisionRecallCurve(size_t pLength)
:
	QualityFunction(pLength)
{

}


auto AveragePrecisionRecallCurve::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	size_t theSize = 0;
	for(size_t k = 0; k < length; ++k)
	{
		if (pRelevantSet.has(pKBest[k].element))
		{
			++theSize;
		}
	}

	QualityMatrix mtx(theSize);

	double precisionSum = 0.0;
	double relevant = 0.0;
	size_t index = 0;
	for(size_t k = 0; k < length; ++k)
	{
		bool isRelevant = pRelevantSet.has(pKBest[k].element);

		if (isRelevant)
		{
			++relevant;
		}

		precisionSum += relevant / static_cast<double>(k + 1);

		if (isRelevant)
		{
			mtx[index][0] = precisionSum / static_cast<double>(k + 1);
			++index;
		}
	}

	return mtx;
}


std::string	AveragePrecisionRecallCurve::name() const
{
	return "average_precision_recall_curve";
}


	}
}
