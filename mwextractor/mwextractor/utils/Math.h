
#pragma once

/**
 * \file Math.h
 * \brief Funkcje matematyczne.
 */


#include <cmath>

#include "Debug.h"


namespace utils
{


template <typename T>
T wrapShiftRight(T pValue, size_t pAmout)
{
	return (pValue >> pAmout) | (pValue << ((sizeof(T) << 3) - pAmout));
}


template <typename T>
T wrapShiftRight(T pValue, size_t pAmout, size_t pBorder)
{
	size_t offset = (sizeof(T) << 3) - pBorder;
	T value = ((pValue << offset) >> offset);
	value = (value >> pAmout) | (value << (pBorder - pAmout));
	return (value << offset) >> offset;
}


template <typename T>
T wrapShiftLeft(T pValue, size_t pAmout)
{
	return wrapShiftRight(pValue, (sizeof(T) << 3) - pAmout);
}


template <typename T>
T wrapShiftLeft(T pValue, size_t pAmout, size_t pBorder)
{
	size_t offset = (sizeof(T) << 3) - pBorder;
	T value = ((pValue << offset) >> offset);
	value = (value << pAmout) | (value >> (pBorder - pAmout));
	return (value << offset) >> offset;
}


template <typename T, typename Iterator>
T sum(
	Iterator pBegin,
	Iterator pEnd)
{
	T s = 0;

	while(pBegin != pEnd)
	{
		s += static_cast<T>(*pBegin);
		++pBegin;
	}

	return s;
}


template <typename Iterator>
double variance(
	Iterator 		pBegin,
	Iterator 		pEnd,
	double			pSamples,
	double			pSum)
{
	double mean 	= pSum / pSamples;
	double stdev	= 0.0;

	while (pBegin != pEnd)
	{
		stdev += ((*pBegin) - mean) * ((*pBegin) - mean);
		++pBegin;
	}

	return (stdev / (pSamples - 1));
}


template <typename Iterator>
double standardDeviation(
	Iterator 		pBegin,
	Iterator 		pEnd,
	double			pSamples,
	double			pSum)
{
	return std::sqrt(variance(pBegin, pEnd, pSamples, pSum));
}


/*
size_t factor(size_t pArgument)
{
	size_t result = pArgument;
	for (size_t i = pArgument - 1; i > 1; --i)
	{
		result *= i;
	}
	return result;
}


void generatePermutations(
	size_t 								pElementCount,
	std::vector<std::vector<size_t>>&	pPermutations)
{
	if (pElementCount == 0)
	{
		for (size_t k = 0; k < 3; ++k)
		{
			std::cerr << arr[k] << ' ';
		}
		std::cerr << std::endl;
		return;
	}

	for (int i = 0; i < pElementCount; ++i)
	{
		permutations(pElementCount - 1, pPermutations);
		int temp;
		if (pElementCount & 1 == 1)
		{
			temp = 0;
		}
		else
		{
			temp = i;
		}
		std::swap(arr[temp], arr[pElementCount - 1]);
	}
}


std::vector<std::vector<size_t>> generatePermutations(size_t pElementCount)
{
	std::vector<std::vector<size_t>> result;
	result.reserve(factor(pElementCount));
	generatePermutations(pElementCount, result);
	return result;
}
*/

}
