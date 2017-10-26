/*
 * Normalizer.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include "../../function/dispersion/Disperser.h"
#include "../../structure/io/DecodedTupleStorageIO.h"
#include "Config.h"


namespace program
{
	namespace normalizer
	{


class Normalizer
{
public:
	typedef function::dispersion::Disperser				Disperser;
	typedef function::dispersion::DispersionFunction	DispersionFunction;
	typedef std::shared_ptr<DispersionFunction>			DispersionFunctionPtrS;

	typedef	structure::storage::MatrixTupleStorage		TupleStorage;
	typedef std::shared_ptr<TupleStorage>				TupleStoragePtrS;


public:
	void normalizeInPlace(Config const& pConfig) const;


private:
	void normalizeTuplesInPlace(
		TupleStoragePtrS&				pOutputTupleStorage,
		DispersionFunctionPtrS const& 	pDispersionFunction,
		bool							pInverse) const;
};


	}
}
