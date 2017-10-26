
#pragma once

#include <string>

#include "FrequencyStorage.h"


namespace structure
{
	namespace storage
	{


/*
 * \brief Klasa przechowuje informacje o danej części mowy.
 */
template <typename Type>
class PartOfSpeech {
public:
	template <typename T>
	friend std::ostream& operator<<(std::ostream& pStream, PartOfSpeech<T> const& pPartOfSpeech);


public:
	PartOfSpeech(
		Type const& pContent,
		size_t		pFrequency,
		size_t		pSources);

	PartOfSpeech(PartOfSpeech&& 				pPartOfSpeech) = default;
	PartOfSpeech(PartOfSpeech const& 			pPartOfSpeech) = default;
	PartOfSpeech& operator=(PartOfSpeech&& 		pPartOfSpeech) = default;
	PartOfSpeech& operator=(PartOfSpeech const& pPartOfSpeech) = default;

	~PartOfSpeech() = default;


	Type const& 		getContent() 		const;
	Type& 				getContent();
	Type 				getContentCopy()	const;

	FrequencyStorage&	getMetadata()		const;


	void setContent(Type const& pContent);


	bool operator==(PartOfSpeech const& pPartOfSpeech) 	const;
	bool operator!=(PartOfSpeech const& pPartOfSpeech) 	const;
	bool operator>(PartOfSpeech const& pPartOfSpeech) 	const;
	bool operator<(PartOfSpeech const& pPartOfSpeech) 	const;
	bool operator>=(PartOfSpeech const& pPartOfSpeech) 	const;
	bool operator<=(PartOfSpeech const& pPartOfSpeech) 	const;

private:
	mutable	FrequencyStorage	mMetadata;
	Type						mContent;
};


template <typename T>
std::ostream& operator<<(std::ostream& pStream, PartOfSpeech<T> const& pPartOfSpeech)
{
	pStream << pPartOfSpeech.mContent << '\t' << pPartOfSpeech.mMetadata.getGlobalFrequency();
	for (size_t i = 0; i < pPartOfSpeech.mMetadata.getSourceCount(); ++i)
	{
		pStream << '\t' << pPartOfSpeech.mMetadata.getLocalFrequency(i);
	}
	return pStream;
}


template <typename Type>
PartOfSpeech<Type>::PartOfSpeech(
	Type const& pContent,
	size_t		pFrequency,
	size_t		pSources)
:
	mMetadata(pFrequency, pSources),
	mContent(pContent)
{

}


template <typename Type>
Type const& PartOfSpeech<Type>::getContent() const
{
	return mContent;
}


template <typename Type>
Type& PartOfSpeech<Type>::getContent()
{
	return mContent;
}


template <typename Type>
Type PartOfSpeech<Type>::getContentCopy() const
{
	return mContent;
}


template <typename Type>
FrequencyStorage& PartOfSpeech<Type>::getMetadata() const
{
	return mMetadata;
}


template <typename Type>
void PartOfSpeech<Type>::setContent(Type const& pContent)
{
	mContent = pContent;
}


template <typename Type>
bool PartOfSpeech<Type>::operator==(PartOfSpeech const& pPartOfSpeech) const
{
	return mContent == pPartOfSpeech.mContent;
}


template <typename Type>
bool PartOfSpeech<Type>::operator!=(PartOfSpeech const& pPartOfSpeech) const
{
	return !((*this) == pPartOfSpeech);
}


template <typename Type>
bool PartOfSpeech<Type>::operator>(PartOfSpeech const& pPartOfSpeech) const
{
	return mContent > pPartOfSpeech.mContent;
}


template <typename Type>
bool PartOfSpeech<Type>::operator<(PartOfSpeech const& pPartOfSpeech) const
{
	return mContent < pPartOfSpeech.mContent;
}


template <typename Type>
bool PartOfSpeech<Type>::operator>=(PartOfSpeech const& pPartOfSpeech) const
{
	return mContent >= pPartOfSpeech.mContent;
}


template <typename Type>
bool PartOfSpeech<Type>::operator<=(PartOfSpeech const& pPartOfSpeech) const
{
	return mContent <= pPartOfSpeech.mContent;
}


	}
}


namespace std
{
	template <typename Type>
	struct hash<structure::storage::PartOfSpeech<Type>>
	{
		typedef structure::storage::PartOfSpeech<Type> __PartOfSpeech;

		size_t operator()(__PartOfSpeech const& pPartOfSpeech) const
		{
			return std::hash<Type>()(pPartOfSpeech.getContent());
		}
	};
}
