#define BOOST_TEST_MODULE measures_test
#define BOOST_TEST_DYN_LINK

#include <unordered_set>
#include <string>
#include <iostream>

#include "../structure/storage/ContingencyTable.h"
#include "../structure/builder/CorporaParser.h"
#include "../structure/builder/ContingencyTableGeneratorBuilder.h"
#include "../structure/builder/ContingencyTableStorageBuilder.h"
#include "../function/association/RankerData.h"
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
	shPtr_vec<ContingencyTableSource> getContTable() const {return contTableSrc;}
	shPtr_vec<RankerData> getRankerData() const {return rankerData;}
	shPtr_vec<MatrixTupleStorage> getMatrixTupleStorage() const {return matrixTupleStorage;}
private:
	shPtr_vec<ContingencyTableSource> contTableSrc;
	shPtr_vec<MatrixTupleStorage> matrixTupleStorage;
	shPtr_vec<RankerData> rankerData;
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
			{"/home/igor/MeWeX/mwextractor/data/test_data/6.ccl"},
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
			
			// contTableSrc.push_back(
			// 	ContingencyTableGeneratorBuilder().build(
			// 	matrixTupleStorage.back(),
			// 	matrixTupleStorage.back()->retrieveTupleIdVector(),
			// 	ContingencyTableGenerator::TableCreationPolicy::JOIN_NONE
			// ));

			contTableSrc.push_back(
				ContingencyTableStorageBuilder().build(
				matrixTupleStorage.back(),
				ContingencyTableGeneratorBuilder().build(
					matrixTupleStorage.back(),
					matrixTupleStorage.back()->retrieveTupleIdVector(),
					ContingencyTableGenerator::TableCreationPolicy::JOIN_NONE),
				matrixTupleStorage.back()->retrieveTupleIdVector()
			));

			rankerData.push_back(
				std::make_shared<RankerData>( RankerData(
					matrixTupleStorage.back(),
					contTableSrc.back()
			)));
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
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 1),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 1),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 3),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 1),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3)});

	std::cout << Frequency().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
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
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.5),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.25),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.25)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.83333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.14285),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0)});

	std::cout << Jaccard().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
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
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.92078),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.92078),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.71241),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.71241)});
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
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
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
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.64379),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.64379),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.28758),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.28758)});
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
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
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
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 3.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.5),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 4.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 4.0)});
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
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = InversedExpectedFrequency().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}
/*
BOOST_AUTO_TEST_CASE( Dice_test ) // TODO
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 3.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 4.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 5.0)});
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
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = Dice().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}
*/
BOOST_AUTO_TEST_CASE( ExpectedFrequency_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.33333),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.25),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.25)});
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
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
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
	auto tableSources = fix.instance->getContTable();
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
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -4.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", -4.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", -11.01955),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", -5.50977),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -5.50977)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", -3.80026),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", -3.80026),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -11.01955),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", -4.78071),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", -4.78071)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", -41.97733),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", -2.63523),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", -6.39450),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -18.52774),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", -0.06954),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", -20.98867)});

	std::cout << LogLikelihood().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = LogLikelihood().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( TScore_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -NAN)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.81650),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.81650),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.08866)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.86603),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.08253)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.70711),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.70711)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.08866),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.81650),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.81650)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.73029),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.73029),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.15470),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.82158),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.82158)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.86429),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.74125),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.88950),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.59364),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.14825),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.53530)});

	std::cout << TScore().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = TScore().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( ZScore_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", -NAN)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.22474),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.22474),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 2.71746)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.54919),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.15470),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 3.77964)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.81650),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.81650)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 2.71746),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.22474),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.22474)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 1.18817),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.18817),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.73205),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 1.53226),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.53226)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 7.74997),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.35015),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 2.27945),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.12085),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.15926),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3.00979)});

	std::cout << ZScore().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = ZScore().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( PearsonsChiSquare_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 3.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 10.5)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 4.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 4.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 17.33333)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 2.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 10.5),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 3.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 2.4),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.4),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 6.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 3.59999),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 3.59999)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 69.15152),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 2.43055),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 6.46154),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 10.37037),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.04861),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 14.0)});

	std::cout << PearsonsChiSquare().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = PearsonsChiSquare().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( WChiSquare_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 6.5)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 12.83333)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 6.5),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.33333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.33333)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.53333),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.53333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 1.79999),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.79999)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 55.00866),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 1.24008),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 3.95604),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.42328),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.00496),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 4.57143)});

	std::cout << WChiSquare().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = WChiSquare().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( OddsRatio_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.00000),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.00000),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 2.00000)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 4.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 3.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 2.00000),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.00000),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.00000)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 2.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 8.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.25),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.25)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 33.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 2.75),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 6.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 20.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.58333),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 33.0)});

	std::cout << OddsRatio().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = OddsRatio().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( UnigramSubtuples_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.00000),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.00000),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 2.00000)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 3.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 4.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 3.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 2.00000),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.00000),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.00000)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 2.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 2.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 8.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.25),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.25)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 33.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 2.75),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 6.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 20.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.58333),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 33.0)});

	std::cout << UnigramSubtuples().usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			auto rank = UnigramSubtuples().rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( Sorgenfrei_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	auto rankers = fix.instance->getRankerData();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty",1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies",1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty",1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies",1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies",1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty",1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies",1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty",1.0),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy",1.0)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.5)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.0),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.5),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.0),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.125),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.125)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.03704),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.25),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.5),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.83333),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.08333),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.0)});

	Sorgenfrei fun;
	std::cout << fun.usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		fun.initialize(rankers[i]);
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			double rank = fun.rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( WOrder_test )
{
	WOrder fun;
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	auto rankers = fix.instance->getRankerData();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.6),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.6),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.57142),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.54545),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.57142)});

	std::cout << fun.usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		fun.initialize(rankers[i]);
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			double rank = fun.rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}

