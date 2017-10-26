
#include <sstream>

#include "../utils/Debug.h"
#include "../utils/Textual.h"

#include "FunctionFactory.h"


namespace function
{


std::string FunctionFactory::ParsedFunctionString::reprezentation() const
{
	std::stringstream str;
	str << name << "\nNamed parameters:\n";
	for (auto i = parameters.begin(); i != parameters.end(); ++i)
	{
		str << '\t' << i->first << " = " << i->second << '\n';
	}
	str << "UnnamedParameters:\n";
	for (auto i = unnamedParameters.begin(); i != unnamedParameters.end(); ++i)
	{
		str << '\t' << i->first << " = " << i->second << '\n';
	}
	return str.str();
}


// FunctionFactory functions
auto FunctionFactory::createFilterFunction(std::string const& pFunctionString) const -> FilterFunctionPtrS
{
	return std::static_pointer_cast<FilterFunction>(
		createFunction(pFunctionString, FilterFunctionCreators::getMapping()));
}


auto FunctionFactory::createDispersionFunction(std::string const& pFunctionString) const -> DispersionFunctionPtrS
{
	return std::static_pointer_cast<DispersionFunction>(
		createFunction(pFunctionString, DispersionFunctionCreators::getMapping()));
}


auto FunctionFactory::createAssociationFunction(std::string const& pFunctionString) const -> AssociationFunctionPtrS
{
	return std::static_pointer_cast<AssociationFunction>(
		createFunction(pFunctionString, AssociationFunctionCreators::getMapping()));
}


auto FunctionFactory::createVectorAssociationMeasure(std::string const& pMeasureString) const -> VectorAssociationMeasurePtrS
{
	return std::static_pointer_cast<VectorAssociationMeasure>(
		createFunction(pMeasureString, VectorAssociationMeasureCreators::getMapping()));
}


auto FunctionFactory::createClassifier(std::string const& pClassifierString) const -> ClassifierPtrS
{
	return std::static_pointer_cast<Classifier>(
			createFunction(pClassifierString, ClassifierCreators::getMapping()));
}


auto FunctionFactory::createAssociationMeasure(std::string const& pMeasureString) const -> AssociationMeasurePtrS
{
	try
	{
		return std::static_pointer_cast<AssociationMeasure>(
			createFunction(pMeasureString, AssociationFunctionCreators::getMapping()));
	}
	catch(exception::Exception const& pException)
	{
		return std::static_pointer_cast<AssociationMeasure>(
			createFunction(pMeasureString, ClassifierCreators::getMapping()));
	}
}


auto FunctionFactory::createScoreFunction(std::string const& pFunctionString) const -> ScoreFunctionPtrS
{
	return std::static_pointer_cast<ScoreFunction>(
		createFunction(pFunctionString, ScoreFunctionCreators::getMapping()));
}


auto FunctionFactory::createAggregationFunction(std::string const& pFunctionString) const -> AggregationFunctionPtrS
{
	return std::static_pointer_cast<AggregationFunction>(
		createFunction(pFunctionString, AggregationFunctionCreators::getMapping()));
}


auto FunctionFactory::createQualityFunction(std::string const& pFunctionString) const -> QualityFunctionPtrS
{
	return std::static_pointer_cast<QualityFunction>(
		createFunction(pFunctionString, QualityFunctionCreators::getMapping()));
}


auto FunctionFactory::createOptimizationFunction(std::string const& pFunctionString) const -> OptimizationFunctionPtrS
{
	return std::static_pointer_cast<OptimizationFunction>(
		createFunction(pFunctionString, OptimizationFunctionCreators::getMapping()));
}


auto FunctionFactory::createFunction(
	std::string const& 		pFunctionString,
	FunctionMapping const&	pValidFunctions) const -> FunctionPtrS
{
	ParsedFunctionString meta = parseFunctionString(prepareFunctionString(pFunctionString));

	auto iter = pValidFunctions.find(meta.name);
	EXCEPTION(
			iter != pValidFunctions.end(),
			"FunctionFactory::createFunction: Function not recognized '" << meta.name << "'.");

	FunctionPtrS function = iter->second();
	validateParameters(function, meta.parameters);
	function->build(meta.parameters, meta.unnamedParameters);

	return function;
}


std::string FunctionFactory::prepareFunctionString(std::string pFunctionString)	const
{
	utils::removeCharacters(pFunctionString, " ");
	return pFunctionString;
}


void FunctionFactory::parseArgument(
	ParsedFunctionString& 	pParametersPlaceholder,
	std::string const& 		pArgumentString,
	size_t					pFirst,
	size_t					pLast) const
{
	std::string temp 		= utils::substring(pArgumentString, pFirst, pLast);
	size_t 		equalSign 	= temp.find_first_of("(=");

	if (equalSign == std::string::npos || temp[equalSign] == '(')
	{
		pParametersPlaceholder.unnamedParameters.insert(StringParameter(
			std::to_string(pParametersPlaceholder.unnamedParameters.size()),
			temp
		));
	}
	else
	{
		pParametersPlaceholder.parameters.insert(StringParameter(
			utils::substring(temp, 0, equalSign - 1),
			temp.substr(equalSign + 1)
		));
	}
}


auto FunctionFactory::parseFunctionString(std::string const& pFunctionString) const -> ParsedFunctionString
{
	// retrieve function name and prepare args
	size_t 	contextBegin 	= pFunctionString.find_first_of('(') + 1;
	size_t 	contextEnd		= 0;
	bool 	isParam			= false;
	bool	done			= false;
	bool	bracketOpen		= false;

	ParsedFunctionString parsed;
	parsed.name = pFunctionString.substr(0, contextBegin - 1);

	if ((contextBegin == pFunctionString.size() - 1) || (contextBegin == 0))
	{
		return parsed;
	}

	while (!done)
	{
		contextEnd = pFunctionString.find_first_of("(),", contextBegin);

		switch(pFunctionString[contextEnd])
		{
			case '(':
			{
				contextEnd 	= utils::findPairedCharacter<'(', ')'>(pFunctionString, contextEnd);
				isParam 	= true;
				bracketOpen = true;
				break;
			}
			case ',':
			{
				isParam = true;
				--contextEnd;
				break;
			}
			case ')':
			{
				if (!bracketOpen)
				{
					--contextEnd;
					isParam = true;
				}

				done = true;
				break;
			}
		}

		bracketOpen = false;

		if (isParam)
		{
			parseArgument(parsed, pFunctionString, contextBegin, contextEnd);
			contextBegin 	= contextEnd + 2;
			isParam 		= false;
			if (contextBegin >= pFunctionString.size())
			{
				done = true;
			}
		}
	}

	return parsed;
}


bool FunctionFactory::isUnnamedParameter(std::string const& pParameterName) const
{
	return !pParameterName.empty() && (pParameterName.find_first_not_of("0123456789") == std::string::npos);
}


void FunctionFactory::validateParameters(
	FunctionPtrS const&	pFunction,
	StringParameterMap& pParsedFunctionString) const
{
	StringParameterMap functionParameters = pFunction->retrieveFunctionParameters();

	// Check if every parameter passed in string is in set of valid parameters for this function or string parameter is a positional parameter
	for (auto i = pParsedFunctionString.begin(); i != pParsedFunctionString.end(); ++i)
	{
		EXCEPTION(
				functionParameters.find(i->first) != functionParameters.end(),
				"FunctionFactory::validateParameters: '" << i->first
					<< "' is an unknown parameter for function '" << pFunction->name() << "'.\nUsage: " << pFunction->usage());
	}

	// Check if all required parameters was passed in function string and put default values for those which didn't if default value is defined
	for (auto i = functionParameters.begin(); i != functionParameters.end(); ++i)
	{
		if (pParsedFunctionString.find(i->first) == pParsedFunctionString.end())
		{
			EXCEPTION(
					i->second.size() > 0,
					"FunctionFactory::validateParameters: required parameter '" << i->first
						<< "' not set for function '" << pFunction->name() << "'.\nUsage: " << pFunction->usage());

			if (i->second != "none")
			{
				pParsedFunctionString.insert(*i);
			}
			else
			{
				pParsedFunctionString.insert(std::pair<std::string, std::string>(i->first, ""));
			}
		}
	}
}


}
