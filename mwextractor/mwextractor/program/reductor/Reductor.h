
#pragma once

#include "Config.h"

#include "../../structure/io/RelevantTupleSetLoader.h"
#include "../../structure/storage/MatrixTupleStorage.h"
#include "../../structure/container/Array2D.h"


namespace program
{
	namespace reductor
	{


class Reductor
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
	typedef RelevantLoader::PositiveNegativePair		PositiveNegativePair;

	typedef structure::container::Array2D<size_t>		CoverMatrix;
	typedef std::map<RelationId, size_t>				RelevantStats;

public:
	void reduce(Config const& pConfig);

private:
	void reduce();

private:
	Config mConfig;

	/* Data */
	TupleStoragePtrS 		mTupleStorage;
	PositiveNegativePair	mPositiveNegative;
};


	}
}
