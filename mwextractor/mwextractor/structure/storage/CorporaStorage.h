/*
 * CorporaStorage.h
 *
 *  Created on: 08-07-2014
 *      Author: michalw
 */

#pragma once

#include "Corpora.h"
#include "../FastSetStorage.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Skład metadanych o korpusach.
 *
 * Klasa zajmuje się przechowywaniem metadanych o sparsowanych korpusach.
 *
 * @see Corpora
 */
class CorporaStorage {
public:
	typedef Corpora										CorporaT;
	typedef FastSetStorage<CorporaT> 					FastCorporaStorage;

	typedef FastCorporaStorage::ObjectId 				CorporaId;
	typedef FastCorporaStorage::ContainerIteratorConst	CorporaIteratorConst;
	typedef FastCorporaStorage::ContainerIterator		CorporaIterator;

private:
	typedef FastCorporaStorage::AddResult				AddResult;


public:
	CorporaStorage()											= default;
	CorporaStorage(CorporaStorage&& 				pStorage) 	= default;
	CorporaStorage(CorporaStorage const& 			pStorage) 	= default;
	CorporaStorage& operator=(CorporaStorage&& 		pStorage) 	= default;
	CorporaStorage& operator=(CorporaStorage const& pStorage) 	= default;

	virtual ~CorporaStorage() = default;


	size_t					getCorporaCount()		 									const;

	CorporaId 				findCorporaId(CorporaIteratorConst const& pIterator)		const;
	CorporaId 				findCorporaId(CorporaT const& pCorpora) 					const;
	CorporaId 				findCorporaIdSilent(CorporaT const& pCorpora)				const;

	CorporaT const& 		findCorpora(CorporaIteratorConst const& pIterator)			const;
	CorporaT const&			findCorpora(CorporaId pCorporaId) 							const;
	CorporaT				findAndCopyCorpora(CorporaId pCorporaId)					const;

	bool 					addCorpora(CorporaT&& pCorpora);
	bool 					addCorpora(CorporaT const& pCorpora);
	CorporaId 				addCorporaGetId(CorporaT&& pCorpora);
	CorporaId 				addCorporaGetId(CorporaT const& pCorpora);

	void					recomputeCorporasGlobalFrequency();

	virtual std::string		createCorporaReprezentation(CorporaT const& pCorpora)		const;
	virtual std::string		createCorporaReprezentation(CorporaId const& pCorporaId)	const;

	virtual CorporaId		parseCorporaReprezentation(std::string const& pCorpora)		const;

	CorporaIteratorConst	beginCorporas() const;
	CorporaIterator			beginCorporas();
	CorporaIteratorConst	endCorporas() 	const;
	CorporaIterator			endCorporas();


private:
	void updateFrequencies(
		CorporaT const& 	pInsertedCorpora,
		AddResult const& 	pResult);


private:
	FastCorporaStorage mCorporas;
};


	}
}
