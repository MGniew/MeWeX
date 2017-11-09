
#include "../../utils/Time.h"
#include "ContingencyTableGeneratorBuilder.h"


namespace structure
{
	namespace builder
	{


auto ContingencyTableGeneratorBuilder::build(
	TupleStorageConstPtrS const&	pTupleStorage,
	TupleIdVector const&			pTupleIdVector,
	TableCreationPolicy 			pCreationPolicy
	) const -> ContingencyTableGeneratorPtrS
{
	typedef ContingencyTableGenerator::InsertResult __Res;

	ContingencyTableGeneratorPtrS generator(new ContingencyTableGenerator((size_t)0, pCreationPolicy));

	std::vector<TupleT> keys;
	{
		size_t maxRelationSize = 0;
		for (auto iter = pTupleStorage->beginRelations(); iter != pTupleStorage->endRelations(); ++iter)
		{
			if (maxRelationSize < iter->getArity())
			{
				maxRelationSize = iter->getArity();
			}
		}

		for (size_t i = 0; i <= maxRelationSize; ++i)
		{
			keys.push_back(TupleT(i, nullptr, 0, 0));
		}
	}

	double sum = 0;
	for (size_t i = 0; i < pTupleIdVector.size(); ++i)
	{
		TupleT const& tuple = pTupleStorage->findTuple(pTupleIdVector[i]);

		TupleT& key = keys[tuple.size()];
		size_t tableSize = tuple.subtupleCount();

		for (size_t t = 1; t < tableSize - 1; ++t)
		{
			tuple.createSubtuple(t, key);
			__Res generatorIter = generator->insert(key);
			generatorIter.first->getMetadata().modifyGlobalFrequency(
				tuple.getMetadata().getGlobalFrequency());
		}

		sum += tuple.getMetadata().getGlobalFrequency();
	}
	generator->setTupleFrequencySum(sum);

	return generator;
}


	}
}
