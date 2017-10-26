/*
 * Extractor.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include "../../utils/Parallel.h"

#include "../../structure/container/Array2D.h"

#include "AssociationMeasure.h"
#include "VectorAssociationMeasure.h"
#include "AssociationFunction.h"
#include "../../machine_learning/Classifier.h"

#include "../score/ScoreFunction.h"

#include "../aggregation/AggregationFunction.h"


namespace function
{
	namespace association
	{


class Extractor
{
public:
	typedef structure::storage::MatrixTupleStorage::TupleId			TupleId;
	typedef structure::storage::MatrixTupleStorage::TupleIdVector	TupleIdVector;

	typedef structure::storage::KBestTupleStructure					KBestTupleStructure;
	typedef structure::storage::KBestTupleList						KBestTupleList;
	typedef structure::storage::KBestTupleListVector				KBestTupleListVector;
	typedef structure::storage::VectorAssociationResult				VectorAssociationResult;

	typedef std::shared_ptr<AssociationMeasure> 					AssociationMeasurePtrS;
	typedef std::vector<AssociationMeasurePtrS> 					AssociationMeasurePtrSVector;
	typedef std::shared_ptr<VectorAssociationMeasure>				VectorAssociationMeasurePtrS;
	typedef std::shared_ptr<AssociationFunction>					AssociationFunctionPtrS;
	typedef std::vector<AssociationFunctionPtrS>					AssociationFunctionPtrSVector;
	typedef machine_learning::Classifier							Classifier;
	typedef std::shared_ptr<Classifier>								ClassifierPtrS;
	typedef std::shared_ptr<aggregation::AggregationFunction>		AggregationFunctionPtrS;


public:
	Extractor()											= default;
	Extractor(Extractor&& 					pExtractor) = default;
	Extractor(Extractor const& 				pExtractor) = default;
	Extractor& operator=(Extractor&& 		pExtractor) = default;
	Extractor& operator=(Extractor const& 	pExtractor) = default;

	virtual ~Extractor() = default;

	virtual KBestTupleList extract(
		AssociationMeasurePtrS const& 	pMeasure,
		TupleIdVector const&			pTupleIdVector,
		size_t 							pRankSize,
		size_t							pThreadCount) const;

	virtual KBestTupleListVector extract(
		VectorAssociationMeasurePtrS const& pVectorMeasure,
		TupleIdVector const&				pTupleIdVector,
		size_t 								pRankSize,
		size_t								pThreadCount) const;

	virtual VectorAssociationResult extractUnranked(
		VectorAssociationMeasurePtrS const& pVectorMeasure,
		TupleIdVector const&				pTupleIdVector,
		size_t								pThreadCount) const;
};


	}
}
