
#include <fstream>

#include "../../utils/Textual.h"
#include "StreamingFileReader.h"
#include "KBestTupleListIO.h"


namespace structure
{
	namespace io
	{


void KBestTupleListIO::write(
	KBestTupleList const&	pKBest,
	TupleStorage const&		pStorage,
	std::string const&		pFilePath) const
{
	writeSome(pKBest, pStorage, pFilePath, pKBest.size());
}


void KBestTupleListIO::writeSome(
	KBestTupleList const&	pKBest,
	TupleStorage const& 	pStorage,
	std::string const&		pFilePath,
	size_t					pCount) const
{
	size_t trueSize = std::min(pCount, pKBest.size());

	std::fstream file(pFilePath, std::ios_base::out);
	EXCEPTION(file.is_open(), "KBestTupleListIO::write(): cannot open a file '" << pFilePath << "'.");

	utils::setStreamMaxDoublePrecision(file);

	file << pKBest.getDescription() << '\n';
	file << trueSize;
	for (size_t i = 0; i < trueSize; ++i)
	{
		file << '\n' << pKBest[i].score << '\t' << pStorage.createTupleReprezentation(pKBest[i].element);
	}

	file.close();
}


auto KBestTupleListIO::read(
	TupleStorage const& pStorage,
	std::string const&	pFile,
	size_t				pMaxLines) const -> KBestTupleList
{
	StreamingFileReader reader(pFile);

	KBestTupleList 				kbest;
	std::string					line;
	std::vector<std::string>	parts;
	size_t 						curLine = 0;

	reader.readline(kbest.getDescription());
	reader.readline(line);
	kbest.getData().resize(std::min(pMaxLines, utils::toSizeT(line)));

	while(reader.readline(line) && (curLine < pMaxLines))
	{
		size_t split = line.find_first_of('\t');
		kbest[curLine].element 	= pStorage.parseTupleReprezentation(line.substr(split + 1));
		kbest[curLine].score 	= utils::toDouble(line.substr(0, split));
		++curLine;
	}

	return kbest;
}


	}
}
