
#pragma once

#include <mutex>
#include <unordered_set>

#include "../storage/MatrixTupleStorage.h"
#include "../storage/ContingencyTableGenerator.h"
#include "../storage/ContingencyTableStorage.h"


namespace structure
{
	namespace builder
	{


/**
 * \brief Budowczniy składowska krotek.
 *
 * Obiekt klasy ma za zadanie zbudowanie składu krotek na podstawie
 * składowiska krotek, identyfikatorów krotek, dla których
 * krotki mają zostać zbudowane, a także konkretnego generatora
 * tablic wielodzielnych.
 *
 * @see ContingencyTableStorage
 */
class ContingencyTableStorageBuilder
{
public:
	typedef storage::MatrixTupleStorage 				TupleStorage;
	typedef std::shared_ptr<TupleStorage const>			TupleStorageConstPtrS;
	typedef TupleStorage::TupleIdVector					TupleIdVector;

	typedef storage::ContingencyTableGenerator			ContingencyTableGenerator;
	typedef std::shared_ptr<ContingencyTableGenerator> 	ContingencyTableGeneratorPtrS;
	typedef storage::ContingencyTableStorage			ContingencyTableStorage;
	typedef std::shared_ptr<ContingencyTableStorage>	ContingencyTableStoragePtrS;

public:
	ContingencyTableStorageBuilder()																= default;
	ContingencyTableStorageBuilder(ContingencyTableStorageBuilder&& 					pCreator) 	= default;
	ContingencyTableStorageBuilder(ContingencyTableStorageBuilder const& 				pCreator) 	= delete;
	ContingencyTableStorageBuilder& operator=(ContingencyTableStorageBuilder&&		 	pCreator) 	= default;
	ContingencyTableStorageBuilder& operator=(ContingencyTableStorageBuilder const& 	pCreator) 	= delete;

	virtual ~ContingencyTableStorageBuilder() = default;


	ContingencyTableStoragePtrS build(
		TupleStorageConstPtrS const& 			pStorage,
		ContingencyTableGeneratorPtrS const&	pContingencyTableGenerator,
		TupleIdVector const&					pTupleIdVector);
};


	}
}
