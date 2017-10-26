
#pragma once

#include <fstream>


namespace structure
{
	namespace io
	{


class StreamingFileReader
{
public:
	StreamingFileReader(std::string const& pFile);

	StreamingFileReader() 													= default;
	StreamingFileReader(StreamingFileReader&& 					pReader)	= default;
	StreamingFileReader(StreamingFileReader const& 				pReader)	= delete;
	StreamingFileReader& operator=(StreamingFileReader&&	 	pReader)	= default;
	StreamingFileReader& operator=(StreamingFileReader const& 	pReader)	= delete;

	virtual ~StreamingFileReader();


	virtual bool readline(
		std::string& 	pLine,
		char			pDelimeter = '\n');

	void open(std::string const& pPath);
	void close();


private:
	std::fstream mFile;
};


	}
}
