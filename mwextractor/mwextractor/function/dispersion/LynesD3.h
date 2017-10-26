/*
 * LynesD3.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "DispersionFunction.h"

#include "../association/PearsonsChiSquare.h"


namespace function
{
	namespace dispersion
	{


class LynesD3 : public DispersionFunction
{
private:
	typedef association::PearsonsChiSquare 		PearsonsChiSquare;
	typedef function::association::RankerData	RankerData;
	typedef std::shared_ptr<RankerData>			RankerDataPtrS;

public:
	LynesD3();

	LynesD3(LynesD3&& 					pLynesD3)	= default;
	LynesD3(LynesD3 const& 				pLynesD3)	= default;
	LynesD3& operator=(LynesD3&& 		pLynesD3)	= default;
	LynesD3& operator=(LynesD3 const& 	pLynesD3)	= default;

	virtual ~LynesD3() = default;


	virtual double disperse(TupleId pTupleId) const override;

	virtual std::string	name() const override;


private:
	PearsonsChiSquare 	mPx2;
	RankerDataPtrS		mRankerData;
};


	}
}
