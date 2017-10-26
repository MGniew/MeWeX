
#pragma once

#include "../FastSetStorage.h"
#include "PartOfSpeech.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Skład części mowy.
 *
 * Obiekt klasy przechowuje informacje o częściach mowy
 * pozyskanych ze sparsowanego zestawu korpusów.
 *
 * @see PartOfSpeech
 */
class PartOfSpeechStorage
{
public:
	typedef PartOfSpeech<std::string>								PartOfSpeechT;
	typedef FastSetStorage<PartOfSpeechT>::ObjectId 				PartOfSpeechId;
	typedef FastSetStorage<PartOfSpeechT>::ContainerIteratorConst	PartOfSpeechIteratorConst;
	typedef FastSetStorage<PartOfSpeechT>::ContainerIterator		PartOfSpeechIterator;

private:
	typedef FastSetStorage<PartOfSpeechT>::AddResult 				AddResult;


public:
	PartOfSpeechStorage()													= default;
	PartOfSpeechStorage(PartOfSpeechStorage&& 					pStorage) 	= default;
	PartOfSpeechStorage(PartOfSpeechStorage const& 				pStorage) 	= delete;
	PartOfSpeechStorage& operator=(PartOfSpeechStorage&&	 	pStorage)	= default;
	PartOfSpeechStorage& operator=(PartOfSpeechStorage const& 	pStorage)	= delete;

	virtual ~PartOfSpeechStorage() = default;


	size_t						getPartOfSpeechCount()		 											const;

	PartOfSpeechId 				findPartOfSpeechId(PartOfSpeechIteratorConst const& pIterator)			const;
	PartOfSpeechId 				findPartOfSpeechId(PartOfSpeechT const& pPartOfSpeech) 					const;
	PartOfSpeechId 				findPartOfSpeechIdSilent(PartOfSpeechT const& pPartOfSpeech)			const;

	PartOfSpeechT const&		findPartOfSpeech(PartOfSpeechIteratorConst const& pIterator)			const;
	PartOfSpeechT const&		findPartOfSpeech(PartOfSpeechId pPartOfSpeechId) 						const;
	PartOfSpeechT				findAndCopyPartOfSpeech(PartOfSpeechId pPartOfSpeechId)					const;

	bool 						addPartOfSpeech(PartOfSpeechT&& pPartOfSpeech);
	bool 						addPartOfSpeech(PartOfSpeechT const& pPartOfSpeech);
	PartOfSpeechId 				addPartOfSpeechGetId(PartOfSpeechT&& pPartOfSpeech);
	PartOfSpeechId 				addPartOfSpeechGetId(PartOfSpeechT const& pPartOfSpeech);

	void						recomputePartsOfSpeechGlobalFrequency();

	virtual std::string			createPartOfSpeechReprezentation(PartOfSpeechT const& pPartOfSpeech)	const;
	virtual std::string			createPartOfSpeechReprezentation(PartOfSpeechId const& pPartOfSpeechId)	const;

	virtual PartOfSpeechId		parsePartOfSpeechReprezentation(std::string const& pPartOfSpeech)		const;

	PartOfSpeechIteratorConst	beginPartsOfSpeech() 	const;
	PartOfSpeechIterator		beginPartsOfSpeech();
	PartOfSpeechIteratorConst	endPartsOfSpeech() 		const;
	PartOfSpeechIterator		endPartsOfSpeech();


private:
	void updateFrequencies(
		PartOfSpeechT const& 	pInsertedPartOfSpeech,
		AddResult const& 		pResult);


private:
	FastSetStorage<PartOfSpeechT> mPartsOfSpeech;
};




	}
}
