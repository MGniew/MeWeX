
#pragma once

#include <memory>

#include "TupleFeatureSource.h"

#include "../../function/association/VectorAssociationMeasure.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Generator cech dla instancji.
 *
 * Obiekt klasy służy do generowania cech dla instancji
 * przeznaczonych do maszynego uczenia, za pomocą funkcji
 * asocjacyjnych -- każda z funkcji staje się jedną z cech.
 *
 * @see Instance
 * @see VectorAssociationMeasure
 */
class TupleFeatureGenerator : public TupleFeatureSource
{
public:
	typedef function::association::VectorAssociationMeasure VectorAssociationMeasure;
	typedef std::shared_ptr<VectorAssociationMeasure>		VectorAssociationMeasurePtrS;


public:
	TupleFeatureGenerator(VectorAssociationMeasurePtrS const& pVectorAssociationMeasure);

	TupleFeatureGenerator()																	= default;
	TupleFeatureGenerator(TupleFeatureGenerator&& 					pTupleFeatureGenerator)	= default;
	TupleFeatureGenerator(TupleFeatureGenerator const& 				pTupleFeatureGenerator) = default;
	TupleFeatureGenerator& operator=(TupleFeatureGenerator&&	 	pTupleFeatureGenerator) = default;
	TupleFeatureGenerator& operator=(TupleFeatureGenerator const& 	pTupleFeatureGenerator) = default;

	virtual ~TupleFeatureGenerator() = default;


	VectorAssociationMeasurePtrS const& getVectorAssociationMeasure() const;
	VectorAssociationMeasurePtrS& 		getVectorAssociationMeasure();

	virtual size_t getFeatureCount() const override;


	virtual Instance constructInstance(
		TupleId 						pTupleId,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;

	virtual Instance constructInstance(
		TupleT const& 					pTupleT,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;

private:
	VectorAssociationMeasurePtrS mVectorAssociationMeasure;
};


	}
}
