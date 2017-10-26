
#pragma once

#include <memory>

#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/storage/MatrixTupleStorage.h"

#include "DataManager.h"


namespace program
{
	namespace metatool
	{


class MatrixTupleStorageManager :
	public DataManager<structure::io::DecodedTupleStorageIO::TupleStoragePtrS>
{
public:
	typedef structure::io::DecodedTupleStorageIO::TupleStoragePtrS TupleStoragePtrS;

public:
	MatrixTupleStorageManager(Id pModuleId, std::string&& 		pName);
	MatrixTupleStorageManager(Id pModuleId, std::string const& 	pName);


	virtual Id loadFromFile(std::string const& pPath) override;

	virtual void writeToFile(std::string const& pPath, Id pId) const override;

	virtual Id copy(Id pId) override;
};


	}
}
