
#include <cstring>

#include "Extractor.h"


namespace function
{
	namespace association
	{


auto Extractor::extract(
	AssociationMeasurePtrS const& 	pMeasure,
	TupleIdVector const&			pTupleIdVector,
	size_t 							pRankSize,
	size_t							pThreadCount) const -> KBestTupleList
{
	KBestTupleStructure kbestStructure(pRankSize);

	std::vector<AssociationMeasurePtrS> measures(pThreadCount);
	for (size_t t = 0; t < pThreadCount; ++t)
	{
		measures[t] = pMeasure->copy();
	}

	std::mutex add;
	utils::parallelFor(
		0,
		pTupleIdVector.size(),
		[&](size_t pThreadId, size_t pJob)
	{
		KBestTupleList::Element element;
		element.element	= pTupleIdVector[pJob];
		element.score	= measures[pThreadId]->rank(element.element);
		add.lock();
		kbestStructure.addElement(element);
		add.unlock();
	}, pThreadCount);

	return kbestStructure.retrieveKBest();
}


auto Extractor::extract(
	VectorAssociationMeasurePtrS const& pVectorMeasure,
	TupleIdVector const&				pTupleIdVector,
	size_t 								pRankSize,
	size_t								pThreadCount) const -> KBestTupleListVector
{
	size_t pFunctionCount = pVectorMeasure->size();

	std::vector<KBestTupleStructure> kbestStructureVector(pFunctionCount, KBestTupleStructure(pRankSize));
	KBestTupleListVector kbestResult(pFunctionCount);

	std::vector<VectorAssociationMeasurePtrS> measures(pThreadCount);
	for (size_t t = 0; t < pThreadCount; ++t)
	{
		measures[t] = pVectorMeasure->copy();
	}

	std::vector<std::mutex> add(pFunctionCount);
	utils::parallelFor(
		0,
		pTupleIdVector.size(),
		[&](size_t pThreadId, size_t pJob)
	{
		std::vector<double> result = measures[pThreadId]->rank(pTupleIdVector[pJob]);
		XASSERT(
			result.size() == measures[pThreadId]->size(),
			"Extractor::extract(): Computed " << result.size() << " result for tuple, but should be " << measures[pThreadId]->size() << '.');
		for (size_t r = 0; r < result.size(); ++r)
		{
			KBestTupleList::Element element;
			element.element	= pTupleIdVector[pJob];
			element.score	= result[r];
			add[r].lock();
			kbestStructureVector[r].addElement(element);
			add[r].unlock();
		}
	}, pThreadCount);

	utils::parallelFor(
		0,
		pFunctionCount,
		[&](size_t pThreadId, size_t pJob)
	{
		kbestResult[pJob] = kbestStructureVector[pJob].retrieveKBest();
		XASSERT(
			kbestResult[pJob].size() == std::min(pTupleIdVector.size(), pRankSize),
			"Extractor::extract(): Extracted kbest size " << kbestResult[pJob].size() << ", should be " << std::min(pTupleIdVector.size(), pRankSize) << '.');
	}, std::min(pThreadCount, pFunctionCount));

	return kbestResult;
}


auto Extractor::extractUnranked(
	VectorAssociationMeasurePtrS const& pVectorMeasure,
	TupleIdVector const&				pTupleIdVector,
	size_t								pThreadCount) const -> VectorAssociationResult
{
	size_t pFunctionCount = pVectorMeasure->size();

	VectorAssociationResult result(pTupleIdVector.size(), pFunctionCount, 0.0);

	std::vector<VectorAssociationMeasurePtrS> measures(pThreadCount);
	for (size_t t = 0; t < pThreadCount; ++t)
	{
		measures[t] = pVectorMeasure->copy();
	}

	utils::parallelFor(
		0,
		pFunctionCount,
		[&](size_t pThreadId, size_t pJob)
	{
		std::vector<double> vector = measures[pThreadId]->rank(pTupleIdVector[pJob]);
		XASSERT(
			vector.size() == pFunctionCount,
			"Extractor::extract(): Computed " << vector.size() << " result for tuple, but should be " << measures[pThreadId]->size() << '.');
		memcpy(result.getRow(pJob), vector.data(), sizeof(double) * pFunctionCount);
	}, pThreadCount);

	return result;
}


	}
}
