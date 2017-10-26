
#pragma once

#include <mutex>
#include <unordered_set>

#include "../storage/MatrixTupleStorage.h"
#include "../storage/ContingencyTableGenerator.h"


namespace structure
{
	namespace builder
	{


/**
 * \brief Budowniczy generatora tablic wielodzielnych.
 *
 * Obiekt tej klasy ma za zadanie zbudowanie generatora
 * tablic wielodzielnych na podstawie zadanego składu krotek.
 * Budowa polega na utworzeniu wewnętrznego indeksu wewnątrz
 * generatora, a następnie zwróceniu instancji tego generatora.
 *
 * @see ContingencyTableGenerator
 * @see MatrixTupleStorage
 */
class ContingencyTableGeneratorBuilder
{
public:
	typedef storage::MatrixTupleStorage 				TupleStorage;
	typedef std::shared_ptr<TupleStorage const>			TupleStorageConstPtrS;

	typedef TupleStorage::WordId						WordId;
	typedef TupleStorage::TupleT						TupleT;

	typedef storage::ContingencyTableGenerator			ContingencyTableGenerator;
	typedef std::shared_ptr<ContingencyTableGenerator>	ContingencyTableGeneratorPtrS;

	typedef TupleStorage::TupleIdVector					TupleIdVector;


public:
	ContingencyTableGeneratorBuilder()																							= default;
	ContingencyTableGeneratorBuilder(ContingencyTableGeneratorBuilder&& 					pContingencyTableGeneratorBuilder) 	= default;
	ContingencyTableGeneratorBuilder(ContingencyTableGeneratorBuilder const& 				pContingencyTableGeneratorBuilder) 	= delete;
	ContingencyTableGeneratorBuilder& operator=(ContingencyTableGeneratorBuilder&&		 	pContingencyTableGeneratorBuilder) 	= default;
	ContingencyTableGeneratorBuilder& operator=(ContingencyTableGeneratorBuilder const& 	pContingencyTableGeneratorBuilder) 	= delete;

	virtual ~ContingencyTableGeneratorBuilder() = default;


	ContingencyTableGeneratorPtrS build(
		TupleStorageConstPtrS const& 	pTupleStorage,
		TupleIdVector const&			pTupleIdVector) const;
};


	}
}
