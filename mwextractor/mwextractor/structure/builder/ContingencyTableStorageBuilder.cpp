
#include "ContingencyTableStorageBuilder.h"


namespace structure
{
	namespace builder
	{


auto ContingencyTableStorageBuilder::build(
	TupleStorageConstPtrS const& 			pStorage,
	ContingencyTableGeneratorPtrS const&	pContingencyTableGenerator,
	TupleIdVector const&					pTupleIdVector) -> ContingencyTableStoragePtrS
{
	ContingencyTableStoragePtrS tableStorage(new ContingencyTableStorage());

	for (size_t i = 0; i < pTupleIdVector.size(); ++i)
	{
		TupleStorage::TupleId 		tid 	= pTupleIdVector[i];
		TupleStorage::TupleT const& tuple 	= pStorage->findTuple(tid);

		tableStorage->insert(ContingencyTableStorage::InsertPair(
			tid, pContingencyTableGenerator->createTable(tuple)));
	}

	return tableStorage;
}

	}
}
