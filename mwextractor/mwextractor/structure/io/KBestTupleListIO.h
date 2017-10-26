
#pragma once

#include "../storage/KBestTupleList.h"


namespace structure
{
	namespace io
	{


class KBestTupleListIO
{
public:
	typedef storage::MatrixTupleStorage TupleStorage;
	typedef storage::KBestTupleList		KBestTupleList;

public:
	KBestTupleListIO() 												= default;
	KBestTupleListIO(KBestTupleListIO&& 				pKBestIO) 	= default;
	KBestTupleListIO(KBestTupleListIO const&	 		pKBestIO) 	= delete;
	KBestTupleListIO& operator=(KBestTupleListIO&&	 	pKBestIO) 	= default;
	KBestTupleListIO& operator=(KBestTupleListIO const& pKBestIO) 	= delete;

	virtual ~KBestTupleListIO()	= default;


	void write(
		KBestTupleList const&	pKBest,
		TupleStorage const& 	pStorage,
		std::string const&		pFilePath) const;

	void writeSome(
		KBestTupleList const&	pKBest,
		TupleStorage const& 	pStorage,
		std::string const&		pFilePath,
		size_t					pCount) const;

	KBestTupleList read(
		TupleStorage const& pStorage,
		std::string const&	pFile,
		size_t				pMaxLines) const;
};


	}
}
