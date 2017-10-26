
#pragma once

#include <memory>
#include <unordered_set>

#include "../RelevantObjectSet.h"
#include "../storage/MatrixTupleStorage.h"


namespace structure
{
	namespace io
	{


/*
 * DEPRECATED, unused
 *
 * word1 word2 word3 ...
 * ...
 */
class WordnetRelevantChainWordSetLoader
{
public:
	typedef storage::MatrixTupleStorage		TupleStorage;
	typedef TupleStorage::TupleId			TupleId;
	typedef TupleStorage::TupleIdSet		TupleIdSet;
	typedef RelevantObjectSet<TupleId>		RelevantTupleIdSet;

public:
	WordnetRelevantChainWordSetLoader() 															= default;
	WordnetRelevantChainWordSetLoader(WordnetRelevantChainWordSetLoader&& 					pSet)	= default;
	WordnetRelevantChainWordSetLoader(WordnetRelevantChainWordSetLoader const& 				pSet)	= delete;
	WordnetRelevantChainWordSetLoader& operator=(WordnetRelevantChainWordSetLoader const& 	pSet)	= delete;

	~WordnetRelevantChainWordSetLoader() = default;

	RelevantTupleIdSet loadFromFile(
		std::string const& 		pFile,
		TupleStorage const&		pTupleStorage,
		TupleIdSet const&		pTupleIdSet = TupleIdSet()) const;

private:
	std::set<std::string> readLines(std::string const& pFile) const;

	RelevantTupleIdSet buildSet(
		std::set<std::string> const& 	pLines,
		TupleStorage const& 			pTupleStorage,
		TupleIdSet const&				pTupleIdSet) const;
};


	}
}
