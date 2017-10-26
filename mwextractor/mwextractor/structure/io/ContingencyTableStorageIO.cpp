
#include <cmath>
#include <fstream>

#include "../../utils/Debug.h"
#include "../../utils/Textual.h"

#include "StreamingFileReader.h"
#include "ContingencyTableStorageIO.h"


namespace structure
{
	namespace io
	{


void ContingencyTableStorageIO::write(
	ContingencyTableStorage const&	pTable,
	TupleStorage const& 			pStorage,
	std::string const&				pFilePath) const
{
	std::fstream file(pFilePath, std::ios_base::out);
	EXCEPTION(file.is_open(), "ContingencyTableStorageIO::write: cannot open output file '" << pFilePath << "'.");
	utils::setStreamMaxDoublePrecision(file);

	for (auto tabIter = pTable.begin(); tabIter != pTable.end(); ++tabIter)
	{
		file << pStorage.createTupleReprezentation(tabIter->first) << '\n';

		for (size_t i = 0; i < tabIter->second.size(); ++i)
		{
			file << '\t' << tabIter->second[i].observed;
		}

		file << '\n';

		for (size_t i = 0; i < tabIter->second.size(); ++i)
		{
			file << '\t' << tabIter->second[i].expected;
		}

		file << '\n';
	}

	file.close();
}


auto ContingencyTableStorageIO::read(
	TupleStorage const& pStorage,
	std::string const&	pFile) const -> ContingencyTableStoragePtrS
{
	typedef storage::ContingencyTable					__CT;
	typedef __CT::ContingencyValue						__CV;
	typedef std::pair<TupleStorage::TupleId, __CT>		__Ins;
	typedef ContingencyTableStorage::ContainerIterator	__CI;

	StreamingFileReader 		reader(pFile);
	ContingencyTableStoragePtrS	map(new ContingencyTableStorage());

	std::string line;
	char* split = 0;
	while(reader.readline(line))
	{
		TupleStorage::TupleId 	tid 	= pStorage.parseTupleReprezentation(line);
		size_t 					power 	= (1 << pStorage.findTuple(tid).size());
		__CI 					current = map->insert(__Ins(tid, __CT(power, __CV(0, 0.0)))).first;

		reader.readline(line);
		split = const_cast<char*>(line.data());
		for (size_t mask = 0; mask < power; ++mask)
		{
			current->second[mask].observed = utils::toDouble(split, &split);
			++split;
		}

		reader.readline(line);
		split = const_cast<char*>(line.data());
		for (size_t mask = 0; mask < power; ++mask)
		{
			current->second[mask].expected = utils::toDouble(split, &split);
			++split;
		}
	}

	return map;
}



	}
}
