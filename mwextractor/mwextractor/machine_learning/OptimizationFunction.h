
#pragma once

#include <memory>

#include "../function/association/AbstractRanker.h"

#include "../function/Function.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
 * \brief Klasa bazowa dla funkcji optymalizujących parametery wektorowych miar asocjacyjnych.
 */
class OptimizationFunction : public function::association::AbstractRanker
{
public:
	typedef function::association::RankerData		RankerData;
	typedef std::shared_ptr<RankerData> 			RankerDataPtrS;
	typedef TupleStorage::TupleIdVector				TupleIdVector;

	typedef std::pair<double, std::vector<double>> 	OptimizationResult;
	typedef std::map<double, std::vector<double>>	OptimizationResultMap;

public:
	OptimizationFunction()																= default;
	OptimizationFunction(OptimizationFunction&& 				pOptimizationFunction)	= default;
	OptimizationFunction(OptimizationFunction const& 			pOptimizationFunction)	= default;
	OptimizationFunction& operator=(OptimizationFunction&& 		pOptimizationFunction)	= default;
	OptimizationFunction& operator=(OptimizationFunction const& pOptimizationFunction)	= default;

	virtual ~OptimizationFunction() = default;


	/**
	 * \brief Optymalizacja parameterów z wykorzystaniem zadanych danych.
	 */
	virtual void optimize(TupleIdVector const& pData) const = 0;


	OptimizationResultMap const& 	getLastOptimizationResultMap() const;
	OptimizationResultMap& 			getLastOptimizationResultMap();

	OptimizationResult				getBestLastOptimizationResult() const;

protected:
	mutable OptimizationResultMap mOptimizationResultMap;
};


	}
}
