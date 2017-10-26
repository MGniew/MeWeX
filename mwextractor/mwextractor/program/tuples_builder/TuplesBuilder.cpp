/*
 * TuplesBuilder.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include <fstream>

#include "../../utils/Debug.h"

#include "TuplesBuilder.h"


namespace program
{
	namespace tuples_builder
	{


void TuplesBuilder::start(Config const& pConfig)
{
	Corpus2::Tagset const& tagset = Corpus2::get_named_tagset(pConfig.tagsetName);

	WcclBoolOperatorDataVector wcclOperators = WcclBoolOperatorLoader().loadOperators(
		tagset,
		pConfig.operatorsFiles,
		"");

	tryToCreateOutputFile(pConfig.outputDirectory + '/' + structure::io::DecodedTupleStorageIO::getWordsFilename());
	tryToCreateOutputFile(pConfig.outputDirectory + '/' + structure::io::DecodedTupleStorageIO::getRelationsFilename());
	tryToCreateOutputFile(pConfig.outputDirectory + '/' + structure::io::DecodedTupleStorageIO::getTuplesFilename());

	TupleStoragePtrS storage = CorporaParser().parse(
		pConfig.corporas,
		wcclOperators,
		tagset,
		pConfig.corpusReaderName);

	std::cerr << "Writing..." << std::endl;
	structure::io::DecodedTupleStorageIO().write(
		pConfig.outputDirectory,
		*storage);
}


void TuplesBuilder::getOutputFile(
	std::string const& 	pFilePath,
	std::fstream&		pFile) const
{
	pFile.open(
		pFilePath.c_str(),
		std::ios_base::out);
	EXCEPTION(pFile.is_open(), "Cannot create or open output file '" << pFilePath << "'.");
}


void TuplesBuilder::tryToCreateOutputFile(std::string const& pFilePath) const
{
	std::fstream file;
	getOutputFile(pFilePath, file);
	file.close();
}


	}
}
