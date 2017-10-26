
#pragma once

/**
 * \file File.h
 * \brief Metody opakowujące funkcje wejścia/wyjścia plików.
 */


#include <fstream>
#include <vector>
#include <string>

#include "../exception/Exception.h"


namespace utils
{


void loadLinesFromFile(
	std::string const&			pFilePath,
	std::vector<std::string>& 	pLines);


template <typename Iterator>
void writeLinesToStream(
	std::ostream& 	pStream,
	Iterator 		pBegin,
	Iterator 		pEnd)
{
	while (pBegin != pEnd)
	{
		pStream << *pBegin << '\n';
		++pBegin;
	}
}


template <typename Iterator>
void writeLinesToFile(
	std::string const& 	pFilePath,
	Iterator 			pBegin,
	Iterator 			pEnd)
{
	std::ofstream file(
		pFilePath.c_str(),
		std::ios_base::out);

	EXCEPTION(file.is_open(), "writeLinesToFile(): Cannot open an output file '" << pFilePath << "'.");

	writeLinesToStream(file, pBegin, pEnd);

	file.close();
}


}
