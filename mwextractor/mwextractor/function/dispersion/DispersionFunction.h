/*
 * AssociationFunction.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "DispersionData.h"

#include "../Function.h"


namespace function
{
	namespace dispersion
	{


class DispersionFunction : public Function
{
public:
	typedef DispersionData::MatrixTupleStoragePtrS		MatrixTupleStoragePtrS;
	typedef DispersionData::ContingencyTableSourcePtrS	ContingencyTableSourcePtrS;
	typedef DispersionData::TupleId 					TupleId;
	typedef DispersionData::TupleT 						TupleT;

	typedef std::shared_ptr<DispersionData>				DispersionDataPtrS;


public:
	DispersionFunction();

	DispersionFunction(DispersionFunction&& 				pDispersionFunction)	= default;
	DispersionFunction(DispersionFunction const& 			pDispersionFunction)	= default;
	DispersionFunction& operator=(DispersionFunction&& 		pDispersionFunction)	= default;
	DispersionFunction& operator=(DispersionFunction const& pDispersionFunction)	= default;

	virtual ~DispersionFunction() = default;


	virtual double disperse(TupleId 			pTableId) 	const = 0;
	virtual double disperse(TupleT const& 		pTableT) 	const;
	virtual double operator()(TupleId 			pTableId)	const;
	virtual double operator()(TupleId const& 	pTableT)	const;


	DispersionDataPtrS const& 	getDispersionData() const;
	DispersionDataPtrS& 		getDispersionData();

	bool hasDispersionData() const;

	void setDispersionData(DispersionDataPtrS const& pDispersionData);

	virtual void initialize(DispersionDataPtrS const& pDispersionData);

private:
	DispersionDataPtrS mDispersionData;
};


	}
}
