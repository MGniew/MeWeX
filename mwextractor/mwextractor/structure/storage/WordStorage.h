
#pragma once

#include <set>

#include "PartOfSpeechStorage.h"
#include "Word.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Składowisko słów.
 *
 * Obiekty klasy zajmują się składowaniem słów, ich częstości oraz
 * części mowy.
 *
 * @see Word
 * @see PartOfSpeech
 */
class WordStorage : public PartOfSpeechStorage
{
public:
	typedef Word<PartOfSpeechStorage::PartOfSpeechId, std::string> WordT;

private:
	typedef FastSetStorage<WordT, std::set<WordT>> 	Container;
	typedef Container::AddResult 					AddResult;

public:
	typedef Container::ObjectId 				WordId;
	typedef std::vector<WordId>					WordIdVector;

	typedef Container::ContainerIteratorConst	WordIteratorConst;
	typedef Container::ContainerIterator		WordIterator;

	typedef std::pair<WordIteratorConst, WordIteratorConst> WordIteratorConstPair;
	typedef std::pair<WordIterator, WordIterator> 			WordIteratorPair;

public:
	WordStorage();
	WordStorage(WordStorage&& 					pStorage)	= default;
	WordStorage(WordStorage const& 				pStorage) 	= delete;
	WordStorage& operator=(WordStorage&& 		pStorage)	= default;
	WordStorage& operator=(WordStorage const& 	pStorage)	= delete;

	virtual ~WordStorage() = default;


	size_t					getWordCount()											const;
	double					getWordGlobalFrequency()								const;

	void					setWordGlobalFrequency(double pWordGlobalFrequency);

	WordId 					findWordId(WordIteratorConst const& pWordIterator)		const;
	WordId 					findWordId(WordT const& pWord) 							const;
	WordId 					findWordIdSilent(WordT const& pWord)					const;
	WordId 					findWordIdAnyPartOfSpeechSilent(WordT const& pWord) 	const;
	WordId 					findWordIdAnyPartOfSpeech(WordT const& pWord) 			const;
	WordIdVector			findWordIdsAllPartOfSpeech(WordT const& pWord) 			const;

	WordT const&			findWord(WordIteratorConst const& pWordIterator)		const;
	WordT const&			findWord(WordId pWordId) 								const;
	WordT					findAndCopyWord(WordId pWordId)							const;

	bool 					addWord(WordT&& pWord);
	bool 					addWord(WordT const& pWord);
	WordId 					addWordGetId(WordT&& pWord);
	WordId 					addWordGetId(WordT const& pWord);
	AddResult 				addWordGetResult(WordT&& pWord);
	AddResult 				addWordGetResult(WordT const& pWord);

	void					recomputeWordsGlobalFrequency();

	std::string				createWordReprezentation(WordT const& pWord)			const;
	std::string				createWordReprezentation(WordId const& pWordId)			const;

	WordId					parseWordReprezentation(std::string const& pWordString)	const;

	WordIteratorConst		beginWords() 	const;
	WordIterator			beginWords();
	WordIteratorConst		endWords() 		const;
	WordIterator			endWords();

	WordIteratorConst 		beginWordsForAnyPartOfSpeech(WordT pWord) 	const;
	WordIterator 			beginWordsForAnyPartOfSpeech(WordT pWord);
	WordIteratorConst 		endWordsForAnyPartOfSpeech(WordT pWord) 	const;
	WordIterator			endWordsForAnyPartOfSpeech(WordT pWord);

	WordIteratorConstPair	range(WordT pWord) const;
	WordIteratorPair		range(WordT pWord);


private:
	void updateFrequencies(
		WordT const& 		pInsertedWord,
		AddResult const& 	pResult);


private:
	Container	mWords;
	double		mWordGlobalFrequency;
};


	}
}
