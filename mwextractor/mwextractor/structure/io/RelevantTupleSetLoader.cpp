
#include <sstream>

#include "../../utils/Textual.h"
#include "StreamingFileReader.h"
#include "RelevantTupleSetLoader.h"


namespace structure
{
	namespace io
	{


auto RelevantTupleSetLoader::loadFromFile(
	std::string const& 		pFile,
	TupleStorage const&		pTupleStorage,
	ElementOrder			pElementOrder,
	TupleIdSet const&		pInterestedTupleIdSet) const -> RelevantTupleIdSetPtrS
{
	return buildSet(pTupleStorage, readTuples(pFile), pElementOrder, pInterestedTupleIdSet);
}


auto RelevantTupleSetLoader::loadPairFromFile(
	std::string const& 		pFile,
	TupleStorage const&		pTupleStorage,
	ElementOrder			pElementOrder,
	TupleIdSet const&		pInterestedTupleIdSet) const -> PositiveNegativePair
{
	return buildPair(pTupleStorage, readTuples(pFile), pElementOrder, pInterestedTupleIdSet);
}


auto RelevantTupleSetLoader::parseLine(std::string pLine) const -> RelevantTuple
{
	std::vector<std::string> parts;
	utils::trim(pLine);
	utils::split(pLine, parts, ' ');
	return RelevantTuple(std::forward<std::vector<std::string>>(parts));
}


auto RelevantTupleSetLoader::readTuples(std::string const& pFile) const -> RelevantTupleSet
{
	RelevantTupleSet relevantTupleSet;

	StreamingFileReader reader(pFile);
	std::string line;
	while (reader.readline(line))
	{
		relevantTupleSet.insert(parseLine(line));
	}

	return relevantTupleSet;
}


bool RelevantTupleSetLoader::isRelevant(
	TupleId const&			pTupleId,
	TupleStorage const&		pTupleStorage,
	RelevantTupleSet const&	pRelevantTupleSet,
	ElementOrder			pElementOrder) const
{
	RelevantTuple relevantTuple(pTupleStorage, pTupleStorage.findTuple(pTupleId));

	/* check flexible */
	bool isRelevant = (pRelevantTupleSet.find(relevantTuple) != pRelevantTupleSet.end());

	/* check fixed */
	if (isRelevant && (pElementOrder == ElementOrder::FIXED))
	{
		isRelevant = false;
		auto rangeIter = pRelevantTupleSet.equal_range(relevantTuple);
		while (!isRelevant && rangeIter.first != rangeIter.second)
		{
			isRelevant = relevantTuple.equalFixed(*(rangeIter.first));
			++rangeIter.first;
		}
	}

	return isRelevant;
}


auto RelevantTupleSetLoader::buildSet(
	TupleStorage const& 	pTupleStorage,
	RelevantTupleSet const&	pRelevantTupleSet,
	ElementOrder			pElementOrder,
	TupleIdSet const&		pInterestedTupleIdSet) const -> RelevantTupleIdSetPtrS
{
	RelevantTupleIdSetPtrS set(new RelevantTupleIdSet(pRelevantTupleSet.size()));

	for (auto iter = pTupleStorage.beginTuples(); iter != pTupleStorage.endTuples(); ++iter)
	{
		TupleId tid = pTupleStorage.findTupleId(iter);
		if ((pInterestedTupleIdSet.empty() || (pInterestedTupleIdSet.find(tid) != pInterestedTupleIdSet.end())) &&
			isRelevant(tid, pTupleStorage, pRelevantTupleSet, pElementOrder))
		{
			set->insert(tid);
		}
	}

	return set;
}


auto RelevantTupleSetLoader::buildPair(
	TupleStorage const& 	pTupleStorage,
	RelevantTupleSet const&	pRelevantTupleSet,
	ElementOrder			pElementOrder,
	TupleIdSet const&		pInterestedTupleIdSet) const -> PositiveNegativePair
{
	PositiveNegativePair pair;
	pair.positive.reset(new RelevantTupleIdSet(pRelevantTupleSet.size()));
	pair.negative.reset(new RelevantTupleIdSet(pRelevantTupleSet.size()));

	for (auto iter = pTupleStorage.beginTuples(); iter != pTupleStorage.endTuples(); ++iter)
	{
		TupleId tid = pTupleStorage.findTupleId(iter);
		if ((pInterestedTupleIdSet.empty() || (pInterestedTupleIdSet.find(tid) != pInterestedTupleIdSet.end())) &&
			isRelevant(tid, pTupleStorage, pRelevantTupleSet, pElementOrder))
		{
			pair.positive->insert(tid);
		}
		else
		{
			pair.negative->insert(tid);
		}
	}

	return pair;
}


	}
}
