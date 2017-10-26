
#pragma once

#include "AbstractTupleFeatureStorageIO.h"


namespace structure
{
	namespace io
	{


class ArffTupleFeatureStorageIO : public AbstractTupleFeatureStorageIO
{
public:
	virtual void writeToFile(
		std::string const& 				pFilePath,
		TupleFeatureStoragePtrS const& 	pDataSet,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;

	virtual TupleFeatureStoragePtrS readFromFile(
		std::string const& 				pFilePath,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;
};


	}
}
