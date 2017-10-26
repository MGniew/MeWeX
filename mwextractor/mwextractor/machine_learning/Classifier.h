
#pragma once

#include <memory>

#include "../function/association/AssociationMeasure.h"
#include "../structure/storage/TupleFeatureSource.h"


namespace machine_learning
{


/**
 * \brief Klasa bazowa dla klasyfikatorów.
 */
class Classifier : public function::association::AssociationMeasure
{
public:
	typedef structure::storage::MatrixTupleStorage::TupleT			TupleT;
	typedef structure::storage::MatrixTupleStorage::TupleIdVector	TupleIdVector;
	typedef structure::storage::Instance							Instance;
	typedef std::shared_ptr<Classifier>								ClassifierPtrS;

public:
	Classifier() 											= default;
	Classifier(Classifier&& 				pClassifier) 	= default;
	Classifier(Classifier const& 			pClassifier) 	= default;
	Classifier& operator=(Classifier&& 		pClassifier) 	= default;
	Classifier& operator=(Classifier const& pClassifier) 	= default;

	virtual ~Classifier() = default;

	virtual AssociationMeasurePtrS	copy()	const override;
	virtual ClassifierPtrS 			clone() const = 0;


	virtual void construct(TupleIdVector const& pTrainData) = 0;

	/**
	 * \brief ContingencyTable jest pomijany.
	 *
	 * ContingencyTable jest pomijany, a wywołanie tej funkcji
	 * jest równoważne rank(TupleId).
	 */
	virtual double rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const;

	virtual double rankInstance(Instance const& pInstance) 	const = 0;
	virtual double rankTuple(TupleT const& pTupleT) 		const = 0;

	virtual int classify(Instance const& pInstance) 		const = 0;
	virtual int classify(TupleId pTupleId)					const = 0;
	virtual int classify(TupleT const& pTupleT)				const = 0;
};


}
