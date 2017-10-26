
#include <memory>
#include <iostream>
#include <fstream>

#include "../../utils/Time.h"

#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/ContingencyTableGeneratorIO.h"

#include "../../structure/builder/ContingencyTableGeneratorBuilder.h"

#include "../../function/FunctionFactory.h"
#include "../../function/filter/Filtrator.h"

#include "Indexer.h"


namespace program
{
	namespace indexer
	{


void Indexer::create(Config const& pConfig) const
{
	typedef structure::storage::MatrixTupleStorage 	TupleStorage;
	typedef std::shared_ptr<TupleStorage>			TupleStoragePtrS;


	std::cerr << "Loading storage..." << std::endl;
	TupleStoragePtrS storage = structure::io::DecodedTupleStorageIO().read(pConfig.storageDirectory);

	TupleStorage::TupleIdVector tupleIdVector;
	{
		if (!pConfig.filter.empty())
		{
			typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
			typedef function::filter::Filtrator					__Filtrator;

			std::cerr << "Building filter: " << pConfig.filter << std::endl;
			__FilterPtrS filter = function::FunctionFactory().createFilterFunction(pConfig.filter);
			filter->initialize(storage);

			std::cerr << "Filtering using: " << filter->reprezentation() << std::endl;
			tupleIdVector = __Filtrator()(*storage, filter);
		}
		else
		{
			std::cerr << "Will use all tuples..." << std::endl;
			tupleIdVector.reserve(storage->getDistinctTupleCount());
			for (auto iter = storage->beginTuples(); iter != storage->endTuples(); ++iter)
			{
				tupleIdVector.push_back(storage->findTupleId(iter));
			}
		}
	}

	std::cerr << "Building index..." << std::endl;
	utils::Time a;
	auto generator = structure::builder::ContingencyTableGeneratorBuilder().build(storage, tupleIdVector);
	utils::Time b;
	std::cerr << (b - a) << '\n';

	std::cerr << "Writing index..." << std::endl;
	structure::io::ContingencyTableGeneratorIO().write(
		*generator,
		*storage,
		pConfig.storageDirectory + '/' + pConfig.outputFilename);

	std::cerr << "Done" << std::endl;
}


	}
}
