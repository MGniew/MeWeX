
#pragma once

#include <memory>

#include "../storage/ContingencyTableGenerator.h"


namespace structure
{
	namespace io
	{


class AbstractContingencyTableGeneratorIO
{
public:
	typedef storage::MatrixTupleStorage 				TupleStorage;
	typedef storage::ContingencyTableGenerator			ContingencyTableGenerator;
	typedef std::shared_ptr<ContingencyTableGenerator>	ContingencyTableGeneratorPtrS;

public:
	AbstractContingencyTableGeneratorIO() 																= default;
	AbstractContingencyTableGeneratorIO(AbstractContingencyTableGeneratorIO&& 					pIO) 	= default;
	AbstractContingencyTableGeneratorIO(AbstractContingencyTableGeneratorIO const&	 			pIO) 	= default;
	AbstractContingencyTableGeneratorIO& operator=(AbstractContingencyTableGeneratorIO&&		pIO) 	= default;
	AbstractContingencyTableGeneratorIO& operator=(AbstractContingencyTableGeneratorIO const& 	pIO) 	= default;

	virtual ~AbstractContingencyTableGeneratorIO() = default;


	virtual void write(
		ContingencyTableGenerator const&	pContingencyTableGenerator,
		TupleStorage const& 				pStorage,
		std::string const&					pFile) const = 0;

	virtual ContingencyTableGeneratorPtrS read(
		TupleStorage const&	pStorage,
		std::string const&	pFile) const = 0;
};


	}
}
