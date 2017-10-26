
#pragma once

#include <unordered_set>
#include <memory>

#include "../storage/RelevantTupleIdSet.h"
#include "../storage/RelevantTuple.h"


namespace structure
{
	namespace io
	{


class RelevantTupleSetLoader
{
public:
	typedef storage::MatrixTupleStorage				TupleStorage;
	typedef TupleStorage::TupleId					TupleId;
	typedef TupleStorage::TupleIdSet				TupleIdSet;
	typedef storage::RelevantTuple					RelevantTuple;
	typedef std::unordered_multiset<RelevantTuple>	RelevantTupleSet;
	typedef storage::RelevantTupleIdSet				RelevantTupleIdSet;
	typedef std::shared_ptr<RelevantTupleIdSet>		RelevantTupleIdSetPtrS;

	struct PositiveNegativePair
	{
		RelevantTupleIdSetPtrS positive;
		RelevantTupleIdSetPtrS negative;
	};


	enum class ElementOrder
	{
		FLEXIBLE = 0,
		FIXED
	};

public:
	RelevantTupleSetLoader() 												= default;
	RelevantTupleSetLoader(RelevantTupleSetLoader&& 				pSet)	= default;
	RelevantTupleSetLoader(RelevantTupleSetLoader const& 			pSet)	= delete;
	RelevantTupleSetLoader& operator=(RelevantTupleSetLoader const& pSet)	= delete;

	~RelevantTupleSetLoader() = default;

	RelevantTupleIdSetPtrS loadFromFile(
		std::string const& 		pFile,
		TupleStorage const&		pTupleStorage,
		ElementOrder			pElementOrder,
		TupleIdSet const&		pInterestedTupleIdSet = TupleIdSet()) const;

	PositiveNegativePair loadPairFromFile(
		std::string const& 		pFile,
		TupleStorage const&		pTupleStorage,
		ElementOrder			pElementOrder,
		TupleIdSet const&		pInterestedTupleIdSet = TupleIdSet()) const;

	RelevantTuple parseLine(std::string pLine) const;

	RelevantTupleSet readTuples(std::string const& pFile) const;

	bool isRelevant(
		TupleId const&			pTupleId,
		TupleStorage const&		pTupleStorage,
		RelevantTupleSet const&	pRelevantTupleSet,
		ElementOrder			pElementOrder) const;

	RelevantTupleIdSetPtrS buildSet(
		TupleStorage const& 	pTupleStorage,
		RelevantTupleSet const&	pRelevantTupleSet,
		ElementOrder			pElementOrder,
		TupleIdSet const&		pInterestedTupleIdSet = TupleIdSet()) const;

	PositiveNegativePair buildPair(
		TupleStorage const& 	pTupleStorage,
		RelevantTupleSet const&	pRelevantTupleSet,
		ElementOrder			pElementOrder,
		TupleIdSet const&		pInterestedTupleIdSet = TupleIdSet()) const;
};


	}
}
