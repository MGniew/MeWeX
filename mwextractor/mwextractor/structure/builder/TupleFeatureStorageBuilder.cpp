
#include "../../utils/Parallel.h"

#include "TupleFeatureStorageBuilder.h"


namespace structure
{
	namespace builder
	{


auto TupleFeatureStorageBuilder::build(
	TupleFeatureGenerator const&	pTupleFeatureGenerator,
	MatrixTupleStoragePtrS const&	pTupleStorage,
	TupleIdVector const&			pInterestedTupleIdVector,
	size_t							pThreadCount) const -> TupleFeatureStoragePtrS
{
	typedef TupleFeatureStorage::TupleId		__TID;
	typedef storage::Instance 					__Inst;
	typedef TupleFeatureStorage::InstanceVector	__InstVec;
	typedef TupleFeatureStorage::InstanceMap	__InstMap;

	std::mutex add;
	__InstMap map;
	utils::parallelFor(0, pInterestedTupleIdVector.size(), [&](
		size_t pThreadId,
		size_t pIndex)
	{
		__Inst inst = pTupleFeatureGenerator.constructInstance(
			pInterestedTupleIdVector[pIndex], pTupleStorage);
		XASSERT(
				inst.getFeatureVector().size() != 0 && inst.getFeatureVector().size() == pTupleFeatureGenerator.getFeatureCount(),
			"TupleFeatureStorageBuilder::build(): Features generation error.");
		add.lock();
		map.insert(std::pair<__TID, __Inst>(pInterestedTupleIdVector[pIndex], std::forward<__Inst>(inst)));
		add.unlock();
	},
	pThreadCount);

	TupleFeatureStoragePtrS dataSet(new TupleFeatureStorage(std::forward<__InstMap>(map), 2));
	dataSet->setReprezentationName("reprezentation");
	dataSet->setClassName("is MWE");

	dataSet->getFeatureNameVector().reserve(pTupleFeatureGenerator.getFeatureCount());
	for (size_t i = 0; i < pTupleFeatureGenerator.getFeatureCount(); ++i)
	{
		dataSet->getFeatureNameVector().push_back(pTupleFeatureGenerator.
			getVectorAssociationMeasure()->getAssociationMeasureVector()[i]->reprezentation());
	}

	return dataSet;
}


	}
}
