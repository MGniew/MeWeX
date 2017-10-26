
#include "Normalizer.h"

#include "../../utils/Textual.h"
#include "../../utils/Debug.h"

#include "../../function/FunctionFactory.h"

#include "../../structure/io/ContingencyTableStorageIO.h"
#include "../../structure/io/ContingencyTableGeneratorIO.h"
#include "../../structure/io/DecodedTupleStorageIO.h"


namespace program
{
	namespace normalizer
	{


void Normalizer::normalizeInPlace(Config const& pConfig) const
{
	std::cerr << "building function " << pConfig.dispersionFunction << "..." << std::endl;
	function::FunctionFactory::DispersionFunctionPtrS function =
		function::FunctionFactory().createDispersionFunction(pConfig.dispersionFunction);

	std::cerr << "loading storage " << pConfig.inputDirectory << "..." << std::endl;
	TupleStoragePtrS storage = structure::io::DecodedTupleStorageIO().read(pConfig.inputDirectory);

	Disperser::ContingencyTableSourcePtrS tableSource;
	if (!pConfig.contingencyTableGenerator.empty())
	{
		std::cerr << "loading tuple frequency index " << pConfig.contingencyTableGenerator << "..." << std::endl;
		tableSource = structure::io::ContingencyTableGeneratorIO().read(*storage, pConfig.contingencyTableGenerator);
	}
	else if (!pConfig.contingencyTableStorage.empty())
	{
		std::cerr << "loading contingency table " << pConfig.contingencyTableStorage << "..." << std::endl;
		tableSource = structure::io::ContingencyTableStorageIO().read(*storage, pConfig.contingencyTableStorage);
	}

	function->getDispersionData()->setMatrixTupleStorage(storage);
	function->getDispersionData()->setContingencyTableSource(tableSource);

	std::cerr << "Doing dispersion..." << std::endl;
	normalizeTuplesInPlace(storage, function, pConfig.inverseDispersion);

	std::cerr << "writing storage..." << std::endl;
	structure::io::DecodedTupleStorageIO().write(pConfig.outputDirectory, *storage);
}


void Normalizer::normalizeTuplesInPlace(
	TupleStoragePtrS&				pOutputTupleStorage,
	DispersionFunctionPtrS const& 	pDispersionFunction,
	bool							pInverse) const
{
	using namespace function::dispersion;

	std::cerr << "Normalizing tuples..." << std::endl;
	size_t removed = Disperser().dispersTuplesInPlace(pDispersionFunction, pOutputTupleStorage, pInverse, 0.0);

	std::cerr << "Removed " << removed << " tuples." << std::endl;
}


	}
}
