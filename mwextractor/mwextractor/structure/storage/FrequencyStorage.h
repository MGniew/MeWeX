
#pragma once

#include "RawFrequencyStorage.h"
#include "CompressedFrequencyStorage.h"


namespace structure
{
	namespace storage
	{

#define SAVE_MEMORY


#ifdef SAVE_MEMORY
// 20% less memory usage with many corporas (20)
// ~11% faster load time
typedef CompressedFrequencyStorage FrequencyStorage;
#else
typedef RawFrequencyStorage FrequencyStorage;
#endif


	}
}
