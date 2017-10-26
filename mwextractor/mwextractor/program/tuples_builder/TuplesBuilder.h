/*
 * TuplesBuilder.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "../../structure/builder/CorporaParser.h"
#include "../../structure/io/DecodedTupleStorageIO.h"
#include "Config.h"


namespace program
{
	namespace tuples_builder
	{


class TuplesBuilder
{
public:
	typedef structure::storage::MatrixTupleStorage				TupleStorage;
	typedef std::shared_ptr<TupleStorage>						TupleStoragePtrS;

	typedef structure::builder::WcclOperatorLoader<Wccl::Bool>	WcclBoolOperatorLoader;
	typedef WcclBoolOperatorLoader::WcclOperatorDataVector		WcclBoolOperatorDataVector;

	typedef structure::builder::CorporaParser					CorporaParser;

public:
	void start(Config const& pConfig);

private:
	void getOutputFile(
		std::string const& 	pFilePath,
		std::fstream&		pFile) const;

	void tryToCreateOutputFile(std::string const& pFilePath) const;
};


	}
}
