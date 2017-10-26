/*
 * RawFrequencyStorage.cpp
 *
 *  Created on: 08-07-2014
 *      Author: michalw
 */

#include <sstream>

#include "../../utils/Math.h"
#include "RawFrequencyStorage.h"


namespace structure
{
	namespace storage
	{


RawFrequencyStorage::RawFrequencyStorage(
	double pGlobalFrequency,
	size_t pSourceCount)
:
	mGlobalFrequency(pGlobalFrequency),
	mLocalFrequencies(pSourceCount, 0)
{

}


RawFrequencyStorage::RawFrequencyStorage(
	double 				pGlobalFrequency,
	FrequencyVector 	pSourceFrequencies)
:
	mGlobalFrequency(pGlobalFrequency),
	mLocalFrequencies(pSourceFrequencies)
{

}


void RawFrequencyStorage::addNewLocalFrequency(size_t pSource, size_t pFrequency)
{
	if (pSource >= getSourceCount())
	{
		mLocalFrequencies.resize(pSource + 1);
	}
	mLocalFrequencies[pSource] = pFrequency;
}


void RawFrequencyStorage::addFrequencies(RawFrequencyStorage const& pStorage)
{
	if (pStorage.getSourceCount() > getSourceCount())
	{
		mLocalFrequencies.resize(pStorage.getSourceCount());
	}

	for (size_t i = 0; i < pStorage.mLocalFrequencies.size(); ++i)
	{
		mLocalFrequencies[i] += pStorage.mLocalFrequencies[i];
	}

	mGlobalFrequency += pStorage.mGlobalFrequency;
}


void RawFrequencyStorage::subtractFrequencies(RawFrequencyStorage const& pStorage)
{
	for (size_t i = 0; i < pStorage.mLocalFrequencies.size(); ++i)
	{
		mLocalFrequencies[i] -= pStorage.mLocalFrequencies[i];
	}

	mGlobalFrequency -= pStorage.mGlobalFrequency;
}


double RawFrequencyStorage::getGlobalFrequency() const
{
	return mGlobalFrequency;
}


size_t RawFrequencyStorage::getSourceCount() const
{
	return mLocalFrequencies.size();
}


size_t RawFrequencyStorage::getLocalFrequency(size_t pSource) const
{
	return mLocalFrequencies[pSource];
}


void RawFrequencyStorage::setGlobalFrequency(double pFrequency)
{
	mGlobalFrequency = pFrequency;
}


void RawFrequencyStorage::setLocalFrequency(size_t pSource, size_t pFrequency)
{
	mLocalFrequencies[pSource] = pFrequency;
}


void RawFrequencyStorage::modifyGlobalFrequency(double pDelta)
{
	mGlobalFrequency += pDelta;
}


void RawFrequencyStorage::modifyLocalFrequency(size_t pSource, size_t pDelta)
{
	mLocalFrequencies[pSource] += pDelta;
}


void RawFrequencyStorage::modifyFrequency(size_t pSource, size_t pDelta)
{
	modifyLocalFrequency(pSource, pDelta);
	mGlobalFrequency += pDelta;
}


double RawFrequencyStorage::sumLocalFrequencies() const
{
	return utils::sum<double>(mLocalFrequencies.begin(), mLocalFrequencies.end());
}


void RawFrequencyStorage::computeGlobalFrequency()
{
	mGlobalFrequency = sumLocalFrequencies();
}


size_t RawFrequencyStorage::countNonZeroSources() const
{
	size_t c = 0;
	for (size_t i = 0; i < mLocalFrequencies.size(); ++i)
	{
		if (mLocalFrequencies[i] != 0)
		{
			++c;
		}
	}
	return c;
}


std::ostream& RawFrequencyStorage::writeFrequenciesReprezentation(std::ostream& pStream) const
{
	for (size_t i = 0; i < mLocalFrequencies.size(); ++i)
	{
		pStream << mLocalFrequencies[i];
		if (i < mLocalFrequencies.size() - 1)
		{
			pStream << '\t';
		}
	}
	return pStream;
}


std::string RawFrequencyStorage::createFrequenciesReprezentation() const
{
	std::stringstream str;
	writeFrequenciesReprezentation(str);
	return str.str();
}


auto RawFrequencyStorage::begin() const -> ValueIteratorConst
{
	return mLocalFrequencies.begin();
}


auto RawFrequencyStorage::begin() -> ValueIterator
{
	return mLocalFrequencies.begin();
}


auto RawFrequencyStorage::end() const -> ValueIteratorConst
{
	return mLocalFrequencies.end();
}


auto RawFrequencyStorage::end() -> ValueIterator
{
	return mLocalFrequencies.end();
}


	}
}
