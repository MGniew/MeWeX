
#pragma once

#include <memory>

#include "MatrixTupleStorage.h"

#include "Instance.h"


namespace structure
{
	namespace storage
	{


class TupleFeatureSource
{
public:
	typedef std::shared_ptr<MatrixTupleStorage>	MatrixTupleStoragePtrS;
	typedef MatrixTupleStorage::TupleId			TupleId;
	typedef MatrixTupleStorage::TupleT			TupleT;

public:
	TupleFeatureSource() 															= default;
	TupleFeatureSource(TupleFeatureSource&& 				pTupleFeatureSource) 	= default;
	TupleFeatureSource(TupleFeatureSource const& 			pTupleFeatureSource) 	= delete;
	TupleFeatureSource& operator=(TupleFeatureSource&&	 	pTupleFeatureSource) 	= default;
	TupleFeatureSource& operator=(TupleFeatureSource const& pTupleFeatureSource)	= delete;

	virtual ~TupleFeatureSource() = default;


	virtual size_t getFeatureCount() const = 0;


	virtual Instance constructInstance(
		TupleId 						pTupleId,
		MatrixTupleStoragePtrS const&	pTupleStorage) const = 0;

	virtual Instance constructInstance(
		TupleT const& 					pTupleT,
		MatrixTupleStoragePtrS const&	pTupleStorage) const = 0;
};


	}
}
