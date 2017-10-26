
#include <cmath>

#include "../../utils/Debug.h"
#include "../../exception/Exception.h"

#include "ContingencyTableGenerator.h"


namespace structure
{
	namespace storage
	{


ContingencyTableGenerator::ContingencyTableGenerator(
	size_t				pTupleFrequencySum,
	TableCreationPolicy pTableCreationPolicy)
:
	mTupleFrequencySum(pTupleFrequencySum),
	mTableCreationPolicy(pTableCreationPolicy)
{

}


auto ContingencyTableGenerator::insert(TupleT&& pInsert) -> InsertResult
{
	return mContainer.insert(std::forward<TupleT>(pInsert));
}


auto ContingencyTableGenerator::insert(TupleT const& pInsert) -> InsertResult
{
	return mContainer.insert(pInsert);
}


auto ContingencyTableGenerator::find(TupleT const& pTupleT) const -> ContainerIteratorConst
{
	return mContainer.find(pTupleT);
}


auto ContingencyTableGenerator::find(TupleT const& pTupleT) -> ContainerIterator
{
	return mContainer.find(pTupleT);
}


bool ContingencyTableGenerator::has(TupleT const& pTupleT) const
{
	return mContainer.find(pTupleT) != mContainer.end();
}


void ContingencyTableGenerator::setTupleFrequencySum(double pTupleFrequencySum)
{
	mTupleFrequencySum = pTupleFrequencySum;
}


auto ContingencyTableGenerator::createTable(TupleT const& pTupleT) const -> ContingencyTable
{
	switch (getTableCreationPolicy())
	{
		default:
		case TableCreationPolicy::JOIN_NONE:
		{
			ContingencyTable table = createTableJoinNoneRelations(pTupleT);
			table.computeExpected(mTupleFrequencySum);
			return table;
		}
		case TableCreationPolicy::JOIN_SAME_SIZE_RELATIONS:
		{
			ContingencyTable table = createTableJoinSameSizeRelations(pTupleT);
			table.computeExpected(mTupleFrequencySum);
			return table;
		}
	}
}


auto ContingencyTableGenerator::constructTable(
	TupleId 						pTupleId,
	MatrixTupleStoragePtrS const&	pTupleStorage) const -> ContingencyTable
{
	return createTable(pTupleStorage->findTuple(pTupleId));
}


auto ContingencyTableGenerator::constructTable(
	TupleT const&					pTupleT,
	MatrixTupleStoragePtrS const&	pTupleStorage) const -> ContingencyTable
{
	return createTable(pTupleT);
}


void ContingencyTableGenerator::setTableCreationPolicy(TableCreationPolicy pTableCreationPolicy)
{
	mTableCreationPolicy = pTableCreationPolicy;
}


auto ContingencyTableGenerator::getTableCreationPolicy() const -> TableCreationPolicy
{
	return mTableCreationPolicy;
}


size_t ContingencyTableGenerator::size() const
{
	return mContainer.size();
}


auto ContingencyTableGenerator::begin() const -> ContainerIteratorConst
{
	return mContainer.begin();
}

auto ContingencyTableGenerator::begin() -> ContainerIterator
{
	return mContainer.begin();
}

auto ContingencyTableGenerator::end() const -> ContainerIteratorConst
{
	return mContainer.end();
}

auto ContingencyTableGenerator::end() -> ContainerIterator
{
	return mContainer.end();
}


auto ContingencyTableGenerator::beginForAnyRelation(TupleT pTuple) const -> ContainerIteratorConst
{
	pTuple.setRelation(nullptr);
	return mContainer.lower_bound(pTuple);
}


auto ContingencyTableGenerator::beginForAnyRelation(TupleT pTuple) -> ContainerIterator
{
	pTuple.setRelation(nullptr);
	return mContainer.lower_bound(pTuple);
}


auto ContingencyTableGenerator::endForAnyRelation(TupleT pTuple) const -> ContainerIteratorConst
{
	pTuple.setRelation(nullptr);
	--pTuple.getRelation();
	return mContainer.upper_bound(pTuple);
}


auto ContingencyTableGenerator::endForAnyRelation(TupleT pTuple) -> ContainerIterator
{
	pTuple.setRelation(nullptr);
	--pTuple.getRelation();
	return mContainer.upper_bound(pTuple);
}


auto ContingencyTableGenerator::range(TupleT pTuple) const -> ContainerIteratorConstPair
{
	ContainerIteratorConstPair pair;

	pTuple.setRelation(nullptr);
	pair.first = mContainer.lower_bound(pTuple);

	--pTuple.getRelation();
	pair.second = mContainer.upper_bound(pTuple);

	return pair;
}


auto ContingencyTableGenerator::range(TupleT pTuple) -> ContainerIteratorPair
{
	ContainerIteratorPair pair;

	pTuple.setRelation(nullptr);
	pair.first = mContainer.lower_bound(pTuple);

	--pTuple.getRelation();
	pair.second = mContainer.upper_bound(pTuple);

	return pair;
}


auto ContingencyTableGenerator::createTableJoinNoneRelations(TupleT const& pTupleT) const -> ContingencyTable
{
	ContingencyTable table(pTupleT.subtupleCount());

	double thisFrequency = pTupleT.getMetadata().getGlobalFrequency();
	TupleT key(pTupleT.size(), nullptr, 0, 0);
	for (size_t i = 1; i < table.size() - 1; ++i)
	{
		pTupleT.createSubtuple(i, key);
		auto iter = find(key);
		if (iter != end())
		{
			table[i].observed = iter->getMetadata().getGlobalFrequency() - thisFrequency;
		}
	}

	table[0].observed 					= thisFrequency;
	table[table.size() - 1].observed 	= mTupleFrequencySum - table.sumObserved();

	return table;
}


auto ContingencyTableGenerator::createTableJoinSameSizeRelations(TupleT const& pTupleT) const -> ContingencyTable
{
	ContingencyTable table(pTupleT.subtupleCount());

	//DEBUG_MESSAGE("Tuple: " << pTupleT);

	double thisFrequency = pTupleT.getMetadata().getGlobalFrequency();
	TupleT key(pTupleT.size(), nullptr, 0, 0);
	for (size_t i = 1; i < table.size() - 1; ++i)
	{
		pTupleT.createSubtuple(i, key);
		ContainerIteratorConstPair iterPair = range(key);

		//DEBUG_MESSAGE("begin: " << i);

		while (iterPair.first != iterPair.second)
		{
			//DEBUG_MESSAGE('\t' << (*iterPair.first));
			table[i].observed += iterPair.first->getMetadata().getGlobalFrequency();
			++iterPair.first;
		}

		/* check if there was any hit - protect against lower than zero values */
		if (iterPair.first != iterPair.second)
		{
			/* only once because other tuples are from different relations */
			// table[i].observed = -thisFrequency;

			table[i].observed = std::max(0.0, table[i].observed - thisFrequency);
		}

		//DEBUG_MESSAGE("end  : " << (*iterPair.second));
	}

	//DEBUG_MESSAGE("");

	table[0].observed 					= pTupleT.getMetadata().getGlobalFrequency();
	table[table.size() - 1].observed 	= mTupleFrequencySum - table.sumObserved();

	return table;
}


	}
}
