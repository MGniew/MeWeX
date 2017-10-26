
#pragma once

#include <vector>

#include "FrequencyStorage.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Klasa przechowująca słowo wraz z jego częścią
 * mowy i częstości tego słowa.
 *
 * Klasa przechowuje słowo (np. tekst) wraz z jego
 * częścią mowy.
 * Zapisane w niej są także informacje o częstości
 * tego słowa wraz z daną częścią mowy.
 *
 * @see FrequencyStorage
 */
template <typename PosType, typename WordType>
class Word {
public:
	template <typename WT, typename PT>
	friend std::ostream& operator<<(std::ostream& pStream, Word<WT, PT> const& pWord);


public:
	Word(
		PosType const& 	pPos,
		WordType const&	pContent,
		double			pFrequency,
		size_t			pSources);

	Word(Word&& 				pWord) = default;
	Word(Word const& 			pWord) = default;
	Word& operator=(Word&& 		pWord) = default;
	Word& operator=(Word const& pWord) = default;

	~Word() = default;


	WordType const& 	getContent() 			const;
	WordType& 			getContent();
	WordType 			getContentCopy()		const;

	PosType const&		getPartOfSpeech()		const;
	PosType&			getPartOfSpeech();
	PosType				getPartOfSpeechCopy()	const;

	FrequencyStorage&	getMetadata()			const;


	void setContent(WordType const& pContent);

	void setPartOfSpeech(PosType const& pPos);


	bool operator==(Word const& pWord) 	const;
	bool operator!=(Word const& pWord) 	const;
	bool operator>(Word const& pWord) 	const;
	bool operator<(Word const& pWord) 	const;
	bool operator>=(Word const& pWord) 	const;
	bool operator<=(Word const& pWord) 	const;

private:
	mutable	FrequencyStorage	mMetadata;
	PosType 					mPos;
	WordType					mContent;
};


template <typename WT, typename PT>
std::ostream& operator<<(std::ostream& pStream, Word<WT, PT> const& pWord)
{
	pStream << pWord.mPos << '\t' << pWord.mContent << '\t' << pWord.mMetadata.getGlobalFrequency();
	for (size_t i = 0; i < pWord.mMetadata.getSourceCount(); ++i)
	{
		pStream << '\t' << pWord.mMetadata.getLocalFrequency(i);
	}
	return pStream;
}


template <typename PosType, typename WordType>
Word<PosType, WordType>::Word(
	PosType const& 	pPos,
	WordType const&	pContent,
	double			pFrequency,
	size_t			pSources)
:
	mMetadata(pFrequency, pSources),
	mPos(pPos),
	mContent(pContent)
{

}


template <typename PosType, typename WordType>
WordType const& Word<PosType, WordType>::getContent() const
{
	return mContent;
}


template <typename PosType, typename WordType>
WordType& Word<PosType, WordType>::getContent()
{
	return mContent;
}


template <typename PosType, typename WordType>
WordType Word<PosType, WordType>::getContentCopy() const
{
	return mContent;
}


template <typename PosType, typename WordType>
PosType const& Word<PosType, WordType>::getPartOfSpeech() const
{
	return mPos;
}


template <typename PosType, typename WordType>
PosType& Word<PosType, WordType>::getPartOfSpeech()
{
	return mPos;
}


template <typename PosType, typename WordType>
PosType Word<PosType, WordType>::getPartOfSpeechCopy() const
{
	return mPos;
}


template <typename PosType, typename WordType>
FrequencyStorage& Word<PosType, WordType>::getMetadata() const
{
	return mMetadata;
}


template <typename PosType, typename WordType>
void Word<PosType, WordType>::setContent(WordType const& pContent)
{
	mContent = pContent;
}


template <typename PosType, typename WordType>
void Word<PosType, WordType>::setPartOfSpeech(PosType const& pPos)
{
	mPos = pPos;
}


template <typename PosType, typename WordType>
bool Word<PosType, WordType>::operator==(Word const& pWord) const
{
	return (mContent == pWord.mContent) && (mPos == pWord.mPos);
}


template <typename PosType, typename WordType>
bool Word<PosType, WordType>::operator!=(Word const& pWord) const
{
	return !((*this) == pWord);
}


template <typename PosType, typename WordType>
bool Word<PosType, WordType>::operator>(Word const& pWord) const
{
	if (mContent > pWord.mContent)
	{
		return true;
	}
	else if (mContent < pWord.mContent)
	{
		return false;
	}

	return (mPos > pWord.mPos);
}


template <typename PosType, typename WordType>
bool Word<PosType, WordType>::operator<(Word const& pWord) const
{
	if (mContent < pWord.mContent)
	{
		return true;
	}
	else if (mContent > pWord.mContent)
	{
		return false;
	}

	return (mPos < pWord.mPos);
}


template <typename PosType, typename WordType>
bool Word<PosType, WordType>::operator>=(Word const& pWord) const
{
	return !((*this) < pWord);
}


template <typename PosType, typename WordType>
bool Word<PosType, WordType>::operator<=(Word const& pWord) const
{
	return !((*this) > pWord);
}


	}
}


namespace std
{
	template <typename PosType, typename WordType>
	struct hash<structure::storage::Word<PosType, WordType>>
	{
		typedef structure::storage::Word<PosType, WordType> __Word;

		size_t operator()(__Word const& pWord) const
		{
			return
				std::hash<PosType>()(pWord.getPartOfSpeech()) +
				std::hash<WordType>()(pWord.getContent());
		}
	};
}
