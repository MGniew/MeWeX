
#include "../../utils/Time.h"

#include "AbstractTupleStorageIO.h"


namespace structure
{
	namespace io
	{


std::string AbstractTupleStorageIO::getWordsFilename()
{
	return "words.csv";
}


std::string AbstractTupleStorageIO::getRelationsFilename()
{
	return "relations.csv";
}


std::string AbstractTupleStorageIO::getTuplesFilename()
{
	return "tuples.csv";
}


std::string AbstractTupleStorageIO::getCorporasFilename()
{
	return "corporas.csv";
}


std::string AbstractTupleStorageIO::getPartsOfSpeechFilename()
{
	return "parts_of_speech.csv";
}


auto AbstractTupleStorageIO::read(std::string const& pDir) const -> TupleStoragePtrS
{
	std::cerr << "Reading storage from: " << pDir << std::endl;
	std::cerr << "Reading corporas" << std::endl;

	TupleStoragePtrS tupleStorage(new TupleStorage());

	readCorporas(
		pDir + '/' + getCorporasFilename(),
		*tupleStorage);
	std::cerr << "Reading poses" << std::endl;
	readPartsOfSpeech(
		pDir + '/' + getPartsOfSpeechFilename(),
		*tupleStorage);
	std::cerr << "Reading words" << std::endl;
	readWords(
		pDir + '/' + getWordsFilename(),
		*tupleStorage);
	std::cerr << "Reading relations" << std::endl;
	readRelations(
		pDir + '/' + getRelationsFilename(),
		*tupleStorage);
	std::cerr << "Reading tuples" << std::endl;
	readTuples(
		pDir + '/' + getTuplesFilename(),
		*tupleStorage);
	std::cerr << "Read" << std::endl;

	return tupleStorage;
}


void AbstractTupleStorageIO::write(
	std::string const&	pDir,
	TupleStorage const& pStorage) const
{
	writeCorporas(
		pDir + '/' + getCorporasFilename(),
		pStorage);
	writePartsOfSpeech(
		pDir + '/' + getPartsOfSpeechFilename(),
		pStorage);
	writeWords(
		pDir + '/' + getWordsFilename(),
		pStorage);
	writeRelations(
		pDir + '/' + getRelationsFilename(),
		pStorage);
	writeTuples(
		pDir + '/' + getTuplesFilename(),
		pStorage);
}


	}
}
