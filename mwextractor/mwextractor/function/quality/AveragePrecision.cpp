
#include "AveragePrecision.h"


namespace function
{
	namespace quality
	{


AveragePrecision::AveragePrecision(size_t pLength)
:
	QualityFunction(pLength)
{

}


auto AveragePrecision::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(length);

	double sum = 0.0;
	double relevant = 0.0;
	for(size_t k = 0; k < length; ++k)
	{
		if (pRelevantSet.has(pKBest[k].element))
		{
			++relevant;
		}

		sum += relevant / static_cast<double>(k + 1);

		mtx[k][0] = sum / static_cast<double>(k + 1);
	}

	return mtx;
}


std::string	AveragePrecision::name() const
{
	return "average_precision";
}


	}
}
