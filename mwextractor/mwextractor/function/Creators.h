
#pragma once

#include <memory>
#include <map>
#include <string>

#include "Function.h"


namespace function
{


class Creators
{
public:
	typedef std::shared_ptr<Function> 		FunctionPtrS;
	typedef FunctionPtrS 					(*Creator)();
	typedef std::map<std::string, Creator> 	FunctionMapping;
};


class FilterFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS Not();
	static FunctionPtrS Or();
	static FunctionPtrS And();
	static FunctionPtrS Xor();

	static FunctionPtrS Frequency();
	static FunctionPtrS CorporaFrequency();
	static FunctionPtrS Relation();
	static FunctionPtrS EveryWord();
	static FunctionPtrS Tuple();

private:
	static FunctionMapping const MAPPING;
};


class DispersionFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS StandardDeviation();
	static FunctionPtrS VariationCoefficient();
	static FunctionPtrS JuillandD();
	static FunctionPtrS DistributionalConsistency();
	static FunctionPtrS LynesD3();
	static FunctionPtrS TermFrequencyInverseDocumentFrequency();

private:
	static FunctionMapping const MAPPING;
};


class AssociationFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	/* Frequency based */
	static FunctionPtrS Frequency();
	static FunctionPtrS ExpectedFrequency();
	static FunctionPtrS InversedExpectedFrequency();
	static FunctionPtrS Jaccard();
	static FunctionPtrS Dice();
	static FunctionPtrS Sorgenfrei();
	static FunctionPtrS OddsRatio();
	static FunctionPtrS UnigramSubtuples();
	static FunctionPtrS ConsonniT1();
	static FunctionPtrS ConsonniT2();

	/* Statistical measures */
	static FunctionPtrS MutualExpectation();
	static FunctionPtrS SpecificInformation();				// TODO: Test, consider signs
	static FunctionPtrS SpecificCorrelation();
	static FunctionPtrS WSpecificCorrelation();
	static FunctionPtrS SpecificMutualDependency();
	static FunctionPtrS SpecificFrequencyBiasedMutualDependency();
	static FunctionPtrS SpecificExponentialCorrelation();
	static FunctionPtrS WSpecificExponentialCorrelation();

	/* Statistical tests */
	static FunctionPtrS TScore();
	static FunctionPtrS ZScore();
	static FunctionPtrS PearsonsChiSquare();
	static FunctionPtrS WChiSquare();
	static FunctionPtrS LogLikelihood();

	/* Heuristics */
	static FunctionPtrS FairDispersionPointNormalization();
	static FunctionPtrS AverageBigram();
	static FunctionPtrS SmoothedBigram();					// TODO: Implement
	static FunctionPtrS MinimalBigram();

	/* Order based */
	static FunctionPtrS WOrder();
	static FunctionPtrS WTFOrder();

private:
	static FunctionMapping const MAPPING;
};


class VectorAssociationMeasureCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS VectorAssociationMeasure();

private:
	static FunctionMapping const MAPPING;
};


class ClassifierCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS MultilayerPerceptron();

private:
	static FunctionMapping const MAPPING;
};


class ScoreFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS Normalization();
	static FunctionPtrS BordaScore();
	static FunctionPtrS ZipfsBordaScore();
	static FunctionPtrS Centering();
	static FunctionPtrS Standarization();
	static FunctionPtrS ScoreFunctionChain();

private:
	static FunctionMapping const MAPPING;
};


class AggregationFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS MaxSum();
	static FunctionPtrS MaxMultiplier();

private:
	static FunctionMapping const MAPPING;
};


class QualityFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS Hit();
	static FunctionPtrS PrecisionCurve();
	static FunctionPtrS AveragePrecision();
	static FunctionPtrS AveragePrecisionRecallCurve();
	static FunctionPtrS MeanAveragePrecision();
	static FunctionPtrS AveragePrecisionOnHit();
	static FunctionPtrS RecallCurve();
	static FunctionPtrS PrecisionRecallCurve();
	static FunctionPtrS FMeasure();
	static FunctionPtrS ConfusionMatrixCreator();	// TODO: Test

private:
	static FunctionMapping const MAPPING;
};


class OptimizationFunctionCreators : public Creators
{
public:
	static FunctionMapping const& getMapping();

	static FunctionPtrS LinearCombination();

private:
	static FunctionMapping const MAPPING;
};


}
