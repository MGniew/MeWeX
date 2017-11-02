
#define BOOST_TEST_MODULE measures_test

// #define BOOST_TEST_NO_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <unordered_set>

#include "../utils/Textual.h"
#include "../function/FunctionFactory.h"
#include "../structure/io/RelevantTupleSetLoader.h"
#include "../structure/storage/RelevantTuple.h"
#include "../structure/io/DecodedTupleStorageIO.h"
#include "../structure/storage/TupleFeatureStorage.h"

#include "../function/association/AverageBigram.h"
#include "../function/association/Jaccard.h"
#include "../function/association/ConsonniT1.h"
#include "../function/association/ConsonniT2.h"

#include "../exception/Exception.h"

#include <algorithm>
#include <string>
#include <iostream>

#include <boost/test/unit_test.hpp>


using namespace function::association;


struct Fixture
{
	static Fixture* instance(){if(!inst)inst = new Fixture;return inst;}
	int x;
private:
	Fixture(){inst=this;x=5;}
	static Fixture *inst;
};
Fixture* Fixture::inst = nullptr;


struct FixtureWrapper
{
	Fixture* instance;
	FixtureWrapper(){instance = Fixture::instance();};
};


BOOST_AUTO_TEST_SUITE(Master)
BOOST_GLOBAL_FIXTURE(FixtureWrapper)


BOOST_AUTO_TEST_CASE( Jaccard_test )
{
	FixtureWrapper fix;
	std::cout << fix.instance->x << std::endl;
	
	
	Jaccard jaccard;
	// std::cout << jaccard.usage() << std::endl;
	std::string cs0("");                                                 // 1 //
	BOOST_CHECK_EQUAL( cs0.length(), (size_t)0 );
	BOOST_CHECK( cs0.empty() );
}

BOOST_AUTO_TEST_CASE( ConsonniT1_test )
{
	FixtureWrapper fix;
	std::cout << fix.instance->x << std::endl;
	
	std::string cs0("");                                                 // 1 //
	BOOST_CHECK_EQUAL( cs0.length(), (size_t)0 );
	BOOST_CHECK( cs0.empty() );
}

BOOST_AUTO_TEST_SUITE_END()