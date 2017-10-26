
#pragma once

#include "Config.h"

#include "../../structure/io/RelevantTupleSetLoader.h"
#include "../../structure/storage/MatrixTupleStorage.h"
#include "../../structure/container/Array2D.h"


namespace program
{
	namespace cover
	{


/*
 * TODO: Conception - save results as NxN matrix where N is relation count
 */
class Cover
{
private:
	typedef structure::storage::MatrixTupleStorage		TupleStorage;
	typedef std::shared_ptr<TupleStorage>				TupleStoragePtrS;
	typedef TupleStorage::RelationId					RelationId;
	typedef TupleStorage::TupleId						TupleId;
	typedef TupleStorage::TupleIdVector					TupleIdVector;
	typedef TupleStorage::TupleIdSet					TupleIdSet;

	typedef structure::io::RelevantTupleSetLoader		RelevantLoader;
	typedef RelevantLoader::RelevantTupleIdSetPtrS		RelevantTupleIdSetPtrS;

	typedef structure::container::Array2D<size_t>		CoverMatrix;
	typedef std::map<RelationId, size_t>				RelevantStats;

public:
	void check(Config const& pConfig);

private:
	void 			loadData();
	void 			check();

	void 			writeRelevantSet() 		const;
	CoverMatrix		computeCoverMatrix()	const;
	RelevantStats	computeRelevantStats()	const;

	void 			writeStatistics(
						CoverMatrix const& 		pCoverMatrix,
						RelevantStats const&	pRelevantStats)	const;

private:
	Config mConfig;

	/* Data */
	TupleStoragePtrS 		mTupleStorage;
	TupleIdSet				mInterestedTupleIdSet;
	RelevantTupleIdSetPtrS 	mRelevantTupleIdSet;
};


	}
}
