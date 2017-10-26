/*
 * CompressedFrequencyStorage.cpp
 *
 *  Created on: 08-07-2014
 *      Author: michalw
 */

#include <sstream>

#include "../../utils/Math.h"
#include "CompressedFrequencyStorage.h"


namespace structure
{
	namespace storage
	{


CompressedFrequencyStorage::CompressedFrequencyStorage(
	double pGlobalFrequency,
	size_t pSourceCount)
:
	mGlobalFrequency(pGlobalFrequency),
	mLocalFrequencies(pSourceCount)
{

}


CompressedFrequencyStorage::CompressedFrequencyStorage(
	double 				pGlobalFrequency,
	FrequencyVector 	pSourceFrequencies)
:
	mGlobalFrequency(pGlobalFrequency),
	mLocalFrequencies(pSourceFrequencies.size())
{
	for (size_t i = 0; i < pSourceFrequencies.size(); ++i)
	{
		setLocalFrequency(i, pSourceFrequencies[i]);
	}
}


void CompressedFrequencyStorage::addNewLocalFrequency(size_t pSource, size_t pFrequency)
{
	if (pSource >= getSourceCount())
	{
		mLocalFrequencies.resize(pSource + 1);
	}

	mLocalFrequencies.set(pSource, pFrequency);
}


void CompressedFrequencyStorage::addFrequencies(CompressedFrequencyStorage const& pStorage)
{
	if (pStorage.getSourceCount() > getSourceCount())
	{
		mLocalFrequencies.resize(pStorage.getSourceCount());
	}

	for (auto i = pStorage.mLocalFrequencies.begin(); i != pStorage.mLocalFrequencies.end(); ++i)
	{
		mLocalFrequencies.add(i->first, i->second);
	}

	mGlobalFrequency += pStorage.mGlobalFrequency;
}


void CompressedFrequencyStorage::subtractFrequencies(CompressedFrequencyStorage const& pStorage)
{
	for (auto i = pStorage.mLocalFrequencies.begin(); i != pStorage.mLocalFrequencies.end(); ++i)
	{
		mLocalFrequencies.add(i->first, -i->second);
	}

	mGlobalFrequency -= pStorage.mGlobalFrequency;
}


double CompressedFrequencyStorage::getGlobalFrequency() const
{
	return mGlobalFrequency;
}


size_t CompressedFrequencyStorage::getSourceCount() const
{
	return mLocalFrequencies.size();
}


size_t CompressedFrequencyStorage::getLocalFrequency(size_t pSource) const
{
	return mLocalFrequencies.get(pSource);
}


void CompressedFrequencyStorage::setGlobalFrequency(double pFrequency)
{
	mGlobalFrequency = pFrequency;
}


void CompressedFrequencyStorage::setLocalFrequency(size_t pSource, size_t pFrequency)
{
	mLocalFrequencies.set(pSource, pFrequency);
}


void CompressedFrequencyStorage::modifyGlobalFrequency(double pDelta)
{
	mGlobalFrequency += pDelta;
}


void CompressedFrequencyStorage::modifyLocalFrequency(size_t pSource, size_t pDelta)
{
	mLocalFrequencies.add(pSource, pDelta);
}


void CompressedFrequencyStorage::modifyFrequency(size_t pSource, size_t pDelta)
{
	modifyLocalFrequency(pSource, pDelta);
	mGlobalFrequency += pDelta;
}


double CompressedFrequencyStorage::sumLocalFrequencies() const
{
	return utils::sum<double>(mLocalFrequencies.beginValues(), mLocalFrequencies.endValues());
}


void CompressedFrequencyStorage::computeGlobalFrequency()
{
	mGlobalFrequency = sumLocalFrequencies();
}


size_t CompressedFrequencyStorage::countNonZeroSources() const
{
	return mLocalFrequencies.sizeNonDefault();
}


std::ostream& CompressedFrequencyStorage::writeFrequenciesReprezentation(std::ostream& pStream) const
{
	for (size_t i = 0; i < mLocalFrequencies.size(); ++i)
	{
		pStream << mLocalFrequencies.get(i);
		if (i < mLocalFrequencies.size() - 1)
		{
			pStream << '\t';
		}
	}
	return pStream;
}


std::string CompressedFrequencyStorage::createFrequenciesReprezentation() const
{
	std::stringstream str;
	writeFrequenciesReprezentation(str);
	return str.str();
}


auto CompressedFrequencyStorage::begin() const -> ValueIteratorConst
{
	return ValueIteratorConst(mLocalFrequencies.beginValues());
}


auto CompressedFrequencyStorage::begin() -> ValueIterator
{
	return ValueIterator(mLocalFrequencies.beginValues());
}


auto CompressedFrequencyStorage::end() const -> ValueIteratorConst
{
	return ValueIteratorConst(mLocalFrequencies.endValues());
}


auto CompressedFrequencyStorage::end() -> ValueIterator
{
	return ValueIterator(mLocalFrequencies.endValues());
}

	}
}