BOOST_AUTO_TEST_CASE( WTFOrder_test )
{
	WTFOrder fun;
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	auto rankers = fix.instance->getRankerData();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.2),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.2),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.71428),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.72727),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.71428)});

	std::cout << fun.usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		fun.initialize(rankers[i]);
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			double rank = fun.rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}
/*
BOOST_AUTO_TEST_CASE( WTFOrder_test )
{
	WTFOrder fun;
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	auto rankers = fix.instance->getRankerData();
	int i = -1;
	
	std::vector<Tmap> results;
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.2),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AllSubstSubst	2	subst:ogon	subst:kot", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 1.2),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:kot", 0.66666),
			Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 0.66666)});
	results.push_back(
		Tmap{Tpair("1	AdjSubstSubst	3	adj:włochaty	subst:ogon	subst:pies", 1.71428),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:szary", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:kot	adj:kulawy", 0.66666),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:włochaty", 2.72727),
			Tpair("1	AgrSubstAdj	2	subst:ogon	adj:szary", 0.66666),
			Tpair("1	AllSubstSubst	2	subst:ogon	subst:pies", 1.71428)});

	std::cout << fun.usage() << std::endl;
	for(auto matrix : matrices)
	{
		auto tableSrc = tableSources[++i];
		fun.initialize(rankers[i]);
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::string repr(matrix->createTupleReprezentation(matrix->findTuple(tuple)));
			double rank = fun.rankUsingTable(tuple, table);
			BOOST_CHECK_CLOSE( rank, results[i].find(repr)->second, 0.01);
		}
	}
}*/
/*
BOOST_AUTO_TEST_CASE( Cout_test )
{
	FixtureWrapper fix;
	auto matrices = fix.instance->getMatrixTupleStorage();
	auto tableSources = fix.instance->getContTable();
	int i = -1;

	std::cout << "Manual Debug" << std::endl;
	for(auto matrix : matrices)
	{
		int j = 0;
		auto tableSrc = tableSources[++i];
		for(auto tuple : matrix->retrieveTupleIdVector())
		{
			auto table = tableSrc->constructTable(matrix->findTuple(tuple), matrix);
			std::cout << matrix->createTupleReprezentation(matrix->findTuple(tuple)) << std::endl;
			std::cout << "  " << Frequency().rankUsingTable(tuple, table) <<
			"\t" << table.createReprezentation() <<// std::endl;
			"\t" << table.gatherObservedBigramData(1).createReprezentation() << std::endl;
		}
		std::cout << "\n--------------------Matrix--------------------\n" << std::endl;
	}
}
//*/

BOOST_AUTO_TEST_SUITE_END()