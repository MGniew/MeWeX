
#pragma once

/**
 * \file mwextractor/utils/Random.h
 *
 * \brief Funkcje losujące liczby całkowite z pewnego zakresu.
 */


#include "Types.h"


namespace utils
{


#define RAND_MAX_8	0xFF
#define RAND_MAX_16	0xFFFF
#define RAND_MAX_32	0xFFFFFFFF
#define RAND_MAX_64	0xFFFFFFFFFFFFFFFF

uint32 rand8();
uint32 rand16();
uint32 rand32();
uint64 rand64();

double randNormalized();


}
