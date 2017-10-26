
#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include <algorithm>

#include "../utils/Debug.h"
#include "../utils/Random.h"


namespace machine_learning
{


/**
 * \brief Klasa budująca foldy z zadanego zestawu danych.
 */
template <typename T>
class FoldsBuilder
{
public:
	enum class Policy
	{
		WITHOUT_REPEATS = 0,
		WITHOUT_REPEATS_BALANCED,
		WITH_REPEATS
	};

	typedef typename std::vector<T> Fold;
	typedef std::vector<Fold>		FoldVector;

	struct FoldPair
	{
		Fold train;
		Fold test;
	};

public:
	FoldsBuilder()											= default;
	FoldsBuilder(FoldsBuilder&& pBuilder) 					= default;
	FoldsBuilder(FoldsBuilder const& pBuilder) 				= default;
	FoldsBuilder& operator=(FoldsBuilder&& pBuilder) 		= default;
	FoldsBuilder& operator=(FoldsBuilder const& pBuilder) 	= default;

	virtual ~FoldsBuilder() = default;

	template <typename C>
	FoldVector build(
		C const& 	pContainer,
		size_t		pFoldCount,
		Policy		pPolicy = Policy::WITHOUT_REPEATS) const;

	/**
	 * \brief Łączy foldy z zadanego wektora z wyłączeniem foldu o indeksie zadanym parametrem.
	 *
	 * @param pFoldVector wektor foldów do połączenia
	 * @param pTestFoldIdx indeks foldu, który ma być pominięty podczas łączenia
	 */
	Fold mergeFolds(
		FoldVector const& 	pFoldVector,
		size_t				pTestFoldIdx) const;

private:
	template <typename C>
	FoldVector createFoldsWithoutRepeats(
		C const& 	pContainer,
		size_t		pFoldCount) const;

	template <typename C>
	FoldVector createFoldsWithoutRepeatsBalanced(
		C const& 	pContainer,
		size_t		pFoldCount) const;

	template <typename C>
	FoldVector createFoldsWithRepeats(
		C const& 	pContainer,
		size_t		pFoldCount) const;
};


template <typename T>
template <typename C>
auto FoldsBuilder<T>::build(
	C const& 	pContainer,
	size_t		pFoldCount,
	Policy		pPolicy) const -> FoldVector
{
	switch(pPolicy)
	{
		case Policy::WITHOUT_REPEATS:
		{
			return createFoldsWithoutRepeats(pContainer, pFoldCount);
		}
		break;
		case Policy::WITHOUT_REPEATS_BALANCED:
		{
			return createFoldsWithoutRepeatsBalanced(pContainer, pFoldCount);
		}
		break;
		case Policy::WITH_REPEATS:
		{
			return createFoldsWithRepeats(pContainer, pFoldCount);
		}
		break;
		default:
		{
			XASSERT(false, "FoldsBuilder<T>::build(): Unknown fold creation policy.");
		}
	}
}


template <typename T>
auto FoldsBuilder<T>::mergeFolds(
	FoldVector const& 	pFoldVector,
	size_t				pTestFoldIdx) const -> Fold
{
	XASSERT(pTestFoldIdx < pFoldVector.size(), "FoldsBuilder<T>::buildFromFolds(): test fold index out of bounds.");

	Fold fold;

	size_t instanceCount = 0;
	for (size_t i = 0; i < pFoldVector.size(); ++i)
	{
		instanceCount += pFoldVector[i].size();
	}

	fold.reserve(instanceCount - pFoldVector[pTestFoldIdx].size());

	for (size_t f = 0; f < pFoldVector.size(); ++f)
	{
		if (pTestFoldIdx != f)
		{
			fold.insert(fold.end(), pFoldVector[f].begin(), pFoldVector[f].end());
		}
	}

	return fold;
}


template <typename T>
template <typename C>
auto FoldsBuilder<T>::createFoldsWithoutRepeats(
	C const& 	pContainer,
	size_t		pFoldCount) const -> FoldVector
{
	std::vector<T> allElements(pContainer.begin(), pContainer.end());
	std::random_shuffle(allElements.begin(), allElements.end());

	FoldVector folds(pFoldCount);
	for (size_t i = 0; i < allElements.size(); ++i)
	{
		size_t foldIndex = i % pFoldCount;
		folds[foldIndex].push_back(allElements[i]);
	}

	return folds;
}


template <typename T>
template <typename C>
auto FoldsBuilder<T>::createFoldsWithoutRepeatsBalanced(
	C const& 	pContainer,
	size_t		pFoldCount) const -> FoldVector
{
	std::vector<T> allElements(pContainer.begin(), pContainer.end());
	std::random_shuffle(allElements.begin(), allElements.end());

	size_t size = allElements.size() - (allElements.size() % pFoldCount);

	FoldVector folds(pFoldCount);
	for (size_t i = 0; i < size; ++i)
	{
		size_t foldIndex = i % pFoldCount;
		folds[foldIndex].push_back(allElements[i]);
	}

	return folds;
}


template <typename T>
template <typename C>
auto FoldsBuilder<T>::createFoldsWithRepeats(
	C const& 	pContainer,
	size_t		pFoldCount) const -> FoldVector
{
	std::vector<T> allElements(pContainer.begin(), pContainer.end());

	FoldVector folds(pFoldCount);
	for (size_t i = 0; i < allElements.size(); ++i)
	{
		size_t foldIndex = i % pFoldCount;
		folds[foldIndex].push_back(allElements[utils::rand64() % allElements.size()]);
	}

	return folds;
}


}
