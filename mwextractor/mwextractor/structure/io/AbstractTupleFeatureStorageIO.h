
#pragma once

#include <memory>

#include "../storage/MatrixTupleStorage.h"
#include "../storage/TupleFeatureStorage.h"


namespace structure
{
	namespace io
	{


class AbstractTupleFeatureStorageIO
{
public:
	typedef std::shared_ptr<storage::TupleFeatureStorage>	TupleFeatureStoragePtrS;
	typedef std::shared_ptr<storage::MatrixTupleStorage>	MatrixTupleStoragePtrS;

public:
	AbstractTupleFeatureStorageIO() 														= default;
	AbstractTupleFeatureStorageIO(AbstractTupleFeatureStorageIO&& 					pIO) 	= default;
	AbstractTupleFeatureStorageIO(AbstractTupleFeatureStorageIO const& 				pIO) 	= default;
	AbstractTupleFeatureStorageIO& operator=(AbstractTupleFeatureStorageIO&& 		pIO) 	= default;
	AbstractTupleFeatureStorageIO& operator=(AbstractTupleFeatureStorageIO const& 	pIO) 	= default;

	virtual ~AbstractTupleFeatureStorageIO() = default;


	virtual void writeToFile(
		std::string const& 				pFilePath,
		TupleFeatureStoragePtrS const&	pTupleStorage,
		MatrixTupleStoragePtrS const& 	pDataSet) const = 0;

	virtual TupleFeatureStoragePtrS readFromFile(
		std::string const& 				pFilePath,
		MatrixTupleStoragePtrS const&	pTupleStorage) const = 0;
};


	}
}
