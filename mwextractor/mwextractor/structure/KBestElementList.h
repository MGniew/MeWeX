
#pragma once

#include "KBestElement.h"


namespace structure
{


/**
 * \brief Obiekty tej klasy są wynikiem działania klas generujących rankingi k-najlepszych elementów.
 *
 * @see AbstractKBestStructure
 * @see QueueKBestStructure
 */
template <typename E, typename S>
class KBestElementList
{
public:
	typedef E										ElementType;
	typedef S										ScoreType;
	typedef KBestElement<ElementType, ScoreType>	Element;
	typedef std::vector<Element>					ElementVector;

public:
	KBestElementList() 											= default;
	KBestElementList(KBestElementList&& 				pKBest)	= default;
	KBestElementList(KBestElementList const& 			pKBest) = delete;
	KBestElementList& operator=(KBestElementList&& 		pKBest) = default;
	KBestElementList& operator=(KBestElementList const& pKBest) = delete;

	ElementVector const& 	getData()	const;
	ElementVector& 			getData();

	std::string const&		getDescription() const;
	std::string&			getDescription();

	void 					setDescription(std::string const& pDescription);

	Element const&			operator[](size_t pIndex) const;
	Element&				operator[](size_t pIndex);

	size_t 					size() 		const;

private:
	ElementVector 	mData;
	std::string		mDescription;
};


template <typename E, typename S>
auto KBestElementList<E, S>::getData() const -> ElementVector const&
{
	return mData;
}


template <typename E, typename S>
auto KBestElementList<E, S>::getData() -> ElementVector&
{
	return mData;
}


template <typename E, typename S>
std::string const& KBestElementList<E, S>::getDescription() const
{
	return mDescription;
}


template <typename E, typename S>
std::string& KBestElementList<E, S>::getDescription()
{
	return mDescription;
}


template <typename E, typename S>
void KBestElementList<E, S>::setDescription(std::string const& pDescription)
{
	mDescription = pDescription;
}


template <typename E, typename S>
auto KBestElementList<E, S>::operator[](size_t pIndex) const -> Element const&
{
	return mData[pIndex];
}


template <typename E, typename S>
auto KBestElementList<E, S>::operator[](size_t pIndex) -> Element&
{
	return mData[pIndex];
}


template <typename E, typename S>
size_t KBestElementList<E, S>::size() const
{
	return mData.size();
}


}
