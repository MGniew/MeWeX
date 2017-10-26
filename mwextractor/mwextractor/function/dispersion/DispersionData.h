
#pragma once

#include <memory>

#include "../../structure/storage/ContingencyTable.h"
#include "../../structure/storage/ContingencyTableSource.h"
#include "../../structure/storage/TupleFeatureSource.h"
#include "../../structure/storage/RelevantTupleIdSet.h"


namespace function
{
	namespace dispersion
	{


class DispersionData
{
public:
	typedef structure::storage::MatrixTupleStorage::TupleId				TupleId;
	typedef structure::storage::MatrixTupleStorage::TupleT				TupleT;
	typedef structure::storage::ContingencyTable						ContingencyTable;

	typedef std::shared_ptr<structure::storage::MatrixTupleStorage>		MatrixTupleStoragePtrS;
	typedef std::shared_ptr<structure::storage::ContingencyTableSource>	ContingencyTableSourcePtrS;

public:
	DispersionData(
		MatrixTupleStoragePtrS const& 		pMatrixTupleStorage,
		ContingencyTableSourcePtrS const&	pContingencyTableSource = nullptr);

	DispersionData() 													= default;
	DispersionData(DispersionData&& 				pDispersionData) 	= default;
	DispersionData(DispersionData const& 			pDispersionData) 	= delete;
	DispersionData& operator=(DispersionData&&	 	pDispersionData) 	= default;
	DispersionData& operator=(DispersionData const& pDispersionData) 	= delete;

	~DispersionData() = default;


	MatrixTupleStoragePtrS const&		getMatrixTupleStorage() 	const;
	ContingencyTableSourcePtrS const&	getContingencyTableSource()	const;

	bool hasMatrixTupleStorage()		const;
	bool hasContingencyTableSource()	const;

	void setMatrixTupleStorage(MatrixTupleStoragePtrS const& pMatrixTupleStorage);
	void setContingencyTableSource(ContingencyTableSourcePtrS const& pContingencyTableSource);


	ContingencyTable 	constructContingencyTable(TupleId pTupleId) 		const;
	ContingencyTable 	constructContingencyTable(TupleT const& pTupleT) 	const;


private:
	MatrixTupleStoragePtrS		mMatrixTupleStorage;
	ContingencyTableSourcePtrS	mContingencyTableSource;
};


std::ostream& operator<<(std::ostream& pStream, DispersionData const& pData);


	}
}
