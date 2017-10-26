
#include <fstream>

#include "File.h"
#include "../structure/io/StreamingFileReader.h"


namespace utils
{


void loadLinesFromFile(
	std::string const&			pFilePath,
	std::vector<std::string>& 	pLines)
{
	structure::io::StreamingFileReader reader(pFilePath);

	pLines.clear();
	std::string line;
	while (reader.readline(line))
	{
		if (line.size() != 0)
		{
			pLines.push_back(line);
		}
	}
}


}
