#define BOOST_TEST_MODULE measures_test
#define BOOST_TEST_DYN_LINK

#include <unordered_set>

#include "../utils/Textual.h"
#include "../structure/io/RelevantTupleSetLoader.h"
#include "../structure/storage/RelevantTuple.h"
#include "../structure/storage/ContingencyTable.h"
#include "../structure/io/DecodedTupleStorageIO.h"
#include "../structure/storage/TupleFeatureStorage.h"
#include "../structure/builder/CorporaParser.h"
#include "../structure/builder/ContingencyTableGeneratorBuilder.h"

#include "../function/FunctionFactory.h"
#include "../function/association/AverageBigram.h"
#include "../function/association/Frequency.h"
#include "../function/association/Jaccard.h"
#include "../function/association/PearsonsChiSquare.h"
#include "../function/association/OddsRatio.h"
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
	template<typename T>
	using shPtr_vec = std::vector<std::shared_ptr<T>>;


	static Fixture* instance(){if(!inst) inst = new Fixture; return inst;}
	shPtr_vec<ContingencyTableGenerator> getContTableGen() const {return contTableGen;}
	shPtr_vec<MatrixTupleStorage> getMatrixTupleStorage() const {return matrixTupleStorage;}
private:
	shPtr_vec<ContingencyTableGenerator> contTableGen;
	shPtr_vec<MatrixTupleStorage> matrixTupleStorage;
	Fixture()
	{
		inst=this;
		auto const& tagset = Corpus2::get_named_tagset("nkjp");
		auto wcclOperators = WcclOperatorLoader<Wccl::Bool>().
			loadOperators(tagset, "/home/igor/MeWeX/mwextractor/data/test_data/2r.ccl", "");

		std::vector<std::vector<std::string>> corporas
			{{"/home/igor/MeWeX/mwextractor/data/test_data/0.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/1.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/2.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/3.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/4.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/5.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/1.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/2.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/1.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/2.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/3.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/4.ccl"}};
		
	
		for(auto corpora : corporas)
		{
			matrixTupleStorage.push_back(
				CorporaParser().parse(corpora, wcclOperators, tagset, "ccl")
			);
			
			contTableGen.push_back(
				ContingencyTableGeneratorBuilder().build(
				matrixTupleStorage.back(),
				matrixTupleStorage.back()->retrieveTupleIdVector()
			));
		}
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
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;

	double results[8][2] = {
		{1,0},
		{1,0},
		{2,0},
		{1,1},
		{1,1},
		{1,1},
		{3,0},
		{5,2}
	};

	std::cout << Frequency().usage() << std::endl;
	for(auto matrix : matrices)
	{
		int j = 0;
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			BOOST_CHECK_EQUAL( Frequency().rankUsingTable(tuple, table), results[i][j++]);
			// std::cout << Frequency().rankUsingTable(tuple, table) << " : \t";
			// std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
		}
	}
}

BOOST_AUTO_TEST_CASE( Jaccard_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;

	double results[8][2] = {
		{1.0/3.0,0},
		{1.0/3.0,0},
		{1.0/3.0,0},
		{1.0/3.0,1.0/3.0},
		{1.0/3.0,1.0/3.0},
		{1.0/4.0,1.0/4.0},
		{1.0/3.0,1.0/3.0},
		{1.0/3.0,1.0/3.0}
	};

	std::cout << Jaccard().usage() << std::endl;
	for(auto matrix : matrices)
	{
		int j = 0;
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			BOOST_CHECK_EQUAL( Jaccard().rankUsingTable(tuple, table), results[i][j++]);
		}
	}
}

BOOST_AUTO_TEST_CASE( Cout_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;

	std::cout << "Manual Debug" << std::endl;
	for(auto matrix : matrices)
	{
		int j = 0;
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
			std::cout << "  " << Frequency().rankUsingTable(tuple, table) <<
			"\t" << table.createReprezentation() << std::endl;
		}
		std::cout << "\n--------------------Matrix--------------------" << std::endl;
	}
}
/*
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

BOOST_AUTO_TEST_CASE( PearsonsChiSquare_test )
{
	FixtureWrapper fix;
	auto matrix = fix.instance->getMatrixTupleStorage();
	auto tableGen = fix.instance->getContTableGen();
	
	std::cout << PearsonsChiSquare().usage() << std::endl;
	for(auto tuple : matrix->retrieveTupleIdVector())
	{
		auto table = tableGen->createTable(matrix->findTuple(tuple));
		std::cout << PearsonsChiSquare().rankUsingTable(tuple, table) << " <<>> ";
		std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
	}
}

BOOST_AUTO_TEST_CASE( OddsRatio_test )
{
	FixtureWrapper fix;
	auto matrix = fix.instance->getMatrixTupleStorage();
	auto tableGen = fix.instance->getContTableGen();
	
	std::cout << OddsRatio().usage() << std::endl;
	for(auto tuple : matrix->retrieveTupleIdVector())
	{
		auto table = tableGen->createTable(matrix->findTuple(tuple));
		std::cout << OddsRatio().rankUsingTable(tuple, table) << " <<>> ";
		std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
	}
}*/

BOOST_AUTO_TEST_SUITE_END()