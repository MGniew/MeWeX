
#define BOOST_TEST_MODULE measures_test

// #define BOOST_TEST_NO_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <unordered_set>

#include "../utils/Textual.h"
#include "../function/FunctionFactory.h"
#include "../structure/io/RelevantTupleSetLoader.h"
#include "../structure/storage/RelevantTuple.h"
#include "../structure/storage/ContingencyTable.h"
#include "../structure/io/DecodedTupleStorageIO.h"
#include "../structure/storage/TupleFeatureStorage.h"
#include "../structure/builder/CorporaParser.h"
#include "../structure/builder/ContingencyTableGeneratorBuilder.h"

#include "../function/association/AverageBigram.h"
#include "../function/association/Frequency.h"
#include "../function/association/Jaccard.h"
#include "../function/association/ConsonniT1.h"
#include "../function/association/ConsonniT2.h"

#include "../exception/Exception.h"

#include "../utils/File.h"

#include <algorithm>
#include <string>
#include <iostream>

#include <boost/test/unit_test.hpp>


using namespace function::association;

using namespace structure::builder;
using namespace structure::storage;

struct Fixture
{
	static Fixture* instance(){if(!inst)inst = new Fixture;return inst;}
	std::shared_ptr<ContingencyTableGenerator> getContTableGen() const {return contTableGen;}
	std::shared_ptr<MatrixTupleStorage> getMatrixTupleStorage() const {return matrixTupleStorage;}
private:
	std::shared_ptr<ContingencyTableGenerator> contTableGen;
	std::shared_ptr<MatrixTupleStorage> matrixTupleStorage;
	Fixture()
	{
		inst=this;
		
		std::vector<std::string> corporas
			// {"/home/igor/MeWeX/mwextractor/data/test_data/medium.ccl",
			// "/home/igor/MeWeX/mwextractor/data/test_data/ala.ccl",
			// "/home/igor/MeWeX/mwextractor/data/test_data/text.ccl",
			// "/home/igor/MeWeX/mwextractor/data/test_data/text.ccl",
			{"/home/igor/MeWeX/mwextractor/data/test_data/ala.ccl"};
	
		auto const& tagset = Corpus2::get_named_tagset("nkjp");
		auto wcclOperators = WcclOperatorLoader<Wccl::Bool>().
			loadOperators(tagset, "/home/igor/MeWeX/mwextractor/data/test_data/2r.ccl", "");
			// loadOperators(tagset, "/home/igor/MeWeX/mwextractor/data/patterns/adam_generalizations/2r.ccl", "");
	
		matrixTupleStorage = CorporaParser().parse(corporas, wcclOperators, tagset, "ccl");
		
		contTableGen = ContingencyTableGeneratorBuilder().build(
			matrixTupleStorage,
			matrixTupleStorage->retrieveTupleIdVector()
		);
	}
	static Fixture *inst;
};
Fixture* Fixture::inst = nullptr;


struct FixtureWrapper
{
	const Fixture* instance;
	FixtureWrapper() : instance(Fixture::instance()){};
};


BOOST_AUTO_TEST_SUITE(Master)
BOOST_GLOBAL_FIXTURE(FixtureWrapper)

BOOST_AUTO_TEST_CASE( Frequency_test )
{
	FixtureWrapper fix;
	auto matrix = fix.instance->getMatrixTupleStorage();
	auto tableGen = fix.instance->getContTableGen();
	
	std::cout << Frequency().usage() << std::endl;
	for(auto tuple : matrix->retrieveTupleIdVector())
	{
		auto table = tableGen->createTable(matrix->findTuple(tuple));
		std::cout << Frequency().rankUsingTable(tuple, table) << " : \t";
		std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
	}
}

BOOST_AUTO_TEST_CASE( Jaccard_test )
{
	FixtureWrapper fix;
	auto matrix = fix.instance->getMatrixTupleStorage();
	auto tableGen = fix.instance->getContTableGen();
	
	std::cout << Jaccard().usage() << std::endl;
	for(auto tuple : matrix->retrieveTupleIdVector())
	{
		auto table = tableGen->createTable(matrix->findTuple(tuple));
		std::cout << Jaccard().rankUsingTable(tuple, table) << " : \t";
		std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
	}
}

BOOST_AUTO_TEST_CASE( ConsonniT1_test )
{
	FixtureWrapper fix;
	auto matrix = fix.instance->getMatrixTupleStorage();
	auto tableGen = fix.instance->getContTableGen();
	
	std::cout << ConsonniT1().usage() << std::endl;
	for(auto tuple : matrix->retrieveTupleIdVector())
	{
		auto table = tableGen->createTable(matrix->findTuple(tuple));
		std::cout << ConsonniT1().rankUsingTable(tuple, table) << " <<>> ";
		std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()