
#include <iostream>
#include <fstream>

#include "../../structure/io/StreamingFileReader.h"
#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/ContingencyTableStorageIO.h"

#include "../../structure/storage/ContingencyTableGenerator.h"

#include "../../structure/builder/ContingencyTableGeneratorBuilder.h"

#include "../../function/FunctionFactory.h"
#include "../../function/filter/Filtrator.h"

#include "Continger.h"


namespace program
{
	namespace continger
	{


void Continger::create(Config const& pConfig) const
{
	typedef structure::io::DecodedTupleStorageIO::TupleStorage		TupleStorage;
	typedef std::shared_ptr<TupleStorage>							TupleStoragePtrS;
	typedef structure::builder::ContingencyTableGeneratorBuilder	ContingencyTableGeneratorBuilder;
	typedef structure::builder::ContingencyTableStorageBuilder		ContingencyTableStorageBuilder;
	typedef structure::storage::ContingencyTableGenerator			ContingencyTableGenerator;

	std::cerr << "Loading storage..." << std::endl;
	TupleStoragePtrS storage = structure::io::DecodedTupleStorageIO().read(pConfig.storageDirectory);

	TupleStorage::TupleIdVector tupleIdVector;
	{
		if (!pConfig.filter.empty())
		{
			typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
			typedef function::filter::Filtrator 				__Filtrator;

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

	// TODO consider policy
	std::cerr << "Building contingency table..." << std::endl;
	std::shared_ptr<ContingencyTableGenerator> generator = ContingencyTableGeneratorBuilder().build(storage, tupleIdVector);
	auto cts = ContingencyTableStorageBuilder().build(storage, generator, tupleIdVector);

	std::cerr << "Writing contingency table..." << std::endl;
	structure::io::ContingencyTableStorageIO().write(
		*cts,
		*storage,
		pConfig.storageDirectory + '/' + pConfig.outputFilename);

	std::cerr << "Done." << std::endl;
}


	}
}
