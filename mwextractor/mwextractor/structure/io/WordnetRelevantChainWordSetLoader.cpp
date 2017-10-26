
#include <sstream>

#include "../../utils/Textual.h"
#include "StreamingFileReader.h"
#include "WordnetRelevantChainWordSetLoader.h"


namespace structure
{
	namespace io
	{


auto WordnetRelevantChainWordSetLoader::loadFromFile(
	std::string const& 		pFile,
	TupleStorage const&		pTupleStorage,
	TupleIdSet const&		pTupleIdSet) const -> RelevantTupleIdSet
{
	return buildSet(readLines(pFile), pTupleStorage, pTupleIdSet);
}


std::set<std::string> WordnetRelevantChainWordSetLoader::readLines(std::string const& pFile) const
{
	std::set<std::string> lines;

	StreamingFileReader reader(pFile);
	std::string line;
	while (reader.readline(line))
	{
		utils::trim(line);
		lines.insert(line);
	}

	return lines;
}


auto WordnetRelevantChainWordSetLoader::buildSet(
	std::set<std::string> const& 	pLines,
	TupleStorage const& 			pTupleStorage,
	TupleIdSet const&				pTupleIdSet) const -> RelevantTupleIdSet
{
	RelevantTupleIdSet set(pLines.size());

	for (auto iter = pTupleStorage.beginTuples(); iter != pTupleStorage.endTuples(); ++iter)
	{
		if (!pTupleIdSet.empty() && pTupleIdSet.find(pTupleStorage.findTupleId(iter)) == pTupleIdSet.end())
		{
			continue;
		}

		std::stringstream str;
		for (size_t e = 0; e < iter->size(); ++e)
		{
			str << pTupleStorage.findWord(iter->getElement(e)).getContent();
			if (e < iter->size() - 1)
			{
				str << ' ';
			}
		}

		auto res = pLines.find(str.str());
		if (res != pLines.end())
		{
			set.insert(pTupleStorage.findTupleId(iter));
		}
	}

	return set;
}


	}
}
