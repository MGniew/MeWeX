
#pragma once

#include "../builder/OrthExtractor.h"
#include "../storage/KBestTupleList.h"


namespace structure
{
	namespace io
	{


class KBestTupleWithOrthsListIO
{
public:
	typedef storage::MatrixTupleStorage 		TupleStorage;
	typedef storage::KBestTupleList				KBestTupleList;

	typedef builder::OrthExtractor::OrthFormMap	OrthFormMap;
	typedef builder::OrthExtractor::OrthForm	OrthForm;

public:
	KBestTupleWithOrthsListIO() 														= default;
	KBestTupleWithOrthsListIO(KBestTupleWithOrthsListIO&& 					pKBestIO) 	= default;
	KBestTupleWithOrthsListIO(KBestTupleWithOrthsListIO const&	 			pKBestIO) 	= delete;
	KBestTupleWithOrthsListIO& operator=(KBestTupleWithOrthsListIO&&	 	pKBestIO) 	= default;
	KBestTupleWithOrthsListIO& operator=(KBestTupleWithOrthsListIO const& 	pKBestIO) 	= delete;

	virtual ~KBestTupleWithOrthsListIO()	= default;


	void write(
		KBestTupleList const&	pKBest,
		OrthFormMap const&		pOrthMap,
		TupleStorage const& 	pStorage,
		std::string const&		pFilePath) const;

	void writeSome(
		KBestTupleList const&	pKBest,
		OrthFormMap const&		pOrthMap,
		TupleStorage const& 	pStorage,
		std::string const&		pFilePath,
		size_t					pCount) const;

	/*KBestTupleList read(
		TupleStorage const& pStorage,
		std::string const&	pFile,
		OrthMap&			pOrthMap) const;*/
};


	}
}
