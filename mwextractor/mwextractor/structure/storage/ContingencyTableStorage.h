
#pragma once

#include "ContingencyTableSource.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Składowisko tablic wielodzielnych.
 *
 * Zadaniem tej klasy jest składowanie gotowych tablic wielodzielnych.
 * Klasa zajmuje się składowaniem tablic wielodzielnych.
 *
 * @see ContingencyTable
 * @see ContingencyTableGenerator
 */
class ContingencyTableStorage : public ContingencyTableSource
{
public:
	typedef std::unordered_map<TupleId, ContingencyTable>	Container;
	typedef Container::iterator								ContainerIterator;
	typedef Container::const_iterator						ContainerIteratorConst;
	typedef std::pair<TupleId, ContingencyTable>			InsertPair;
	typedef std::pair<ContainerIterator, bool>				InsertResult;


public:
	ContingencyTableStorage() 																		= default;
	ContingencyTableStorage(ContingencyTableStorage&& 					pContingencyTableStorage) 	= default;
	ContingencyTableStorage(ContingencyTableStorage const& 				pContingencyTableStorage) 	= delete;
	ContingencyTableStorage& operator=(ContingencyTableStorage&&	 	pContingencyTableStorage) 	= default;
	ContingencyTableStorage& operator=(ContingencyTableStorage const& 	pContingencyTableStorage) 	= delete;

	virtual ~ContingencyTableStorage() = default;


	void 					reserve(size_t pSpace);

	InsertResult			insert(InsertPair&& pInsert);
	InsertResult			insert(InsertPair const& pInsert);

	ContingencyTable 		findTableCopy(TupleId pTupleId) const;
	ContingencyTable const& findTable(TupleId pTupleId) 	const;
	ContingencyTable& 		findTable(TupleId pTupleId);

	virtual ContingencyTable constructTable(
		TupleId 						pTupleId,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;

	virtual ContingencyTable constructTable(
		TupleT const&					pTupleT,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;


	size_t					size() 	const;

	ContainerIteratorConst	begin() const;
	ContainerIterator		begin();
	ContainerIteratorConst	end() 	const;
	ContainerIterator		end();


private:
	Container mContainer;
};


	}
}
