
#include <limits>
#include <cmath>

#include "../../utils/Debug.h"

#include "TupleFeatureStorage.h"


namespace structure
{
	namespace storage
	{


TupleFeatureStorage::TupleFeatureStorage()
:
	mClassCount(0)
{

}


TupleFeatureStorage::TupleFeatureStorage(
	InstanceMap&& 	pInstanceMap,
	size_t			pClassCount)
:
	mInstanceMap(std::forward<InstanceMap>(pInstanceMap)),
	mClassCount(pClassCount)
{

}


TupleFeatureStorage::TupleFeatureStorage(
	InstanceMap const& 	pInstanceMap,
	size_t				pClassCount)
:
	mInstanceMap(pInstanceMap),
	mClassCount(pClassCount)
{

}


TupleFeatureStorage::TupleFeatureStorage(
	size_t 						pClassCount,
	FeatureNameVector const&	pFeatureNameVector,
	std::string const&			pRelationName,
	std::string const&			pReprezentationName,
	std::string const&			pClassName,
	HeaderNoteVector const&		pHeaderNotes)
:
	mClassCount(pClassCount),
	mFeatureNameVector(pFeatureNameVector),
	mRelationName(pRelationName),
	mReprezentationName(pReprezentationName),
	mClassName(pClassName),
	mHeaderNotes(pHeaderNotes)
{

}


TupleFeatureStorage TupleFeatureStorage::copyMetadata() const
{
	return TupleFeatureStorage(
		getClassCount(),
		getFeatureNameVector(),
		getRelationName(),
		getReprezentationName(),
		getClassName(),
		getHeaderNoteVector());
}


TupleFeatureStorage TupleFeatureStorage::buildSubset(InstanceMap&& pInstanceMap) const
{
	TupleFeatureStorage dataSubset = copyMetadata();
	dataSubset.getInstanceMap() = std::forward<InstanceMap>(pInstanceMap);
	return dataSubset;
}


TupleFeatureStorage TupleFeatureStorage::buildSubset(InstanceMap const& pInstanceMap) const
{
	TupleFeatureStorage dataSubset = copyMetadata();
	dataSubset.getInstanceMap() = pInstanceMap;
	return dataSubset;
}


auto TupleFeatureStorage::getInstanceMap() const -> InstanceMap const&
{
	return mInstanceMap;
}


auto TupleFeatureStorage::getInstanceMap() -> InstanceMap&
{
	return mInstanceMap;
}


auto TupleFeatureStorage::getFeatureNameVector() const -> FeatureNameVector const&
{
	return mFeatureNameVector;
}


auto TupleFeatureStorage::getFeatureNameVector() -> FeatureNameVector&
{
	return mFeatureNameVector;
}


auto TupleFeatureStorage::getHeaderNoteVector() const -> HeaderNoteVector const&
{
	return mHeaderNotes;
}


auto TupleFeatureStorage::getHeaderNoteVector() -> HeaderNoteVector&
{
	return mHeaderNotes;
}


std::string const& TupleFeatureStorage::getClassName() const
{
	return mClassName;
}


std::string& TupleFeatureStorage::getClassName()
{
	return mClassName;
}


std::string const& TupleFeatureStorage::getReprezentationName() const
{
	return mReprezentationName;
}


std::string& TupleFeatureStorage::getReprezentationName()
{
	return mReprezentationName;
}


std::string const& TupleFeatureStorage::getRelationName() const
{
	return mRelationName;
}


std::string& TupleFeatureStorage::getRelationName()
{
	return mRelationName;
}


size_t TupleFeatureStorage::getInstanceCount() const
{
	return mInstanceMap.size();
}


size_t TupleFeatureStorage::getFeatureCount() const
{
	return mFeatureNameVector.size();
}


size_t TupleFeatureStorage::getClassCount() const
{
	return mClassCount;
}


void TupleFeatureStorage::setClassCount(size_t pClassCount)
{
	mClassCount = pClassCount;
}


void TupleFeatureStorage::setClassName(std::string const& pClassName)
{
	mClassName = pClassName;
}


void TupleFeatureStorage::setReprezentationName(std::string const& pReprezentationName)
{
	mReprezentationName = pReprezentationName;
}


void TupleFeatureStorage::setRelationName(std::string const& pRelationName)
{
	mRelationName = pRelationName;
}


double TupleFeatureStorage::findFeatureMin(size_t pFeatureIndex) const
{
	XASSERT(pFeatureIndex < getFeatureCount(), "TupleFeatureStorage::findFeatureMin(): No such feature " << pFeatureIndex << '.');

	double min = std::numeric_limits<double>::max();
	for (auto iter = mInstanceMap.begin(); iter != mInstanceMap.end(); ++iter)
	{
		FeatureVector const& features = iter->second.getFeatureVector();
		if (features[pFeatureIndex] < min)
		{
			min = features[pFeatureIndex];
		}
	}
	return min;
}


double TupleFeatureStorage::findFeatureMax(size_t pFeatureIndex) const
{
	XASSERT(pFeatureIndex < getFeatureCount(), "TupleFeatureStorage::findFeatureMin(): No such feature " << pFeatureIndex << '.');

	double max = -std::numeric_limits<double>::max();
	for (auto iter = mInstanceMap.begin(); iter != mInstanceMap.end(); ++iter)
	{
		FeatureVector const& features = iter->second.getFeatureVector();
		if (features[pFeatureIndex] > max)
		{
			max = features[pFeatureIndex];
		}
	}
	return max;
}


double TupleFeatureStorage::computeFeatureMean(size_t pFeatureIndex) const
{
	XASSERT(pFeatureIndex < getFeatureCount(), "TupleFeatureStorage::findFeatureMin(): No such feature " << pFeatureIndex << '.');

	double mean = 0;
	for (auto iter = mInstanceMap.begin(); iter != mInstanceMap.end(); ++iter)
	{
		FeatureVector const& features = iter->second.getFeatureVector();
		mean += features[pFeatureIndex];
	}
	return mean / static_cast<double>(getInstanceCount());
}


double TupleFeatureStorage::computeFeatureVariance(size_t pFeatureIndex, double pMean) const
{
	XASSERT(pFeatureIndex < getFeatureCount(), "TupleFeatureStorage::findFeatureMin(): No such feature " << pFeatureIndex << '.');

	double var = 0;
	for (auto iter = mInstanceMap.begin(); iter != mInstanceMap.end(); ++iter)
	{
		FeatureVector const& features = iter->second.getFeatureVector();
		var += (features[pFeatureIndex] - pMean) * (features[pFeatureIndex] - pMean);
	}
	return var / static_cast<double>(getInstanceCount());
}


double TupleFeatureStorage::computeFeatureVariance(size_t pFeatureIndex) const
{
	return computeFeatureVariance(pFeatureIndex, computeFeatureMean(pFeatureIndex));
}


double TupleFeatureStorage::computeFeatureStandardDeviation(size_t pFeatureIndex, double pMean) const
{
	return std::sqrt(computeFeatureVariance(pFeatureIndex, pMean));
}


double TupleFeatureStorage::computeFeatureStandardDeviation(size_t pFeatureIndex) const
{
	return computeFeatureStandardDeviation(pFeatureIndex, computeFeatureMean(pFeatureIndex));
}


auto TupleFeatureStorage::computeMinMeanMax(size_t pFeatureIndex) const -> MinMeanMax
{
	XASSERT(pFeatureIndex < getFeatureCount(), "TupleFeatureStorage::findFeatureMin(): No such feature " << pFeatureIndex << '.');

	MinMeanMax stats = {0};
	stats.min = std::numeric_limits<double>::max();
	stats.max = -std::numeric_limits<double>::max();

	for (auto iter = mInstanceMap.begin(); iter != mInstanceMap.end(); ++iter)
	{
		FeatureVector const& features = iter->second.getFeatureVector();
		if (features[pFeatureIndex] > stats.max)
		{
			stats.max = features[pFeatureIndex];
		}
		if (features[pFeatureIndex] < stats.min)
		{
			stats.min = features[pFeatureIndex];
		}
		stats.mean += features[pFeatureIndex];
	}

	stats.mean /= static_cast<double>(getInstanceCount());

	return stats;
}


auto TupleFeatureStorage::computeMinMeanMax() const -> MinMeanMaxVector
{
	MinMeanMax temp;
	temp.min = std::numeric_limits<double>::max();
	temp.mean = 0.0;
	temp.max = -std::numeric_limits<double>::max();

	MinMeanMaxVector stats(getFeatureCount(), temp);

	for (auto iter = mInstanceMap.begin(); iter != mInstanceMap.end(); ++iter)
	{
		FeatureVector const& features = iter->second.getFeatureVector();
		for (size_t f = 0; f < getFeatureCount(); ++f)
		{
			if (features[f] > stats[f].max)
			{
				stats[f].max = features[f];
			}
			if (features[f] < stats[f].min)
			{
				stats[f].min = features[f];
			}
			stats[f].mean += features[f];
		}
	}

	for (size_t f = 0; f < getFeatureCount(); ++f)
	{
		stats[f].mean /= static_cast<double>(getInstanceCount());
	}

	return stats;
}


Instance TupleFeatureStorage::constructInstance(
	TupleId 						pTupleId,
	MatrixTupleStoragePtrS const&	pTupleStorage) const
{
	auto iter = getInstanceMap().find(pTupleId);
	XASSERT(iter != getInstanceMap().end(), "TupleFeatureStorage::constructInstance(): Instance for TupleId not found.");
	return iter->second;
}


Instance TupleFeatureStorage::constructInstance(
	TupleT const& 					pTupleT,
	MatrixTupleStoragePtrS const&	pTupleStorage) const
{
	TupleId tid = pTupleStorage->findTupleIdSilent(pTupleT);
	XASSERT(tid != nullptr, "TupleFeatureStorage::constructInstance(): Tuple not found.");
	return constructInstance(tid, pTupleStorage);
}


	}
}
