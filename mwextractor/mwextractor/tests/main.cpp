/**
\mainpage Strona główna projektu MWeXtractor

MWeXtractor to biblioteka programistyczna oraz zestaw narzędzi
i skryptów przeznaczonych do ekstrakcji wyrażeń wielowyrazowych
z tekstów, a także badań nad metodami wydobywania kolokacji.
*/

#include <unordered_set>

#include "../utils/Textual.h"
#include "../function/FunctionFactory.h"
#include "../structure/io/RelevantTupleSetLoader.h"
#include "../structure/storage/RelevantTuple.h"
#include "../structure/io/DecodedTupleStorageIO.h"
#include "../structure/storage/TupleFeatureStorage.h"

#include "../function/association/AverageBigram.h"
#include "../function/association/ConsonniT1.h"
#include "../function/association/ConsonniT2.h"
#include "../function/association/VectorAssociationMeasure.h"
#include "../machine_learning/multilayer_perceptron/MultilayerPerceptron.h"
#include "../machine_learning/heuristic_optimization/LinearCombination.h"

#include "../exception/Exception.h"

#include <algorithm>
#include <string>
#include <iostream>

int main()
{
	using namespace function;
	using namespace function::association;
	using namespace machine_learning::multilayer_perceptron;
	using namespace machine_learning::heuristic_optimization;


	std::vector<std::shared_ptr<Function>> functions;
	functions.emplace_back(new AverageBigram());
	functions.emplace_back(new ConsonniT1());
	functions.emplace_back(new ConsonniT2());
	functions.emplace_back(new MultilayerPerceptron());
	functions.emplace_back(new VectorAssociationMeasure());
	functions.emplace_back(new LinearCombination());

	for (size_t i = 0; i < functions.size(); ++i)
	{
		std::cerr << functions[i]->usage() << std::endl << std::endl;
	}

	try
	{
		function::FunctionFactory().createClassifier("mlp()");
	}
	catch(exception::Exception const& e)
	{
		std::cerr << e.getMessage() << std::endl << std::endl;
	}

	try
	{
		function::FunctionFactory().createOptimizationFunction("lc()");
	}
	catch(exception::Exception const& e)
	{
		std::cerr << e.getMessage() << std::endl << std::endl;
	}


	return 0;
}
