
#pragma once

#include <memory>

#include "../../structure/storage/MatrixTupleStorage.h"

#include "../Function.h"


namespace function
{
	namespace filter
	{


class Filter : public Function
{
public:
	typedef structure::storage::MatrixTupleStorage 	TupleStorage;
	typedef std::shared_ptr<TupleStorage>			TupleStoragePtrS;
	typedef TupleStorage::TupleId					TupleId;

public:
	TupleStoragePtrS const& getMatrixTupleStorage() const;


	virtual bool meets(TupleId pTupleId) const = 0;

	virtual bool operator()(TupleId pTupleId) const;


	virtual void initialize(TupleStoragePtrS const& pStorage);


protected:
	virtual void construct() = 0;


private:
	TupleStoragePtrS mTupleStorage;
};


	}
}
