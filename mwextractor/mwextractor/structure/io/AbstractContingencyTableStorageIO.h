
#pragma once

#include "../storage/ContingencyTableStorage.h"
#include "../builder/ContingencyTableStorageBuilder.h"


namespace structure
{
	namespace io
	{


class AbstractContingencyTableStorageIO
{
public:
	typedef storage::MatrixTupleStorage 											TupleStorage;
	typedef storage::ContingencyTableStorage										ContingencyTableStorage;
	typedef builder::ContingencyTableStorageBuilder::ContingencyTableStoragePtrS	ContingencyTableStoragePtrS;

public:
	AbstractContingencyTableStorageIO() 															= default;
	AbstractContingencyTableStorageIO(AbstractContingencyTableStorageIO&& 					pIO) 	= default;
	AbstractContingencyTableStorageIO(AbstractContingencyTableStorageIO const&	 			pIO) 	= default;
	AbstractContingencyTableStorageIO& operator=(AbstractContingencyTableStorageIO&&		pIO) 	= default;
	AbstractContingencyTableStorageIO& operator=(AbstractContingencyTableStorageIO const& 	pIO) 	= default;

	virtual ~AbstractContingencyTableStorageIO() = default;


	virtual void write(
		ContingencyTableStorage const&	pTable,
		TupleStorage const& 			pStorage,
		std::string const&				pFile) const = 0;

	virtual ContingencyTableStoragePtrS read(
		TupleStorage const&	pStorage,
		std::string const&	pFile) const = 0;
};


	}
}
