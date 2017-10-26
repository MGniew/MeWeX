
#pragma once

#include <memory>

#include "MatrixTupleStorage.h"
#include "ContingencyTable.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Klasa bazowa dla klas składujących/generujących tablice wielodzielne.
 *
 * Klasa jest klasą bazową dla klas, których obiekty składują tablice wielodzielne (ContingencyTableStorage)
 * lub są ich generatorami (ContingencyTableGenerator).
 * Jest to także interfejs pozwalający na abstrahowanie od faktycznego sposobu generowania/składowania krotek.
 *
 * @see ContingencyTable
 * @see ContingencyTableGenerator
 * @see ContingencyTableStorage
 */
class ContingencyTableSource
{
public:
	typedef std::shared_ptr<MatrixTupleStorage>	MatrixTupleStoragePtrS;
	typedef MatrixTupleStorage::TupleT			TupleT;
	typedef MatrixTupleStorage::TupleId			TupleId;

public:
	ContingencyTableSource() 																	= default;
	ContingencyTableSource(ContingencyTableSource&& 				pContingencyTableSource) 	= default;
	ContingencyTableSource(ContingencyTableSource const& 			pContingencyTableSource) 	= delete;
	ContingencyTableSource& operator=(ContingencyTableSource&&	 	pContingencyTableSource) 	= default;
	ContingencyTableSource& operator=(ContingencyTableSource const& pContingencyTableSource) 	= delete;

	virtual ~ContingencyTableSource() = default;


	virtual ContingencyTable constructTable(
		TupleId 						pTupleId,
		MatrixTupleStoragePtrS const&	pTupleStorage) const = 0;

	virtual ContingencyTable constructTable(
		TupleT const&					pTupleT,
		MatrixTupleStoragePtrS const&	pTupleStorage) const = 0;
};


	}
}
