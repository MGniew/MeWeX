/*
 * TuplesManagerWriter.h
 *
 *  Created on: 22-05-2014
 *      Author: michalw
 */

#pragma once

#include <memory>

#include "../storage/MatrixTupleStorage.h"


namespace structure
{
	namespace io
	{


class AbstractTupleStorageIO
{
public:
	typedef storage::MatrixTupleStorage		TupleStorage;
	typedef std::shared_ptr<TupleStorage>	TupleStoragePtrS;

public:
	static std::string getWordsFilename();
	static std::string getRelationsFilename();
	static std::string getTuplesFilename();
	static std::string getCorporasFilename();
	static std::string getPartsOfSpeechFilename();

public:
	AbstractTupleStorageIO() 																	= default;
	AbstractTupleStorageIO(AbstractTupleStorageIO&& 				pAbstractTupleStorageIO) 	= default;
	AbstractTupleStorageIO(AbstractTupleStorageIO const&			pAbstractTupleStorageIO) 	= default;
	AbstractTupleStorageIO& operator=(AbstractTupleStorageIO&&		pAbstractTupleStorageIO) 	= default;
	AbstractTupleStorageIO& operator=(AbstractTupleStorageIO const& pAbstractTupleStorageIO) 	= default;

	virtual ~AbstractTupleStorageIO() = default;


	virtual TupleStoragePtrS read(std::string const& pDir) const;

	virtual void write(
		std::string const&	pDir,
		TupleStorage const& pStorage) const;

protected:
	virtual void readCorporas(
			std::string const& 	pCorporasFile,
			TupleStorage&		pStorage) const = 0;

	virtual void readPartsOfSpeech(
			std::string const& 	pPartsOfSpeechFile,
			TupleStorage&		pStorage) const = 0;

	virtual void readWords(
			std::string const& 	pWordsFile,
			TupleStorage&		pStorage) const = 0;

	virtual void readRelations(
			std::string const& 	pRelationsFile,
			TupleStorage&		pStorage) const = 0;

	virtual void readTuples(
			std::string const& 	pTuplesFile,
			TupleStorage&		pStorage) const = 0;


	virtual void writeCorporas(
			std::string const& 	pCorporasFile,
			TupleStorage const&	pStorage) const = 0;

	virtual void writePartsOfSpeech(
			std::string const& 	pPartsOfSpeechFile,
			TupleStorage const&	pStorage) const = 0;

	virtual void writeWords(
			std::string const& 	pWordsFile,
			TupleStorage const&	pStorage) const = 0;

	virtual void writeRelations(
			std::string const& 	pRelationsFile,
			TupleStorage const&	pStorage) const = 0;

	virtual void writeTuples(
			std::string const& 	pTuplesFile,
			TupleStorage const&	pStorage) const = 0;
};


	}
}
