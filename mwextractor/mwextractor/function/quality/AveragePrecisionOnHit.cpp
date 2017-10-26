
#include "AveragePrecisionOnHit.h"


namespace function
{
	namespace quality
	{


AveragePrecisionOnHit::AveragePrecisionOnHit(size_t pLength)
:
	QualityFunction(pLength)
{

}


auto AveragePrecisionOnHit::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(pRelevantSet.size());

	double sum = 0.0;
	double relevant = 0.0;
	size_t index = 0;
	for(size_t k = 0; k < length; ++k)
	{
		bool isRelevant = pRelevantSet.has(pKBest[k].element);
		if (isRelevant)
		{
			++relevant;
			sum = sum + (relevant / static_cast<double>(k + 1.0));
			mtx[index][0] = sum / relevant;
			++index;
		}
	}

	return mtx;
}


std::string	AveragePrecisionOnHit::name() const
{
	return "average_precision_on_hit";
}


	}
}
