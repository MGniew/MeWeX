
#include "../../exception/Exception.h"

#include "StreamingFileReader.h"


namespace structure
{
	namespace io
	{


StreamingFileReader::StreamingFileReader(std::string const& pFile)
{
	open(pFile);
}


StreamingFileReader::~StreamingFileReader()
{
	close();
}


bool StreamingFileReader::readline(
	std::string& 	pLine,
	char 			pDelimeter)
{
	return static_cast<bool>(std::getline(mFile, pLine, pDelimeter));
}


void StreamingFileReader::open(std::string const& pFilePath)
{
	close();
	mFile.open(pFilePath, std::ios_base::in);
	EXCEPTION(mFile.is_open(), "StreamingFileReader::open(): cannot open a file '" << pFilePath << "'.");
}


void StreamingFileReader::close()
{
	if(mFile.is_open())
	{
		mFile.close();
	}
}


	}
}
