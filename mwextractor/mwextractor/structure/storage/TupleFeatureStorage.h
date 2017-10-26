
#pragma once

#include <unordered_map>

#include "TupleFeatureSource.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Skład cech dla instancji.
 *
 * Obiekt klasy służy do składowania instancji -- przykładów
 * uczących, testowych lub innych, ogólnie obiektów klasy
 * Instance.
 *
 * @see Instance
 * @see VectorAssociationMeasure
 * @see TupleFeatureGenerator
 */
class TupleFeatureStorage : public TupleFeatureSource
{
public:
	typedef std::vector<Instance> 					InstanceVector;
	typedef MatrixTupleStorage::TupleId				TupleId;
	typedef std::unordered_map<TupleId, Instance>	InstanceMap;

	typedef std::vector<std::string> 				FeatureNameVector;
	typedef std::vector<std::string> 				HeaderNoteVector;

	struct MinMeanMax
	{
		double min;
		double mean;
		double max;
	};

	typedef std::vector<MinMeanMax> 				MinMeanMaxVector;

public:
	TupleFeatureStorage();

	TupleFeatureStorage(
		InstanceMap&& 	pInstanceMap,
		size_t			pClassCount);

	TupleFeatureStorage(
		InstanceMap const& 	pInstanceMap,
		size_t				pClassCount);

	TupleFeatureStorage(
		size_t 						pClassCount,
		FeatureNameVector const&	pFeatureNameVector,
		std::string const&			pRelationName,
		std::string const&			pReprezentationName,
		std::string const&			pClassName,
		HeaderNoteVector const&		pHeaderNotes);

	TupleFeatureStorage(TupleFeatureStorage&& 					pTupleFeatureStorage) = default;
	TupleFeatureStorage(TupleFeatureStorage const& 				pTupleFeatureStorage) = default;
	TupleFeatureStorage& operator=(TupleFeatureStorage&& 		pTupleFeatureStorage) = default;
	TupleFeatureStorage& operator=(TupleFeatureStorage const& 	pTupleFeatureStorage) = default;

	virtual ~TupleFeatureStorage() = default;


	TupleFeatureStorage copyMetadata() const;

	TupleFeatureStorage buildSubset(InstanceMap&& 		pInstanceVector) const;
	TupleFeatureStorage buildSubset(InstanceMap const& 	pInstanceVector) const;


	InstanceMap const& 			getInstanceMap() 		const;
	InstanceMap& 				getInstanceMap();

	FeatureNameVector const& 	getFeatureNameVector() 	const;
	FeatureNameVector& 			getFeatureNameVector();

	HeaderNoteVector const& 	getHeaderNoteVector() 	const;
	HeaderNoteVector& 			getHeaderNoteVector();

	std::string const&			getClassName()			const;
	std::string&				getClassName();

	std::string const&			getReprezentationName()	const;
	std::string&				getReprezentationName();

	std::string const&			getRelationName()		const;
	std::string&				getRelationName();

	size_t 						getInstanceCount() 		const;
	virtual size_t 				getFeatureCount() 		const override;
	size_t						getClassCount()			const;

	void setClassCount(size_t pClassCount);

	void setClassName(std::string const& pClassName);

	void setReprezentationName(std::string const& pRelationName);

	void setRelationName(std::string const& pRelationName);


	double findFeatureMin(size_t pFeatureIndex) 								const;
	double findFeatureMax(size_t pFeatureIndex) 								const;
	double computeFeatureMean(size_t pFeatureIndex) 							const;
	double computeFeatureVariance(size_t pFeatureIndex, double pMean) 			const;
	double computeFeatureVariance(size_t pFeatureIndex) 						const;
	double computeFeatureStandardDeviation(size_t pFeatureIndex, double pMean) 	const;
	double computeFeatureStandardDeviation(size_t pFeatureIndex) 				const;

	MinMeanMax 			computeMinMeanMax(size_t pFeatureIndex) const;
	MinMeanMaxVector 	computeMinMeanMax() const;


	virtual Instance constructInstance(
		TupleId 						pTupleId,
		MatrixTupleStoragePtrS const&	pTupleStorage) const override;

	virtual Instance constructInstance(
		TupleT const& 					pTupleT,
		MatrixTupleStoragePtrS const&	pTupleStorage) 	const override;


private:
	InstanceMap			mInstanceMap;
	size_t 				mClassCount;
	FeatureNameVector	mFeatureNameVector;
	std::string			mReprezentationName;
	std::string			mClassName;
	std::string			mRelationName;
	HeaderNoteVector	mHeaderNotes;
};


	}
}
