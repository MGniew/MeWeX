
#include <sstream>

#include "../../utils/Math.h"

#include "WordStorage.h"


namespace structure
{
	namespace storage
	{



WordStorage::WordStorage()
:
	PartOfSpeechStorage(),
	mWordGlobalFrequency(0)
{

}


size_t WordStorage::getWordCount() const
{
	return mWords.size();
}


double WordStorage::getWordGlobalFrequency() const
{
	return mWordGlobalFrequency;
}


void WordStorage::setWordGlobalFrequency(double pWordGlobalFrequency)
{
	mWordGlobalFrequency = pWordGlobalFrequency;
}


auto WordStorage::findWordId(WordIteratorConst const& pWordIterator) const -> WordId
{
	return mWords.findObjectId(pWordIterator);
}


auto WordStorage::findWordId(WordT const& pWord) const -> WordId
{
	return mWords.findObjectId(pWord);
}


auto WordStorage::findWordIdSilent(WordT const& pWord) const -> WordId
{
	return mWords.findObjectIdSilent(pWord);
}


auto WordStorage::findWordIdAnyPartOfSpeechSilent(WordT const& pWord) const -> WordId
{
	auto iter = beginWordsForAnyPartOfSpeech(pWord);
	return iter != endWords() ? findWordId(iter) : nullptr;
}


auto WordStorage::findWordIdAnyPartOfSpeech(WordT const& pWord) const -> WordId
{
	WordId id = findWordIdAnyPartOfSpeechSilent(pWord);
	EXCEPTION(id != nullptr, "WordStorage::findWordIdAnyPartOfSpeech(): no such word '" << pWord.getContent() << "'.");
	return id;
}


auto WordStorage::findWordIdsAllPartOfSpeech(WordT const& pWord) const -> WordIdVector
{
	WordIdVector ids;
	{
		auto end = endWordsForAnyPartOfSpeech(pWord);
		for (auto begin = beginWordsForAnyPartOfSpeech(pWord); begin != end; ++begin)
		{
			ids.push_back(findWordId(begin));
		}
	}

	return ids;
}


auto WordStorage::findWord(WordIteratorConst const& pWordIterator) const -> WordT const&
{
	return mWords.findObject(pWordIterator);
}


auto WordStorage::findWord(WordId pWordId) const -> WordT const&
{
	return mWords.findObject(pWordId);
}


auto WordStorage::findAndCopyWord(WordId pWordId) const -> WordT
{
	return mWords.findAndCopyObject(pWordId);
}


bool WordStorage::addWord(WordT&& pWord)
{
	auto res = mWords.addObjectGetResult(std::forward<WordT>(pWord));
	updateFrequencies(pWord, res);
	return res.second;
}


bool WordStorage::addWord(WordT const& pWord)
{
	auto res = mWords.addObjectGetResult(pWord);
	updateFrequencies(pWord, res);
	return res.second;
}


auto WordStorage::addWordGetId(WordT&& pWord) -> WordId
{
	auto res = mWords.addObjectGetResult(std::forward<WordT>(pWord));
	updateFrequencies(pWord, res);
	return findWordId(res.first);
}


auto WordStorage::addWordGetId(WordT const& pWord) -> WordId
{
	auto res = mWords.addObjectGetResult(pWord);
	updateFrequencies(pWord, res);
	return findWordId(res.first);
}


auto WordStorage::addWordGetResult(WordT&& pWord) -> AddResult
{
	auto res = mWords.addObjectGetResult(std::forward<WordT>(pWord));
	updateFrequencies(pWord, res);
	return res;
}


auto WordStorage::addWordGetResult(WordT const& pWord) -> AddResult
{
	auto res = mWords.addObjectGetResult(pWord);
	updateFrequencies(pWord, res);
	return res;
}


void WordStorage::recomputeWordsGlobalFrequency()
{
	for (auto i = beginWords(); i != endWords(); ++i)
	{
		i->getMetadata().computeGlobalFrequency();
	}
}


std::string WordStorage::createWordReprezentation(WordT const& pWord) const
{
	std::stringstream str;
	str << createPartOfSpeechReprezentation(pWord.getPartOfSpeechCopy()) << ':' << pWord.getContent();
	return str.str();
}


std::string WordStorage::createWordReprezentation(WordId const& pWordId) const
{
	return createWordReprezentation(findWord(pWordId));
}


auto WordStorage::parseWordReprezentation(std::string const& pWordString) const -> WordId
{
	size_t split = pWordString.find_first_of(':');
	return findWordId(WordT(
		parsePartOfSpeechReprezentation(pWordString.substr(0, split)),
		pWordString.substr(split + 1),
		0,
		0));
}


auto WordStorage::beginWords() const -> WordIteratorConst
{
	return mWords.begin();
}


auto WordStorage::beginWords() -> WordIterator
{
	return mWords.begin();
}


auto WordStorage::endWords() const -> WordIteratorConst
{
	return mWords.end();
}


auto WordStorage::endWords() -> WordIterator
{
	return mWords.end();
}


auto WordStorage::beginWordsForAnyPartOfSpeech(WordT pWord) const -> WordIteratorConst
{
	pWord.setPartOfSpeech(nullptr);
	return mWords.getContainer().lower_bound(pWord);
}


auto WordStorage::beginWordsForAnyPartOfSpeech(WordT pWord) -> WordIterator
{
	pWord.setPartOfSpeech(nullptr);
	return mWords.getContainer().lower_bound(pWord);
}


auto WordStorage::endWordsForAnyPartOfSpeech(WordT pWord) const -> WordIteratorConst
{
	pWord.setPartOfSpeech(nullptr);
	--pWord.getPartOfSpeech();
	return mWords.getContainer().upper_bound(pWord); // upper_bound maybe? It should be better in theory but in practice it shouldn't be any difference
}


auto WordStorage::endWordsForAnyPartOfSpeech(WordT pWord) -> WordIterator
{
	pWord.setPartOfSpeech(nullptr);
	--pWord.getPartOfSpeech();
	return mWords.getContainer().upper_bound(pWord); // upper_bound maybe?
}


auto WordStorage::range(WordT pWord) const -> WordIteratorConstPair
{
	WordIteratorConstPair pair;

	pWord.setPartOfSpeech(nullptr);
	pair.first = mWords.getContainer().lower_bound(pWord);

	--pWord.getPartOfSpeech();
	pair.second = mWords.getContainer().upper_bound(pWord);

	return pair;
}


auto WordStorage::range(WordT pWord) -> WordIteratorPair
{
	WordIteratorPair pair;

	pWord.setPartOfSpeech(nullptr);
	pair.first = mWords.getContainer().lower_bound(pWord);

	--pWord.getPartOfSpeech();
	pair.second = mWords.getContainer().upper_bound(pWord);

	return pair;
}


void WordStorage::updateFrequencies(
	WordT const& 		pInsertedWord,
	AddResult const& 	pResult)
{
	if (!pResult.second)
	{
		pResult.first->getMetadata().addFrequencies(pInsertedWord.getMetadata());
	}
	mWordGlobalFrequency += pInsertedWord.getMetadata().getGlobalFrequency();
}


	}
}
