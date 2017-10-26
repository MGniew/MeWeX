
#include "Debug.h"

namespace utils
{


void xassert(
	bool 				pTest,
	std::string const& 	pMessage)
{
	std::cerr << pMessage << std::endl;
	assert(pTest);
}


void xassert(
	bool 				pTest,
	char const* const	pMessage)
{
	std::cerr << pMessage << std::endl;
	assert(pTest);
}


}
