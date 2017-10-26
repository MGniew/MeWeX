
#pragma once

#include <memory>

#include "../../structure/storage/ContingencyTable.h"
#include "../../structure/storage/ContingencyTableSource.h"
#include "../../structure/storage/TupleFeatureSource.h"
#include "../../structure/storage/RelevantTupleIdSet.h"

#include "../filter/Filter.h"


namespace function
{
	namespace association
	{


class RankerData
{
public:
	typedef structure::storage::MatrixTupleStorage::TupleId				TupleId;
	typedef structure::storage::MatrixTupleStorage::TupleT				TupleT;
	typedef structure::storage::Instance								Instance;
	typedef structure::storage::ContingencyTable						ContingencyTable;
	typedef std::shared_ptr<filter::Filter>								FilterPtrS;

	typedef std::shared_ptr<structure::storage::MatrixTupleStorage>		MatrixTupleStoragePtrS;
	typedef std::shared_ptr<structure::storage::ContingencyTableSource>	ContingencyTableSourcePtrS;
	typedef std::shared_ptr<structure::storage::TupleFeatureSource> 	TupleFeatureSourcePtrS;
	typedef std::shared_ptr<structure::storage::RelevantTupleIdSet>		RelevantTupleIdSetPtrS;

public:
	RankerData(
		MatrixTupleStoragePtrS const& 		pMatrixTupleStorage,
		ContingencyTableSourcePtrS const&	pContingencyTableSource = nullptr,
		TupleFeatureSourcePtrS const&		pTupleFeatureSource = nullptr,
		RelevantTupleIdSetPtrS const&		pRelevantTupleIdSet = nullptr,
		FilterPtrS const&					pStatisticTupleFilter = nullptr);

	RankerData() 											= default;
	RankerData(RankerData&& 				pRankerData) 	= default;
	RankerData(RankerData const& 			pRankerData) 	= delete;
	RankerData& operator=(RankerData&&	 	pRankerData) 	= default;
	RankerData& operator=(RankerData const& pRankerData) 	= delete;

	~RankerData() = default;


	MatrixTupleStoragePtrS const&		getMatrixTupleStorage() 	const;
	ContingencyTableSourcePtrS const&	getContingencyTableSource()	const;
	TupleFeatureSourcePtrS const&		getTupleFeatureSource() 	const;
	RelevantTupleIdSetPtrS const&		getRelevantTupleIdSet()		const;
	FilterPtrS const&					getStatisticTupleFilter()	const;

	bool hasMatrixTupleStorage()		const;
	bool hasContingencyTableSource()	const;
	bool hasTupleFeatureSource()		const;
	bool hasRelevantTupleIdSet()		const;
	bool hasStatisticTupleFilter()		const;

	bool isTupleIdValid(TupleId pTupleId) const;

	void setMatrixTupleStorage(MatrixTupleStoragePtrS const& pMatrixTupleStorage);
	void setContingencyTableSource(ContingencyTableSourcePtrS const& pContingencyTableSource);
	void setTupleFeatureSource(TupleFeatureSourcePtrS const& pTupleFeatureSource);
	void setRelevantTupleIdSet(RelevantTupleIdSetPtrS const& pRelevantTupleIdSet);
	void setStatisticTupleFilter(FilterPtrS const& pStatisticTupleFilter);


	ContingencyTable 	constructContingencyTable(TupleId pTupleId) 		const;
	ContingencyTable 	constructContingencyTable(TupleT const& pTupleT) 	const;

	Instance 			constructInstance(TupleId pTupleId) 				const;
	Instance 			constructInstance(TupleT const& pTupleT) 			const;

	int					checkClass(TupleId pTupleId)						const;
	int					checkClass(TupleT const& pTupleT)					const;


private:
	MatrixTupleStoragePtrS		mMatrixTupleStorage;
	ContingencyTableSourcePtrS	mContingencyTableSource;
	TupleFeatureSourcePtrS 		mTupleFeatureSource;
	RelevantTupleIdSetPtrS		mRelevantTupleIdSet;

	/* Only this tuples from storage which pass this filter restrictions should be used by rankers */
	/* If nullptr then all tuples in storage are valid */
	FilterPtrS					mStatisticTupleFilter;
};


std::ostream& operator<<(std::ostream& pStream, RankerData const& pData);


	}
}
