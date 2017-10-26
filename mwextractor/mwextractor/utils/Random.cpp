
#include <stdlib.h>

#include "Random.h"


namespace utils
{


uint32 rand8()
{
	return static_cast<uint32>(rand() & 0xFF);
}


uint32 rand16()
{
	return
		(rand8() << 8) |
		(rand8());
}


uint32 rand32()
{
	return
		(rand16() << 16) |
		(rand16());
}


uint64 rand64()
{
	return
		(static_cast<uint64>(rand32()) << 32) |
		(static_cast<uint64>(rand32())		);
}


double randNormalized()
{
	return 
		static_cast<double>(rand32()) / 
		static_cast<double>(RAND_MAX_32);
}


}
