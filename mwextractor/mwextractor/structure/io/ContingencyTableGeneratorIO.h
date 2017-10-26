
#pragma once

#include "AbstractContingencyTableGeneratorIO.h"


namespace structure
{
	namespace io
	{


class ContingencyTableGeneratorIO : public AbstractContingencyTableGeneratorIO
{
public:
	virtual void write(
		ContingencyTableGenerator const&	pGenerator,
		TupleStorage const& 				pStorage,
		std::string const&					pFile) const override;

	virtual ContingencyTableGeneratorPtrS read(
		TupleStorage const&	pStorage,
		std::string const&	pFile) const override;
};


	}
}
