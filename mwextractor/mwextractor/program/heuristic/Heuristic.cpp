
#include <memory>
#include <iostream>
#include <fstream>

#include "../../utils/Time.h"

#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/ContingencyTableGeneratorIO.h"
#include "../../structure/io/ContingencyTableStorageIO.h"
#include "../../structure/io/RelevantTupleSetLoader.h"

#include "../../structure/storage/ContingencyTableSource.h"

#include "../../function/FunctionFactory.h"
#include "../../function/filter/Filtrator.h"

#include "../../machine_learning/heuristic_optimization/LinearCombination.h"

#include "Heuristic.h"


namespace program
{
	namespace heuristic
	{


void Heuristic::run(Config const& pConfig) const
{
	using namespace function;
	using namespace function::association;
	using namespace function::filter;
	using namespace structure::io;
	using namespace structure::storage;

	typedef ContingencyTableStorageIO::TupleStorage::TupleId TupleId;

	auto linearCombination = std::static_pointer_cast<machine_learning::heuristic_optimization::LinearCombination>(
		FunctionFactory().createOptimizationFunction(pConfig.linearCombinationCommand));

	auto storage = DecodedTupleStorageIO().read(pConfig.storageDirectory);
	auto tableSource = pConfig.contingencyTableGenerator.empty() ?
		std::static_pointer_cast<ContingencyTableSource>(ContingencyTableStorageIO().read(*storage, pConfig.contingencyTableStorage)) :
		std::static_pointer_cast<ContingencyTableSource>(ContingencyTableGeneratorIO().read(*storage, pConfig.contingencyTableGenerator));
	auto relevantSet = RelevantTupleSetLoader().loadFromFile(
		pConfig.relevantTupleSetFilepath,
		*storage,
		pConfig.tupleElementsFixedOrder ? RelevantTupleSetLoader::ElementOrder::FIXED : RelevantTupleSetLoader::ElementOrder::FLEXIBLE);

	linearCombination->initialize(std::shared_ptr<RankerData>(new RankerData(storage, tableSource, nullptr, relevantSet)));

	std::vector<TupleId> interested;
	if (pConfig.filter.empty())
	{
		std::vector<TupleId> tids;
		tids.reserve(storage->getDistinctTupleCount());
		for (auto iter = storage->beginTuples(); iter != storage->endTuples(); ++iter)
		{
			tids.push_back(storage->findTupleId(iter));
		}
		interested.swap(tids);
	}
	else
	{
		auto filterFunction = FunctionFactory().createFilterFunction(pConfig.filter);
		filterFunction->initialize(storage);
		interested = Filtrator()(*storage, filterFunction);
	}

	std::cerr << "Optimizing..." << std::endl;
	linearCombination->optimize(interested);

	auto const& results = linearCombination->getLastOptimizationResultMap();

	std::fstream outputFile(pConfig.outputFilename, std::ios_base::out);
	EXCEPTION(outputFile.is_open(), "Heuristic::run(): Cannot open output file.");
	for (auto iter = results.rbegin(); iter != results.rend(); ++iter)
	{
		outputFile << iter->first;
		for (size_t j = 0; j < iter->second.size(); ++j)
		{
			outputFile << ',' << iter->second[j];
		}
		outputFile << std::endl;
	}
	outputFile.close();
}


	}
}
