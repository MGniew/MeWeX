
#include <limits>

#include "../../utils/Math.h"
#include "Disperser.h"


namespace function
{
	namespace dispersion
	{


auto Disperser::dispersTuples(
	DispersionFunctionPtrS const& 	pFunction,
	bool 							pInverseDispersionValues) const -> TupleDispersionVectorPtrS
{
	XASSERT(
		pFunction->getDispersionData()->hasMatrixTupleStorage(),
		"Disperser::dispersTuples(): Matrix tuple storage not set.");

	TupleStoragePtrS const& storage = pFunction->getDispersionData()->getMatrixTupleStorage();

	TupleDispersionVectorPtrS result(new TupleDispersionVector(
		storage->getDistinctTupleCount(), std::pair<TupleId, double>(nullptr, 0.0)));

	double minDispersion = std::numeric_limits<double>::max();
	double maxDispersion = -std::numeric_limits<double>::max();
	size_t i = 0;
	for (auto t = storage->beginTuples(); t != storage->endTuples(); ++t)
	{
		TupleId tid	= storage->findTupleId(t);

		double dispersion = pFunction->disperse(tid);

		(*result)[i].first 	= tid;
		(*result)[i].second	= dispersion;
		++i;

		minDispersion = std::min(minDispersion, dispersion);
		maxDispersion = std::max(maxDispersion, dispersion);
	}

	if (pInverseDispersionValues)
	{
		double minMaxSum = minDispersion + maxDispersion;
		for (size_t i = 0; i < result->size(); ++i)
		{
			(*result)[i].second = -(*result)[i].second + minMaxSum;
		}
	}

	return result;
}


size_t Disperser::updateStorage(
	TupleDispersionVectorPtrS const& 	pDispersionVector,
	TupleStoragePtrS const& 			pOutputTupleStorage,
	double								pThreshold) const
{
	size_t removed 	= 0;
	double sum 		= 0.0;
	for (auto iter = pDispersionVector->begin(); iter != pDispersionVector->end(); ++iter)
	{
		if (iter->second > pThreshold)
		{
			sum += iter->second;
			pOutputTupleStorage->findTuple(iter->first).getMetadata().setGlobalFrequency(iter->second);
		}
		else
		{
			++removed;
			pOutputTupleStorage->removeTuple(iter->first);
		}
	}
	pOutputTupleStorage->setTupleGlobalFrequency(sum);

	return removed;
}


size_t Disperser::dispersTuplesInPlace(
	DispersionFunctionPtrS const& 	pFunction,
	TupleStoragePtrS const& 		pOutputTupleStorage,
	bool 							pInverseDispersionValues,
	double							pThreshold) const
{
	auto const& dispVec = dispersTuples(pFunction, pInverseDispersionValues);
	return updateStorage(dispVec, pFunction->getDispersionData()->getMatrixTupleStorage(), pThreshold);
}


double Disperser::sum(TupleDispersionVectorPtrS const& pVector) const
{
	double sum = 0.0;
	for (size_t i = 0; i < pVector->size(); ++i)
	{
		sum += (*pVector)[i].second;
	}
	return sum;
}


	}
}
