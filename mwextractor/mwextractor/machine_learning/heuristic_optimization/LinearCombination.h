
#pragma once

#include <memory>

#include "../OptimizationFunction.h"

#include "../../structure/storage/MatrixTupleStorage.h"
#include "../../structure/storage/TupleFeatureGenerator.h"
#include "../../structure/storage/ContingencyTableGenerator.h"
#include "../../structure/storage/ContingencyTableStorage.h"
#include "../../structure/io/RelevantTupleSetLoader.h"
#include "../../function/association/VectorAssociationMeasure.h"
#include "../../function/aggregation/AggregationFunction.h"
#include "../../function/association/Extractor.h"
#include "../../function/quality/QualityFunction.h"

#include "Evaluator.h"
#include "EvaluatorWrapper.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
 * \brief Obiekt klasy umożliwia optymalizację wag dla kombinacji liniowej.
 *
 * Obiekt klasy umożliwia optymalizację wag dla funkcji składowych
 * kombinacji liniowej z wykorzystaniem pięciu różnych algorytmów
 * heurystycznych.
 *
 * ===
 * Parametery dla tej funkcji:
 * Typ metody (nazwa):
 * ~~~
 * HC -- wspinaczka
 * RS -- przeszukiwanie losowe
 * TS -- przeszukiwanie tabu
 * SA -- symulowane wyżarzanie
 * EA -- algorytm ewolucyjny
 * PSO -- particle swarm optimization
 *
 * method=[HC|RS|TS|SA|EA|PSO]
 * ~~~
 *
 * Plik konfiguracyjny metod (ścieżka):
 * ~~~
 * methods_config=file_path
 * ~~~
 *
 * Kombinacja miar:
 * ~~~
 * vam=definicja_vam
 * ~~~
 *
 * Miara agregacji:
 * ~~~
 * aggregator=definicja_agregatora
 * ~~~
 *
 * Funkcja oceny stosowana w kombinacji liniowej:
 * ~~~
 * quality_function=definicja_funkcji_oceny
 * ~~~
 *
 * Długość listy k-najlepszych poddawana ocenie:
 * Parameter definiuje wynikową długość listy k-najlepszych,
 * która zostanie następnie poddana ocenie.
 * ~~~
 * quality_kbest_length=definicja_funkcji_oceny
 * ~~~
 *
 * Liczba dostepnych watkow w obliczeniach:
 * ~~~
 * threads=liczba_całkowita
 * ~~~
 *
 * Minimalna wartość parametru:
 * Musi być mniejsza od "max_value".
 * ~~~
 * min_value=liczba_rzeczywista
 * ~~~
 *
 * Maksymalna wartość parametru:
 * Musi być większa od "min_value".
 * ~~~
 * max_value=liczba_rzeczywista
 * ~~~
 *
 * Krok optymalizacji:
 * Musi być mniejszy lub równy "max_value" - "min_value".
 * ~~~
 * step_value=liczba_rzeczywista
 * ~~~
 *
 * @see VectorAssociationMeasure
 * @see AggregationFunction
 * @see ScoreFunction
 * @see QualityFunction
 */
class LinearCombination :
	public OptimizationFunction,
	public Evaluator
{
private:
	typedef structure::storage::MatrixTupleStorage 				TupleStorage;
	typedef std::shared_ptr<TupleStorage> 						TupleStoragePtrS;

	typedef structure::storage::ContingencyTableGenerator		ContingencyTableGenerator;
	typedef std::shared_ptr<ContingencyTableGenerator>			ContingencyTableGeneratorPtrS;

	typedef structure::storage::ContingencyTableStorage			ContingencyTableStorage;
	typedef std::shared_ptr<ContingencyTableStorage>			ContingencyTableStoragePtrS;

	typedef structure::io::RelevantTupleSetLoader				RelevantLoader;
	typedef RelevantLoader::RelevantTupleIdSet					RelevantTupleIdSet;
	typedef TupleStorage::TupleIdVector							TupleIdVector;

	typedef function::association::VectorAssociationMeasure		VectorAssociationMeasure;
	typedef std::shared_ptr<VectorAssociationMeasure>			VectorAssociationMeasurePtrS;

	typedef function::aggregation::AggregationFunction			AggregationFunction;
	typedef std::shared_ptr<AggregationFunction>				AggregationFunctionPtrS;

	typedef function::quality::QualityFunction					QualityFunction;
	typedef std::shared_ptr<QualityFunction>					QualityFunctionPtrS;

	typedef function::association::Extractor 					Extractor;


public:
	LinearCombination(
		std::string const&					pMethodName = "EA",
		std::string const&					pMethodsName = "",
		VectorAssociationMeasurePtrS const& pVectorAssociationFunction = nullptr,
		AggregationFunctionPtrS const& 		pAggregationFunction = nullptr,
		QualityFunctionPtrS	const& 			pQualityFunction = nullptr,
		size_t								pKBestQualityLength = static_cast<size_t>(-1),
		size_t 								pWorkerThreadCount = 1,
		double								pMinParameterValue = -1.0,
		double								pMaxParameterValue = 1.0,
		double								pParameterStepValue = 0.05);

	LinearCombination(LinearCombination const& pLinearCombination);
	LinearCombination& operator=(LinearCombination const& pLinearCombination);

	LinearCombination(LinearCombination&& pLinearCombination) = default;
	LinearCombination& operator=(LinearCombination&& pLinearCombination) = default;

	virtual ~LinearCombination() = default;


	virtual void initialize(RankerDataPtrS const& pRankerDataPtrS) override;

	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual std::string	name() 				const override;
	virtual std::string	reprezentation() 	const override;
	virtual std::string	usage() 			const override;

	virtual void optimize(TupleIdVector const& pData) const override;

	virtual double evaluateIndividual(Point const& pPoint) override;

private:
	void construct();

	Point buildStartPoint() const;

	void updateWeights(Point const& pPoint);

private:
	std::string							mMethodName;
	std::string							mMethodsConfig;

	VectorAssociationMeasurePtrS		mVectorAssociationFunction;
	AggregationFunctionPtrS				mAggregationFunction;
	QualityFunctionPtrS					mQualityFunction;

	size_t								mKBestQualityLength;
	size_t								mWorkerThreadCount;

	double								mMinParameterValue;
	double 								mMaxParameterValue;
	double								mParameterStepValue;

	std::unique_ptr<EvaluatorWrapper>	mEvaluatorWrapper;

private:
	mutable TupleIdVector const* 		mTempTupleData;
};


	}
}
