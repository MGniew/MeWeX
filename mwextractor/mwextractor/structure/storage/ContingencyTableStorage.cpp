
#include "../../utils/Debug.h"

#include "ContingencyTableStorage.h"


namespace structure
{
	namespace storage
	{


void ContingencyTableStorage::reserve(size_t pSpace)
{
	mContainer.reserve(pSpace);
}


auto ContingencyTableStorage::insert(InsertPair&& pInsert) -> InsertResult
{
	return mContainer.insert(std::forward<InsertPair>(pInsert));
}


auto ContingencyTableStorage::insert(InsertPair const& pInsert) -> InsertResult
{
	return mContainer.insert(pInsert);
}


auto ContingencyTableStorage::findTableCopy(TupleId pTupleId) const -> ContingencyTable
{
	return mContainer.find(pTupleId)->second;
}


auto ContingencyTableStorage::findTable(TupleId pTupleId) const -> ContingencyTable const&
{
	return mContainer.find(pTupleId)->second;
}


auto ContingencyTableStorage::findTable(TupleId pTupleId) -> ContingencyTable&
{
	return mContainer.find(pTupleId)->second;
}


auto ContingencyTableStorage::constructTable(
	TupleId 						pTupleId,
	MatrixTupleStoragePtrS const&	pTupleStorage) const -> ContingencyTable
{
	//DEBUG_MESSAGE("Getting table from id for: " << pTupleStorage->createTupleReprezentation(pTupleId));
	return findTable(pTupleId);
}


auto ContingencyTableStorage::constructTable(
	TupleT const&					pTupleT,
	MatrixTupleStoragePtrS const&	pTupleStorage) const -> ContingencyTable
{
	//DEBUG_MESSAGE("Getting table from tuple for: " << pTupleStorage->createTupleReprezentation(pTupleT));
	return findTable(pTupleStorage->findTupleId(pTupleT));
}


size_t ContingencyTableStorage::size() const
{
	return mContainer.size();
}


auto ContingencyTableStorage::begin() const -> ContainerIteratorConst
{
	return mContainer.begin();
}

auto ContingencyTableStorage::begin() -> ContainerIterator
{
	return mContainer.begin();
}

auto ContingencyTableStorage::end() const -> ContainerIteratorConst
{
	return mContainer.end();
}

auto ContingencyTableStorage::end() -> ContainerIterator
{
	return mContainer.end();
}


	}
}
