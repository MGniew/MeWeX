/**
\mainpage Strona główna projektu MWeXtractor

MWeXtractor to biblioteka programistyczna oraz zestaw narzędzi
i skryptów przeznaczonych do ekstrakcji wyrażeń wielowyrazowych
z tekstów, a także badań nad metodami wydobywania kolokacji.
*/
#define BOOST_TEST_MODULE measures_test
#define BOOST_TEST_DYN_LINK

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


BOOST_AUTO_TEST_CASE( Jaccard_test )
{
	Jaccard jaccard;

	std::cout << jaccard.usage() << std::endl;
	
	std::string cs0("");                                                 // 1 //
	BOOST_CHECK_EQUAL( cs0.length(), (size_t)0 );
	BOOST_CHECK( cs0.empty() );
}

BOOST_AUTO_TEST_CASE( ConsonniT1_test )
{
	std::cout << "ConsonniT1" << std::endl;
	std::string cs0("");                                                 // 1 //
	BOOST_CHECK_EQUAL( cs0.length(), (size_t)0 );
	BOOST_CHECK( cs0.empty() );
}