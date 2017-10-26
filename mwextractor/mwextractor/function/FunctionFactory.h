
#pragma once

#include <map>

#include "filter/Filter.h"

#include "dispersion/DispersionFunction.h"

#include "association/AssociationFunction.h"
#include "association/VectorAssociationMeasure.h"
#include "../machine_learning/Classifier.h"

#include "score/ScoreFunction.h"

#include "aggregation/AggregationFunction.h"

#include "quality/QualityFunction.h"

#include "Creators.h"


namespace function
{


/**
 * \brief Fabryka funkcji tworząca je na podstawie ciągów tekstowych.
 *
 * Obiekt klasy potrafi parsować ciągi tekstowe i tworzyć
 * na jego podstawie określone funkcje (obiekty innych klas).
 * Podczas parsowania tekstu białe znaki są usuwane z ciągu.
 * Obiekt klasy sprawdza także czy podane zostały wszystkie
 * wymagane dla funkcji argumenty oraz czy sama funkcja
 * (jej nazwa) jest określona.
 *
 * @see AssociationFunction
 * @see VectorAssociationFunction
 * @see Classifier
 * @see ScoreFunction
 * @see AggregationFunction
 * @see QualityFunction
 * @see OptimizationFunction
 */
class FunctionFactory
{
public:
	typedef Creators::FunctionPtrS						FunctionPtrS;
	typedef Creators::FunctionMapping					FunctionMapping;

	typedef filter::Filter								FilterFunction;
	typedef std::shared_ptr<FilterFunction>				FilterFunctionPtrS;

	typedef dispersion::DispersionFunction				DispersionFunction;
	typedef std::shared_ptr<DispersionFunction>			DispersionFunctionPtrS;

	typedef association::AssociationMeasure				AssociationMeasure;
	typedef std::shared_ptr<AssociationMeasure>			AssociationMeasurePtrS;
	typedef association::AssociationFunction			AssociationFunction;
	typedef std::shared_ptr<AssociationFunction>		AssociationFunctionPtrS;
	typedef association::VectorAssociationMeasure		VectorAssociationMeasure;
	typedef std::shared_ptr<VectorAssociationMeasure>	VectorAssociationMeasurePtrS;
	typedef machine_learning::Classifier				Classifier;
	typedef std::shared_ptr<Classifier>					ClassifierPtrS;

	typedef score::ScoreFunction						ScoreFunction;
	typedef std::shared_ptr<ScoreFunction>				ScoreFunctionPtrS;

	typedef aggregation::AggregationFunction			AggregationFunction;
	typedef std::shared_ptr<AggregationFunction>		AggregationFunctionPtrS;

	typedef quality::QualityFunction					QualityFunction;
	typedef std::shared_ptr<QualityFunction>			QualityFunctionPtrS;

	typedef association::AbstractRanker					OptimizationFunction;
	typedef std::shared_ptr<OptimizationFunction>		OptimizationFunctionPtrS;

	typedef Function::StringParameter					StringParameter;
	typedef Function::StringParameterMap				StringParameterMap;

	struct ParsedFunctionString
	{
		ParsedFunctionString()													= default;
		ParsedFunctionString(ParsedFunctionString&& 				pParsed) 	= default;
		ParsedFunctionString(ParsedFunctionString const& 			pParsed) 	= default;
		ParsedFunctionString& operator=(ParsedFunctionString&&	 	pParsed) 	= default;
		ParsedFunctionString& operator=(ParsedFunctionString const& pParsed) 	= default;

		~ParsedFunctionString() = default;

		std::string 		name;
		StringParameterMap	parameters;
		StringParameterMap	unnamedParameters;

		std::string reprezentation() const;
	};

public:
	FunctionFactory()												= default;
	FunctionFactory(FunctionFactory&& 					pFactory)	= default;
	FunctionFactory(FunctionFactory const& 				pFactory)	= default;
	FunctionFactory& operator=(FunctionFactory&& 		pFactory)	= default;
	FunctionFactory& operator=(FunctionFactory const& 	pFactory)	= default;

	virtual ~FunctionFactory() = default;


	FilterFunctionPtrS 				createFilterFunction(std::string const& 			pFunctionString) 	const;

	DispersionFunctionPtrS 			createDispersionFunction(std::string const& 		pFunctionString) 	const;

	AssociationFunctionPtrS			createAssociationFunction(std::string const& 		pFunctionString) 	const;
	VectorAssociationMeasurePtrS	createVectorAssociationMeasure(std::string const& 	pMeasureString) 	const;
	ClassifierPtrS					createClassifier(std::string const& 				pClassifierString) 	const;
	AssociationMeasurePtrS			createAssociationMeasure(std::string const&			pMeasureString)		const;

	ScoreFunctionPtrS				createScoreFunction(std::string const& 				pFunctionString) 	const;

	AggregationFunctionPtrS			createAggregationFunction(std::string const& 		pFunctionString) 	const;

	QualityFunctionPtrS 			createQualityFunction(std::string const& 			pFunctionString) 	const;

	OptimizationFunctionPtrS		createOptimizationFunction(std::string const&		pFunctionString)	const;


public:
	FunctionPtrS createFunction(
		std::string const& 		pFunctionString,
		FunctionMapping const&	pValidFunctions) const;

	std::string 			prepareFunctionString(std::string pFunctionString)			const;

	void					parseArgument(
								ParsedFunctionString& 	pParametersPlaceholder,
								std::string const&		pArgumentString,
								size_t					pFirst	= 0,
								size_t					pLast 	= std::string::npos)	const;

	ParsedFunctionString 	parseFunctionString(std::string const& pFunctionString)	 	const;

	bool					isUnnamedParameter(std::string const& pParameterName) 		const;

	void validateParameters(
		FunctionPtrS const&	pFunction,
		StringParameterMap& pParsedFunctionString) const;
};


}
