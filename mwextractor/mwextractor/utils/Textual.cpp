
#include <algorithm>
#include <ostream>

#include "Textual.h"


namespace utils
{


void split(
	std::string const&			pString,
	std::vector<std::string>&	pOutput,
	char						pDelim) 
{
	pOutput.clear();

	size_t pos 		= -1;
	size_t last 	= 0;
	size_t length 	= 0;
	while ((pos = pString.find_first_of(pDelim, last)) != std::string::npos)
	{
		length = pos - last;
		if (length > 0)
		{
			pOutput.emplace_back(pString.data() + last, length);
		}
		else
		{
			pOutput.emplace(pOutput.end());
		}
		last = pos + 1;
	}
	pOutput.emplace_back(pString.data() + last, pString.size() - last);
}


void split(
	std::string const&		pString,
	std::set<std::string>&	pOutput,
	char					pDelim)
{
	pOutput.clear();

	size_t pos 		= -1;
	size_t last 	= 0;
	size_t length 	= 0;
	while ((pos = pString.find_first_of(pDelim, last)) != std::string::npos)
	{
		length = pos - last;
		if (length > 0)
		{
			pOutput.emplace(pString.data() + last, length);
		}
		else
		{
			pOutput.emplace();
		}
		last = pos + 1;
	}
	pOutput.emplace(pString.data() + last, pString.size() - last);
}


void splitPoints(
	std::string const&		pString,
	std::vector<size_t>&	pOutput,
	char					pDelim)
{
	pOutput.clear();

	size_t pos 		= -1;
	size_t last 	= 0;
	while ((pos = pString.find_first_of(pDelim, last)) != std::string::npos)
	{
		pOutput.push_back(pos);
		last = pos + 1;
	}
}


std::string substring(
	std::string const& 	pString,
	size_t				pBegin,
	size_t				pEnd)
{
	return pString.substr(pBegin, pEnd - pBegin + 1);
}


void replaceChar(
	std::string&	pString,
	char			pFrom,
	char			pTo)
{
	for (size_t i = 0; i < pString.size(); ++i)
	{
		if (pString[i] == pFrom)
		{
			pString[i] = pTo;
		}
	}
}


void removeCharacters(
	std::string&		pString,
	std::string const&	pCharactersList)
{
	size_t last = pString.size() - 1;

	while (true)
	{
		last = pString.find_last_of(pCharactersList, last);
		if (last == std::string::npos)
		{
			break;
		}
		pString.erase(last, 1);
		--last;
	}
}


void trim(
	std::string&		pString,
	std::string const&	pDelims)
{
	size_t f = pString.find_first_not_of(pDelims);
	if (f != std::string::npos)
	{
		size_t l = pString.find_last_not_of(pDelims);
		pString = pString.substr(f, l - f + 1);
	}
	else if (pString.size() > 0)
	{
		pString.clear();
	}
}


void toLower(
	std::string const& 	pString,
	std::string& 		pOutput)
{
	std::transform(
		pString.begin(),
		pString.end(),
		pOutput.begin(),
		::tolower);
}


bool toBool(char pChar)
{
	return (pChar == '0' || pChar == 'f' || pChar == 'F' || pChar == 'n' || pChar == 'N' ? false : true);
}


bool toBool(std::string const& pString)
{
	return toBool(pString[0]);
}


size_t toSizeT(
	std::string const& 	pString,
	char** 				pEndPoint,
	int 				pBase)
{
	return toSizeT(pString.data(), pEndPoint, pBase);
}


size_t toSizeT(
	char const* pString,
	char** 		pEndPoint,
	int 		pBase)
{
	return static_cast<size_t>(std::strtoll(pString, pEndPoint, pBase));
}


double toDouble(
	std::string const& 	pString,
	char** 				pEndPoint)
{
	return toDouble(pString.data(), pEndPoint);
}


double toDouble(
	char const* pString,
	char** 		pEndPoint)
{
	return std::strtod(pString, pEndPoint);
}


void setStreamMaxDoublePrecision(std::ostream& pStream)
{
	pStream.precision(std::numeric_limits<double>::digits10 + 1);
}


std::ostream& printDouble(std::ostream& pStream, double pDouble)
{
	setStreamMaxDoublePrecision(pStream);
	return (pStream << pDouble);
}


}
