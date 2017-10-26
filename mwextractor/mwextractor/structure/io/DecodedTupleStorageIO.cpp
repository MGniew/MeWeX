
#include <fstream>

#include "../../utils/Debug.h"
#include "../../utils/Textual.h"

#include "StreamingFileReader.h"
#include "DecodedTupleStorageIO.h"


namespace structure
{
	namespace io
	{


/*
 *	File:
 *	-------------------------
 *	corpora_count
 *	corpora_name \t artifficial_id \t tokens
 *	...
 */
void DecodedTupleStorageIO::readCorporas(
	std::string const& 	pCorporasFile,
	TupleStorage&		pStorage) const
{
	StreamingFileReader reader(pCorporasFile);

	std::string line;
	reader.readline(line);
	size_t corporaCount = utils::toSizeT(line);

	std::vector<std::string> parts;
	while(reader.readline(line))
	{
		utils::split(line, parts, '\t');
		pStorage.addCorpora(TupleStorage::CorporaT(parts[0], utils::toSizeT(parts[1]), utils::toSizeT(parts[2])));
	}

	EXCEPTION(
		corporaCount == pStorage.getCorporaCount(),
		"DecodedTupleStorageIO::readCorporas(): Read corpora count is not equal to declared in header, header = "
			<< corporaCount << ", read = " << pStorage.getCorporaCount() << '.');
}


/*
 *	File:
 *	-------------------------
 *	pos_count
 *	pos_name \t global_frequency \t corpora_0_frequency \t corpora_1_frequency ...
 *	...
 */
void DecodedTupleStorageIO::readPartsOfSpeech(
	std::string const& 	pPartsOfSpeechFile,
	TupleStorage&		pStorage) const
{
	StreamingFileReader reader(pPartsOfSpeechFile);

	std::string line;
	reader.readline(line);
	size_t posesCount = utils::toSizeT(line);

	std::vector<std::string> parts;
	while(reader.readline(line))
	{
		utils::split(line, parts, '\t');
		TupleStorage::PartOfSpeechT pos(parts[0], utils::toDouble(parts[1]), pStorage.getCorporaCount());
		for (size_t c = 0; c < pStorage.getCorporaCount(); ++c)
		{
			pos.getMetadata().setLocalFrequency(c, utils::toSizeT(parts[2 + c]));
		}

		pStorage.addPartOfSpeech(pos);
	}

	EXCEPTION(
		posesCount == pStorage.getPartOfSpeechCount(),
		"DecodedTupleStorageIO::readPartsOfSpeech(): Read parts of speech count is not equal to declared in header, header = "
			<< posesCount << ", read = " << pStorage.getPartOfSpeechCount() << '.');
}


/*
 *	File:
 *	-------------------------
 *	word_count \t token_count
 *	pos_name:word \t global_frequency \t corpora_0_frequency \t corpora_1_frequency ...
 *	...
 */
void DecodedTupleStorageIO::readWords(
	std::string const& 	pWordsFile,
	TupleStorage&		pStorage) const
{
	StreamingFileReader reader(pWordsFile);

	std::string line;
	reader.readline(line);

	std::vector<std::string> parts;
	utils::split(line, parts, '\t');

	size_t wordCount 			= utils::toSizeT(parts[0]);
	double wordGlobalFrequency	= utils::toDouble(parts[1]);

	while(reader.readline(line))
	{
		utils::split(line, parts, '\t');
		size_t split = parts[0].find(':');

		TupleStorage::WordT word = TupleStorage::WordT(
			pStorage.parsePartOfSpeechReprezentation(parts[0].substr(0, split)),
			parts[0].substr(split + 1),
			utils::toDouble(parts[1]),
			pStorage.getCorporaCount());

		for (size_t c = 0; c < pStorage.getCorporaCount(); ++c)
		{
			if (parts[2 + c][0] != '0')
			{
				word.getMetadata().setLocalFrequency(c, utils::toSizeT(parts[2 + c]));
			}
		}

		pStorage.addWord(word);
	}

	EXCEPTION(
		wordCount == pStorage.getWordCount(),
		"DecodedTupleStorageIO::readWords(): Read word count is not equal to declared in header, header = "
			<< wordCount << ", read = " << pStorage.getWordCount() << '.');

	EXCEPTION(
		static_cast<size_t>(wordGlobalFrequency) == static_cast<size_t>(pStorage.getWordGlobalFrequency()),
		"DecodedTupleStorageIO::readWords(): Read global word frequency is not equal to declared in header, header = "
			<< static_cast<size_t>(wordGlobalFrequency) << ", read = " << pStorage.getWordGlobalFrequency() << '.');
}


/*
 *	File:
 *	-------------------------
 *	relation_count
 *	relation_group \t relation_name \t arity \t global_frequency \t corpora_0_frequency \t corpora_1_frequency ...
 *	...
 */
void DecodedTupleStorageIO::readRelations(
	std::string const& 	pRelationsFile,
	TupleStorage&		pStorage) const
{
	StreamingFileReader reader(pRelationsFile);

	std::string line;
	reader.readline(line);
	size_t relationCount = utils::toSizeT(line);

	std::vector<std::string> parts;
	while(reader.readline(line))
	{
		utils::split(line, parts, '\t');
		pStorage.addRelation(TupleStorage::RelationT(
			utils::toSizeT(parts[0]),
			parts[1],
			utils::toSizeT(parts[2]),
			0.0,
			pStorage.getCorporaCount()));
	}

	EXCEPTION(
		relationCount == pStorage.getRelationCount(),
		"DecodedTupleStorageIO::readRelations(): Read relation count is not equal to declared in header, header = "
			<< relationCount << ", read = " << pStorage.getRelationCount() << '.');
}


/*
 *	File:
 *	-------------------------
 *	distinct_tuple_count \t tuple_count
 *	relation_name \t size \t pos:word_0 \t ... \t pos:word_size-1 \t global_frequency \t corpora_0_frequency \t corpora_1_frequency ...
 *	...
 */
void DecodedTupleStorageIO::readTuples(
	std::string const& 	pTuplesFile,
	TupleStorage&		pStorage) const
{
	StreamingFileReader reader(pTuplesFile);

	std::string line;
	reader.readline(line);

	std::vector<std::string> parts;
	utils::split(line, parts, '\t');
	size_t distinctTupleCount 	= utils::toSizeT(parts[0]);
	double tupleGlobalFrequency = utils::toDouble(parts[1]);

	while(reader.readline(line))
	{
		utils::split(line, parts, '\t');
		size_t relationGroup = utils::toSizeT(parts[0]);
		size_t elemsCount = utils::toSizeT(parts[2]);

		TupleStorage::TupleT tuple(
			elemsCount,
			pStorage.findRelationId(TupleStorage::RelationT(relationGroup, parts[1], elemsCount, 0, 0)),
			utils::toDouble(parts[3 + elemsCount]),
			pStorage.getCorporaCount());

		for (size_t i = 0; i < elemsCount; ++i)
		{
			tuple[i] = pStorage.parseWordReprezentation(parts[3 + i]);
		}

		for (size_t c = 0; c < pStorage.getCorporaCount(); ++c)
		{
			size_t idx = 3 + 1 + elemsCount + c;
			if (parts[idx][0] != '0')
			{
				tuple.getMetadata().setLocalFrequency(c, utils::toSizeT(parts[idx]));
			}
		}

		pStorage.addTuple(tuple);
	}

	XASSERT(
		distinctTupleCount == pStorage.getDistinctTupleCount(),
		"DecodedTupleStorageIO::readTuples(): Read distinct tuple count is not equal to declared in header, header = "
			<< distinctTupleCount << ", read = " << pStorage.getDistinctTupleCount() << '.');

	XASSERT(
		static_cast<size_t>(tupleGlobalFrequency) == static_cast<size_t>(pStorage.getTupleGlobalFrequency()),
		"DecodedTupleStorageIO::readTuples(): Read global tuple frequency is not equal to declared in header, header = "
			<< static_cast<size_t>(tupleGlobalFrequency) << ", read = " << pStorage.getTupleGlobalFrequency() << '.');
}


void DecodedTupleStorageIO::writePartsOfSpeech(
	std::string const& 	pPartsOfSpeechFile,
	TupleStorage const&	pStorage) const
{
	std::fstream file(pPartsOfSpeechFile.c_str(), std::ios_base::out);
	utils::setStreamMaxDoublePrecision(file);

	file << pStorage.getPartOfSpeechCount();

	for (auto i = pStorage.beginPartsOfSpeech(); i != pStorage.endPartsOfSpeech(); ++i)
	{
		file << '\n' << pStorage.createPartOfSpeechReprezentation(*i) << '\t'
			<< i->getMetadata().getGlobalFrequency() << '\t';
		i->getMetadata().writeFrequenciesReprezentation(file);
	}

	file.close();
}


void DecodedTupleStorageIO::writeCorporas(
	std::string const& 	pCorporasFile,
	TupleStorage const&	pStorage) const
{
	std::fstream file(pCorporasFile.c_str(), std::ios_base::out);
	utils::setStreamMaxDoublePrecision(file);

	file << pStorage.getCorporaCount();

	for (auto i = pStorage.beginCorporas(); i != pStorage.endCorporas(); ++i)
	{
		file << '\n' << pStorage.createCorporaReprezentation(*i) << '\t' << i->getTokenCount();
	}

	file.close();
}


void DecodedTupleStorageIO::writeWords(
	std::string const& 	pWordsFile,
	TupleStorage const&	pStorage) const
{
	std::fstream file(pWordsFile.c_str(), std::ios_base::out);
	utils::setStreamMaxDoublePrecision(file);

	file
		<< pStorage.getWordCount() << '\t'
		<< pStorage.getWordGlobalFrequency();

	for (auto i = pStorage.beginWords(); i != pStorage.endWords(); ++i)
	{
		file << '\n' << pStorage.createWordReprezentation(*i) << '\t'
			<< i->getMetadata().getGlobalFrequency() << '\t';
		i->getMetadata().writeFrequenciesReprezentation(file);
	}

	file.close();
}


void DecodedTupleStorageIO::writeRelations(
	std::string const& 	pRelationsFile,
	TupleStorage const&	pStorage) const
{
	std::fstream file(pRelationsFile.c_str(), std::ios_base::out);
	utils::setStreamMaxDoublePrecision(file);

	file << pStorage.getRelationCount();
	for (auto i = pStorage.beginRelations(); i != pStorage.endRelations(); ++i)
	{
		file << '\n' << pStorage.createRelationReprezentation(*i) << '\t'
			<< i->getMetadata().getGlobalFrequency() << '\t';
		i->getMetadata().writeFrequenciesReprezentation(file);
	}

	file.close();
}


void DecodedTupleStorageIO::writeTuples(
	std::string const& 	pTuplesFile,
	TupleStorage const&	pStorage) const
{
	std::fstream file(pTuplesFile.c_str(), std::ios_base::out);
	utils::setStreamMaxDoublePrecision(file);

	file << pStorage.getDistinctTupleCount() << '\t' << pStorage.getTupleGlobalFrequency();
	for (auto i = pStorage.beginTuples(); i != pStorage.endTuples(); ++i)
	{
		file << '\n' << pStorage.createTupleReprezentation(*i) << '\t'
			<< i->getMetadata().getGlobalFrequency() << '\t';
		i->getMetadata().writeFrequenciesReprezentation(file);
	}

	file.close();
}


	}
}
