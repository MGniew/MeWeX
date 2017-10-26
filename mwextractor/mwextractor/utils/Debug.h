
#pragma once

/**
 * \file Debug.h
 * \brief Metody służące do debugowania i asercji.
 */


#include <sstream>
#include <iostream>
#include <cassert>

namespace utils
{


#if defined(NDEBUG)

#define XASSERT(test, msg)

#define DEBUG_MESSAGE(messageStream)

#else

#define XASSERT(test, messageStream) 			\
{												\
	bool __test = (test);						\
	if (!__test)								\
	{											\
		std::stringstream __str;				\
		__str << messageStream;					\
		utils::xassert(__test, __str.str());	\
	}											\
}

#define DEBUG_MESSAGE(messageStream)			\
{												\
	std::cerr << messageStream << std::endl; 	\
}

#endif


void xassert(
	bool 				pTest,
	std::string const& 	pMessage);


void xassert(
	bool 				pTest,
	char const* const	pMessage);


}
