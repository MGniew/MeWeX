
#pragma once

#include "../../structure/io/RelevantTupleSetLoader.h"

#include "RankerData.h"
#include "../../structure/storage/TupleFeatureGenerator.h"
#include "../../structure/storage/TupleFeatureStorage.h"

#include "../../structure/builder/ContingencyTableStorageBuilder.h"
#include "../../structure/builder/ContingencyTableGeneratorBuilder.h"
#include "../../structure/builder/TupleFeatureStorageBuilder.h"

#include "../../machine_learning/FoldsBuilder.h"

#include "../../function/FunctionFactory.h"
#include "../../function/filter/Filtrator.h"

#include "Extractor.h"


namespace function
{
	namespace association
	{


/**
 * \brief Moduł wykonuje walidację krzyżową dla miar i klasyfikatorów.
 */
class CrossValidator : public Extractor
{
public:
	typedef std::shared_ptr<RankerData>								RankerDataPtrS;
	typedef structure::storage::MatrixTupleStorage					MatrixTupleStorage;
	typedef std::shared_ptr<MatrixTupleStorage>						MatrixTupleStoragePtrS;
	typedef MatrixTupleStorage::TupleIdVector						TupleIdVector;
	typedef MatrixTupleStorage::TupleIdSet							TupleIdSet;

	typedef structure::storage::TupleFeatureGenerator				TupleFeatureGenerator;
	typedef std::shared_ptr<TupleFeatureGenerator>					TupleFeatureGeneratorPtrS;
	typedef structure::storage::TupleFeatureStorage					TupleFeatureStorage;
	typedef std::shared_ptr<TupleFeatureStorage>					TupleFeatureStoragePtrS;

	typedef structure::builder::ContingencyTableGeneratorBuilder 	ContingencyTableGeneratorBuilder;
	typedef structure::builder::ContingencyTableStorageBuilder 		ContingencyTableStorageBuilder;
	typedef structure::builder::TupleFeatureStorageBuilder			TupleFeatureStorageBuilder;

	typedef structure::storage::ContingencyTableGenerator			ContingencyTableGenerator;
	typedef std::shared_ptr<ContingencyTableGenerator>				ContingencyTableGeneratorPtrS;
	typedef structure::storage::ContingencyTableStorage				ContingencyTableStorage;
	typedef std::shared_ptr<ContingencyTableStorage>				ContingencyTableStoragePtrS;
	typedef ContingencyTableGenerator::TableCreationPolicy			ContingencyTableCreationPolicy;

	typedef structure::io::RelevantTupleSetLoader					RelevantTupleSetLoader;
	typedef RelevantTupleSetLoader::RelevantTupleIdSetPtrS			RelevantTupleIdSetPtrS;

	typedef machine_learning::FoldsBuilder<TupleId> 				FoldsBuilder;
	typedef FoldsBuilder::Fold										Fold;
	typedef FoldsBuilder::FoldVector								FoldVector;
	typedef std::vector<RelevantTupleIdSetPtrS>						RelevantTupleIdSetPtrSVector;

	typedef function::FunctionFactory								FunctionFactory;

	typedef FunctionFactory::FilterFunctionPtrS						FilterFunctionPtrS;
	typedef FunctionFactory::AssociationFunctionPtrS				AssociationFunctionPtrS;
	typedef std::vector<AssociationFunctionPtrS>					AssociationFunctionPtrSVector;
	typedef FunctionFactory::VectorAssociationMeasurePtrS			VectorAssociationMeasurePtrS;
	typedef std::vector<VectorAssociationMeasurePtrS>				VectorAssociationMeasurePtrSVector;
	typedef FunctionFactory::ClassifierPtrS							ClassifierPtrS;
	typedef std::vector<ClassifierPtrS>								ClassifierPtrSVector;
	typedef FunctionFactory::ScoreFunctionPtrS						ScoreFunctionPtrS;
	typedef FunctionFactory::AggregationFunctionPtrS				AggregationFunctionPtrS;
	typedef std::vector<AggregationFunctionPtrS>					AggregationFunctionPtrSVector;


public:
	/**
	 * \brief Zestaw funkcji używanych w walidacji krzyżowej.
	 */
	struct FunctionSet
	{
		FilterFunctionPtrS					statisticFilter;
		FilterFunctionPtrS					extractionFilter;

		ClassifierPtrSVector 				classifierVector;
		VectorAssociationMeasurePtrSVector 	vectorAssociationMeasureVector;
		AssociationFunctionPtrSVector		associationFunctionVector;

		VectorAssociationMeasurePtrS		featureGenerator;
		ScoreFunctionPtrS					featureProcessor;
		AggregationFunctionPtrSVector		vectorMeasureAggregatorVector;
	};

	/**
	 * \brief Zestaw parameterów dla walidacji krzyżowej.
	 */
	struct ParameterSet
	{
		size_t 							foldCount;
		FoldsBuilder::Policy			foldCreationPolicy;
		ContingencyTableCreationPolicy	tableCreationPolicy;
		size_t 							rankSize;
		size_t 							threadCount;
	};

	/**
	 * \brief Zbiór zestawów danych.
	 */
	struct DataSet
	{
		MatrixTupleStoragePtrS tupleStorage;
		RelevantTupleIdSetPtrS relevantTupleIdSet;
	};

	/**
	 * \brief Struktura wynikowa walidacji krzyżowej każdego z foldów.
	 */
	struct Result
	{
		/* index = function identifier */
		KBestTupleListVector 	foldResultForFunctions;
		/* contains relevant tuple id set for this fold after extraction filter */
		RelevantTupleIdSetPtrS 	foldRelevantTupleIdSetExtraction;
	};
	typedef std::shared_ptr<Result> ResultPtrS;


public:
	CrossValidator(
		FunctionSet const&		pFunctionSet,
		ParameterSet const&		pParameterSet,
		DataSet const&			pDataSet);

	CrossValidator(CrossValidator&& 				pCrossValidator) 	= default;
	CrossValidator(CrossValidator const& 			pCrossValidator) 	= default;
	CrossValidator& operator=(CrossValidator&& 		pCrossValidator) 	= default;
	CrossValidator& operator=(CrossValidator const& pCrossValidator) 	= default;

	virtual ~CrossValidator() = default;

	/**
	 * \brief Przygotowuje kolejną rundę walidacji krzyżowej.
	 *
	 * Należy wykonać tę funkcję przed każdą rundą
	 * walidacji krzyżowej.
	 * Funkcja automatycznie czyści stan obiektu.
	 */
	virtual void prepareRound();

	/**
	 * \brief Wykonanie obliczeń dla kolejnego foldu w danej rundzie.
	 *
	 * Wywołanie tej funkcji więcej razy niż liczba foldów
	 * zadeklarowana w zestawie parametrów spowoduje błąd
	 * i wyrzucenie wyjątku.
	 *
	 * @see Exception
	 * @see ParameterSet
	 */
	virtual ResultPtrS performForNextFold();


private:
	void initialize();


private:
	/* contains pointers copy */
	FunctionSet 	mFunctionSet;

	/* contains pointers copy */
	ParameterSet	mParameterSet;

	/* contains parameters values */
	DataSet			mDataSet;

private:
	/* other temporary values */
	FoldVector 						mFolds;
	RankerDataPtrS					mRankerData;
	VectorAssociationMeasurePtrS	mPackedFunctions;
	TupleFeatureGeneratorPtrS 		mFeatureGenerator;

	size_t							mCurrentFold;
};


	}
}
