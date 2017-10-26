/*
 * Disperser.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "../../structure/storage/ContingencyTableSource.h"

#include "DispersionFunction.h"


namespace function
{
	namespace dispersion
	{


class Disperser
{
public:
	typedef structure::storage::MatrixTupleStorage			TupleStorage;
	typedef std::shared_ptr<TupleStorage>					TupleStoragePtrS;
	typedef structure::storage::ContingencyTable 			ContingencyTable;
	typedef ContingencyTable::ContingencyValue				ContingencyValue;
	typedef structure::storage::ContingencyTableSource		ContingencyTableSource;
	typedef std::shared_ptr<ContingencyTableSource>			ContingencyTableSourcePtrS;
	typedef std::shared_ptr<DispersionFunction> 			DispersionFunctionPtrS;

	typedef TupleStorage::TupleId							TupleId;

	typedef std::pair<TupleId, double>						TupleDispersion;
	typedef std::vector<TupleDispersion>					TupleDispersionVector;
	typedef std::shared_ptr<TupleDispersionVector>			TupleDispersionVectorPtrS;

public:
	Disperser()											= default;
	Disperser(Disperser&& 					pStorage) 	= default;
	Disperser(Disperser const& 				pStorage) 	= default;
	Disperser& operator=(Disperser&& 		pStorage) 	= default;
	Disperser& operator=(Disperser const& 	pStorage) 	= default;

	virtual ~Disperser() = default;

	TupleDispersionVectorPtrS 	dispersTuples(
									DispersionFunctionPtrS const& pFunction,
									bool pInverseDispersionValues = false) const;

	size_t						updateStorage(
									TupleDispersionVectorPtrS const& 	pDispersionVector,
									TupleStoragePtrS const& 			pOutputTupleStorage,
									double								pThreshold = 0.0) const;

	size_t						dispersTuplesInPlace(
									DispersionFunctionPtrS const& 	pFunction,
									TupleStoragePtrS const&			pOutputTupleStorage,
									bool 							pInverseDispersionValues = false,
									double							pThreshold = 0.0)	const;


	double						sum(TupleDispersionVectorPtrS const& pVector) const;
};


	}
}
