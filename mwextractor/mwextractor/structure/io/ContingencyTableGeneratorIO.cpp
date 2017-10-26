
#include <cmath>
#include <fstream>

#include "../../utils/Debug.h"
#include "../../utils/Textual.h"

#include "StreamingFileReader.h"
#include "ContingencyTableGeneratorIO.h"


namespace structure
{
	namespace io
	{


void ContingencyTableGeneratorIO::write(
	ContingencyTableGenerator const&	pContingencyTableGenerator,
	TupleStorage const& 				pStorage,
	std::string const&					pFilePath) const
{
	std::fstream file(pFilePath, std::ios_base::out);
	EXCEPTION(file.is_open(), "ContingencyTableGeneratorIO::write(): cannot open output file '" << pFilePath << "'.");
	utils::setStreamMaxDoublePrecision(file);

	file << pStorage.getTupleGlobalFrequency() << '\n';

	for (auto tabIter = pContingencyTableGenerator.begin(); tabIter != pContingencyTableGenerator.end(); ++tabIter)
	{
		file << pStorage.createRelationReprezentation(tabIter->getRelation());

		for (size_t e = 0; e < tabIter->size(); ++e)
		{
			file << '\t' << ((*tabIter)[e] != nullptr ? pStorage.createWordReprezentation((*tabIter)[e]) : "0");
		}

		file << '\t' << tabIter->getMetadata().getGlobalFrequency() << '\n';
	}

	file.close();
}


auto ContingencyTableGeneratorIO::read(
	TupleStorage const& pStorage,
	std::string const&	pFile) const -> ContingencyTableGeneratorPtrS
{
	typedef TupleStorage::RelationId 	RelationId;
	typedef TupleStorage::TupleT 		TupleT;

	StreamingFileReader reader(pFile);

	std::string line;
	reader.readline(line);
	ContingencyTableGeneratorPtrS generator(new ContingencyTableGenerator(utils::toSizeT(line)));

	std::vector<std::string> parts;
	char* split = 0;
	while(reader.readline(line))
	{
		size_t end = line.find_first_of('\t', line.find_first_of('\t', line.find_first_of('\t') + 1) + 1);
		RelationId relId = pStorage.findRelationByReprezentation(line.substr(0, end));

		utils::split(line.substr(end + 1), parts, '\t');

		TupleT tuple(pStorage.findRelation(relId).getArity(), relId, utils::toDouble(*parts.rbegin()), 0);

		for (size_t i = 0; i < parts.size() - 1; ++i)
		{
			if (parts[i] == "0")
			{
				tuple[i] = nullptr;
			}
			else
			{
				tuple[i] = pStorage.parseWordReprezentation(parts[i]);
			}
		}

		generator->insert(tuple);
	}

	return generator;
}



	}
}
