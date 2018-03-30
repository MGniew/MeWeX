
#include <fstream>

#include "../../utils/Textual.h"

#include "StreamingFileReader.h"

#include "KBestTupleWithOrthsListIO.h"


namespace structure
{
	namespace io
	{


void KBestTupleWithOrthsListIO::write(
	KBestTupleList const&	pKBest,
	OrthFormMap const&		pOrthMap,
	TupleStorage const&		pStorage,
	std::string const&		pFilePath,
	bool					useWebToolFormat) const
{
	if(useWebToolFormat)
		writeSomeWebTool(pKBest, pOrthMap, pStorage, pFilePath, pKBest.size());
	else
		writeSome(pKBest, pOrthMap, pStorage, pFilePath, pKBest.size());
}


void KBestTupleWithOrthsListIO::writeSomeWebTool(
	KBestTupleList const&	pKBest,
	OrthFormMap const&		pOrthMap,
	TupleStorage const& 	pStorage,
	std::string const&		pFilePath,
	size_t					pCount) const
{
	size_t trueSize = std::min(pCount, pKBest.size());

	std::fstream file(pFilePath, std::ios_base::out);
	EXCEPTION(file.is_open(), "KBestTupleWithOrthsListIO::write(): cannot open a file '" << pFilePath << "'.");

	utils::setStreamMaxDoublePrecision(file);

	file << pKBest.getDescription() << '\n';
	file << trueSize;

	std::vector<OrthForm> temp;
	for (size_t i = 0; i < trueSize; ++i)
	{
		file << '\n'
			<< pKBest[i].score << '\t'
			<< pStorage.createTupleReprezentationWebTool(pKBest[i].element);

		auto const& orthFromMap = pOrthMap.find(pKBest[i].element)->second;
		for (auto iter = orthFromMap.begin(); iter != orthFromMap.end(); ++iter)
		{
			temp.push_back(*iter);
		}

		auto comparator = [](OrthForm const& fs1, OrthForm const& fs2) -> bool { return fs1.frequency > fs2.frequency; };
		std::sort(temp.begin(), temp.end(), comparator);

		file << '\t';

		for (size_t i = 0; i < temp.size(); ++i)
		{
			file << temp[i].frequency << ':' << temp[i].form << " (" << temp[i].tag << "), ";
		}

		temp.clear();
	}

	file.close();
}

void KBestTupleWithOrthsListIO::writeSome(
	KBestTupleList const&	pKBest,
	OrthFormMap const&		pOrthMap,
	TupleStorage const& 	pStorage,
	std::string const&		pFilePath,
	size_t					pCount) const
{
	size_t trueSize = std::min(pCount, pKBest.size());

	std::fstream file(pFilePath, std::ios_base::out);
	EXCEPTION(file.is_open(), "KBestTupleWithOrthsListIO::write(): cannot open a file '" << pFilePath << "'.");

	utils::setStreamMaxDoublePrecision(file);

	file << pKBest.getDescription() << '\n';
	file << trueSize;

	std::vector<OrthForm> temp;
	for (size_t i = 0; i < trueSize; ++i)
	{
		file << '\n'
			<< pKBest[i].score << '\t'
			<< pStorage.createTupleReprezentation(pKBest[i].element);

		auto const& orthFromMap = pOrthMap.find(pKBest[i].element)->second;
		for (auto iter = orthFromMap.begin(); iter != orthFromMap.end(); ++iter)
		{
			temp.push_back(*iter);
		}

		auto comparator = [](OrthForm const& fs1, OrthForm const& fs2) -> bool { return fs1.frequency > fs2.frequency; };
		std::sort(temp.begin(), temp.end(), comparator);

		for (size_t i = 0; i < temp.size(); ++i)
		{
			file << '\t' << temp[i].frequency << ' ' << temp[i].form;
		}

		temp.clear();
	}

	file.close();
}


/*auto KBestTupleWithOrthsListIO::read(
	TupleStorage const& pStorage,
	std::string const&	pFile
	OrthMap&			pOrthMap) const -> KBestTupleList
{
	StreamingFileReader reader(pFile);

	KBestTupleList 				kbest;
	std::string					line;
	std::vector<std::string>	parts;
	size_t 						curLine = 0;

	reader.readline(kbest.getDescription());
	reader.readline(line);
	kbest.getData().resize(utils::toSizeT(line));

	while(reader.readline(line))
	{
		size_t split = line.find_first_of('\t');
		kbest[curLine].element 	= pStorage.parseTupleReprezentation(line.substr(split + 1));
		kbest[curLine].score 	= utils::toDouble(line.substr(0, split));
		++curLine;
	}

	return kbest;
}*/


	}
}
