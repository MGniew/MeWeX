/*
 * AssociationMeasure.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <memory>
#include <limits>

#include "AbstractRanker.h"

#include "../../structure/storage/ContingencyTable.h"


namespace function
{
	namespace association
	{


class AssociationMeasure : public AbstractRanker
{
public:
	typedef structure::storage::MatrixTupleStorage 	MatrixTupleStorage;
	typedef MatrixTupleStorage::TupleId				TupleId;
	typedef structure::storage::ContingencyTable	ContingencyTable;
	typedef std::shared_ptr<AssociationMeasure>		AssociationMeasurePtrS;

public:
	AssociationMeasure()															= default;
	AssociationMeasure(AssociationMeasure&& 				pAssociationMeasure)	= default;
	AssociationMeasure(AssociationMeasure const& 			pAssociationMeasure)	= default;
	AssociationMeasure& operator=(AssociationMeasure&& 		pAssociationMeasure)	= default;
	AssociationMeasure& operator=(AssociationMeasure const& pAssociationMeasure)	= default;

	virtual ~AssociationMeasure() = default;


	virtual double rank(TupleId pTupleId) const = 0;

	virtual double rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const = 0;

	double operator()(TupleId pTupleId) const;

	double operator()(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const;


	virtual AssociationMeasurePtrS copy() const = 0;


protected:
	static constexpr double minDouble(){ return -std::numeric_limits<double>::max(); }
};


	}
}
