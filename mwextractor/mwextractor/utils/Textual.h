
#pragma once

/**
 * \file Textual.h
 * \brief Funkcje do analizy i działania na tekstach.
 */


#include <vector>
#include <set>
#include <string>

#include "../exception/Exception.h"


namespace utils
{


void split(
	std::string const&			pString,
	std::vector<std::string>&	pOutput,
	char						pDelim);

void split(
	std::string const&		pString,
	std::set<std::string>&	pOutput,
	char					pDelim);


void splitPoints(
	std::string const&		pString,
	std::vector<size_t>&	pOutput,
	char					pDelim);


std::string substring(
	std::string const& 	pString,
	size_t				pBegin,
	size_t				pEnd);


void replaceChar(
	std::string&	pString,
	char			pFrom,
	char			pTo);


void removeCharacters(
	std::string&		pString,
	std::string const&	pCharactersList);
 
void trim(
	std::string&		pString,
	std::string const&	pDelims = "\n\r\t ");


void toLower(
	std::string const& 	pString,
	std::string& 		pOutput);


bool toBool(char pChar);
bool toBool(std::string const& pString);


size_t toSizeT(
	char const* pString,
	char** 		pEndPoint 	= nullptr,
	int 		pBase 		= 10);

size_t toSizeT(
	std::string const& 	pString,
	char** 				pEndPoint 	= nullptr,
	int 				pBase 		= 10);


double toDouble(
	char const* pString,
	char** 		pEndPoint = nullptr);

double toDouble(
	std::string const& 	pString,
	char** 				pEndPoint = nullptr);


void setStreamMaxDoublePrecision(std::ostream& pStream);

std::ostream& printDouble(std::ostream& pStream, double pDouble);


template <char Left, char Right>
size_t findPairedCharacter(
	std::string const& 	pString,
	size_t				pFirst)
{
	size_t left 	= 1;
	size_t right	= 0;
	size_t idx		= pFirst;

	char pair[] = {Left, Right, '\0'};

	while(left != right)
	{
		idx = pString.find_first_of(pair, idx + 1);
		switch(pString[idx])
		{
			case Left:
				++left;
				break;
			case Right:
				++right;
				break;
			default:
				EXCEPTION(false, "utils::findPairedCharacter(): no character pair in string: '"
					<< pString << "', '" << pString.substr(pFirst) << "', starting from " << pFirst
					<< ", L:" << left << ", R:" << right << ", I:" << idx
					<< "LC:" << Left << ", RC:" << Right << ", char:" << pString[idx]);
		}
	}

	return idx;
}


}
