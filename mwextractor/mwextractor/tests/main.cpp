#define BOOST_TEST_MODULE measures_test
#define BOOST_TEST_DYN_LINK

#include <unordered_set>
#include <string>
#include <iostream>

#include "../structure/storage/ContingencyTable.h"
#include "../structure/builder/CorporaParser.h"
#include "../structure/builder/ContingencyTableGeneratorBuilder.h"
#include "../exception/Exception.h"
#include "../utils/File.h"

#include <boost/test/unit_test.hpp>

#include "../function/association/AverageBigram.h"
#include "../function/association/ConsonniT1.h"
#include "../function/association/ConsonniT2.h"
#include "../function/association/Dice.h"
#include "../function/association/ExpectedFrequency.h"
#include "../function/association/FairDispersionPointNormalization.h"
#include "../function/association/Frequency.h"
#include "../function/association/InversedExpectedFrequency.h"
#include "../function/association/Jaccard.h"
#include "../function/association/LogLikelihood.h"
#include "../function/association/MinimalBigram.h"
#include "../function/association/MutualExpectation.h"
#include "../function/association/OddsRatio.h"
#include "../function/association/PearsonsChiSquare.h"
#include "../function/association/SmoothedBigram.h"
#include "../function/association/Sorgenfrei.h"
#include "../function/association/SpecificCorrelation.h"
#include "../function/association/SpecificExponentialCorrelation.h"
#include "../function/association/SpecificFrequencyBiasedMutualDependency.h"
#include "../function/association/TScore.h"
#include "../function/association/UnigramSubtuples.h"
#include "../function/association/WChiSquare.h"
#include "../function/association/WOrder.h"
#include "../function/association/WSpecificCorrelation.h"
#include "../function/association/WSpecificExponentialCorrelation.h"
#include "../function/association/WTFOrder.h"
#include "../function/association/ZScore.h"

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
			loadOperators(tagset, "/home/igor/MeWeX/mwextractor/data/test_data/wccl.ccl", "");

		std::vector<std::vector<std::string>> corporas
			{{"/home/igor/MeWeX/mwextractor/data/test_data/0.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/1.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/2.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/3.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/4.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/5.ccl"},
			{"/home/igor/MeWeX/mwextractor/data/test_data/1.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/2.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/3.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/4.ccl",
			"/home/igor/MeWeX/mwextractor/data/test_data/5.ccl"}};
		
	
		for(auto corpora : corporas)
		{
			matrixTupleStorage.push_back(
				CorporaParser().parse(corpora, wcclOperators, tagset, "ccl")
			);
			
			contTableGen.push_back(
				ContingencyTableGeneratorBuilder().build(
				matrixTupleStorage.back(),
				matrixTupleStorage.back()->retrieveTupleIdVector(),
				ContingencyTableGenerator::TableCreationPolicy::JOIN_NONE
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
typedef std::map<std::string, double> Tmap;
typedef std::pair<std::string, double> Tpair;

BOOST_AUTO_TEST_CASE( Frequency_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;

	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 3),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1)});

	std::cout << Frequency().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			BOOST_CHECK_EQUAL( Frequency().rankUsingTable(tuple, table), results[i].find(repr)->second);
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

	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.5)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.83333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.14285),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5)});

	std::cout << Jaccard().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = Jaccard().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( ConsonniT1_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.63092),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.63092)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.94715),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.97452),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.97452),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.81136),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0)});

	std::cout << ConsonniT1().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = ConsonniT1().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( ConsonniT2_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.36907),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.36907)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.59431),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.74404),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.74404),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.28143),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0)});

	std::cout << ConsonniT2().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = ConsonniT2().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( InversedExpectedFrequency_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0/1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0/0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0/0.33333),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0/0.11111)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0/0.25),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0/1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0/0.0625)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0/0.5),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0/0.5)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0/1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0/1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0/0.11111),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0/0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0/0.33333)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0/0.13775),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0/0.28571),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0/0.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0/2.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0/0.85714),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0/0.64285)});

	std::cout << InversedExpectedFrequency().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = InversedExpectedFrequency().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( Dice_test ) // TODO
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.36907)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0)});

	std::cout << Dice().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = Dice().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}


BOOST_AUTO_TEST_CASE( ExpectedFrequency_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.25),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.0625)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.13775),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.28571),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.85714),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.64285)});

	std::cout << ExpectedFrequency().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = ExpectedFrequency().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( LogLikelihood_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", -5.50977),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -5.50977),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", -11.01955)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", -6.49022),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -8.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", -12.98044)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0)});

	std::cout << LogLikelihood().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = LogLikelihood().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}
/*
BOOST_AUTO_TEST_CASE( MutualExpectation_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.25),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.0625)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.13775),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.28571),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.85714),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.64285)});

	std::cout << MutualExpectation().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = MutualExpectation().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( OddsRatio_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.25),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.0625)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.13775),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.28571),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.85714),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.64285)});

	std::cout << OddsRatio().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = OddsRatio().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( PearsonsChiSquare_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableGenerators = fix.instance->getContTableGen();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.25),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.0625)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.11111),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.13775),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.28571),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.14285),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.85714),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.64285)});

	std::cout << PearsonsChiSquare().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableGen = tableGenerators[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableGen->createTable(matrix->findTuple(tuple));
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = PearsonsChiSquare().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}
*/


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
		std::cout << "\n--------------------Matrix--------------------\n" << std::endl;
	}
}
//*/

BOOST_AUTO_TEST_SUITE_END()