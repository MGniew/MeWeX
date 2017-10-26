
#pragma once

#include "AbstractContingencyTableStorageIO.h"


namespace structure
{
	namespace io
	{


class ContingencyTableStorageIO : public AbstractContingencyTableStorageIO
{
public:
	virtual void write(
		ContingencyTableStorage const&	pTable,
		TupleStorage const& 			pStorage,
		std::string const&				pFile) const override;

	virtual ContingencyTableStoragePtrS read(
		TupleStorage const&	pStorage,
		std::string const&	pFile) const override;
};


	}
}
