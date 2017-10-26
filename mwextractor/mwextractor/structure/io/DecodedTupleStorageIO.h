
#pragma once


#include "AbstractTupleStorageIO.h"


namespace structure
{
	namespace io
	{


class DecodedTupleStorageIO : public AbstractTupleStorageIO
{
public:
	typedef AbstractTupleStorageIO::TupleStorage TupleStorage;


public:
	DecodedTupleStorageIO() 																= default;
	DecodedTupleStorageIO(DecodedTupleStorageIO&& 					pDecodedTupleStorageIO) = default;
	DecodedTupleStorageIO(DecodedTupleStorageIO const&				pDecodedTupleStorageIO) = delete;
	DecodedTupleStorageIO& operator=(DecodedTupleStorageIO&&	 	pDecodedTupleStorageIO) = default;
	DecodedTupleStorageIO& operator=(DecodedTupleStorageIO const& 	pDecodedTupleStorageIO) = delete;

	virtual ~DecodedTupleStorageIO() = default;


protected:
		virtual void readCorporas(
						std::string const& 	pCorporasFile,
						TupleStorage&		pStorage) 		const override;

		virtual void readPartsOfSpeech(
						std::string const& 	pPartsOfSpeechFile,
						TupleStorage&		pStorage) 		const override;

		virtual void readWords(
						std::string const& 	pWordsFile,
						TupleStorage&		pStorage) 		const override;

		virtual void readRelations(
						std::string const& 	pRelationsFile,
						TupleStorage&		pStorage) 		const override;

		virtual void readTuples(
						std::string const& 	pTuplesFile,
						TupleStorage&		pStorage) 		const override;


		virtual void writeCorporas(
						std::string const& 	pCorporasFile,
						TupleStorage const&	pStorage) 		const override;

		virtual void writePartsOfSpeech(
						std::string const& 	pPartsOfSpeechFile,
						TupleStorage const&	pStorage) 		const override;

		virtual void writeWords(
						std::string const& 	pWordsFile,
						TupleStorage const&	pStorage) 		const override;

		virtual void writeRelations(
						std::string const& 	pRelationsFile,
						TupleStorage const&	pStorage) 		const override;

		virtual void writeTuples(
						std::string const& 	pTuplesFile,
						TupleStorage const&	pStorage) 		const override;
};


	}
}
