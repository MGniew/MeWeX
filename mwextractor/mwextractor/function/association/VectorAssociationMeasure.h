/*
 * VectorAssociationMeasure.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <vector>
#include <memory>

#include "AssociationMeasure.h"

#include "../../structure/storage/ContingencyTable.h"


namespace function
{
	namespace association
	{


class VectorAssociationMeasure : public AbstractRanker
{
public:
	typedef structure::storage::MatrixTupleStorage 		MatrixTupleStorage;
	typedef MatrixTupleStorage::TupleId					TupleId;
	typedef structure::storage::ContingencyTable		ContingencyTable;

	typedef std::shared_ptr<AssociationMeasure> 		AssociationMeasurePtrS;
	typedef std::vector<AssociationMeasurePtrS> 		AssociationMeasurePtrSVector;

	typedef std::shared_ptr<VectorAssociationMeasure> 	VectorAssociationMeasurePtrS;

public:
	VectorAssociationMeasure(AssociationMeasurePtrSVector const& pAssociationFunctionPtrSVector);

	VectorAssociationMeasure()																		= default;
	VectorAssociationMeasure(VectorAssociationMeasure&& 				pVectorAssociationMeasure) 	= default;
	VectorAssociationMeasure(VectorAssociationMeasure const& 			pVectorAssociationMeasure);
	VectorAssociationMeasure& operator=(VectorAssociationMeasure&& 		pVectorAssociationMeasure) 	= default;
	VectorAssociationMeasure& operator=(VectorAssociationMeasure const&	pVectorAssociationMeasure);

	virtual ~VectorAssociationMeasure() = default;

	virtual VectorAssociationMeasurePtrS copy() const;


	virtual void initialize(RankerDataPtrS const& pRankerData) override;

	AssociationMeasurePtrSVector const& 	getAssociationMeasureVector() const;
	AssociationMeasurePtrSVector& 			getAssociationMeasureVector();


	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual std::vector<double> rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const&	pContingencyTable) const;

	virtual std::vector<double> rank(TupleId pTupleId) const;

	virtual std::vector<double> operator()(TupleId pTupleId) const;


	size_t size() const;

	virtual std::string	name() 				const override;
	virtual std::string reprezentation() 	const override;
	virtual std::string usage() 			const override;

private:
	AssociationMeasurePtrSVector mAssociationMeasures;
};


	}
}
