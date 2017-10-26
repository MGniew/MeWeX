
#pragma once

#include <limits>
#include <memory>

#include "KBestElementList.h"
#include "../utils/Debug.h"


namespace structure
{


/**
 * \brief Klasa bazowa dla struktur budujących rankingi k-najlepszych elementow.
 *
 * Klasa jest klasą bazową dla klasy budujących rankingi k-najlepszych elementów.
 * Zadaniem obiektu jest składowanie elementów, a następnie zwrócenie KBestElementList
 * jako wyniku działania.
 *
 * @see KBestElement
 * @see KBestElementList
 */
template <typename E, typename S, typename Container>
class AbstractKBestStructure
{
public:
	typedef KBestElementList<E, S>				KBestList;
	typedef typename KBestList::Element			Element;

public:
	static constexpr size_t maxTopSize(){ return std::numeric_limits<size_t>::max(); }
	static constexpr size_t minTopSize(){ return 1; }

public:
	AbstractKBestStructure(size_t pTopSize = maxTopSize());

	AbstractKBestStructure(AbstractKBestStructure&& 				pKBest) = default;
	AbstractKBestStructure(AbstractKBestStructure const& 			pKBest) = default;
	AbstractKBestStructure& operator=(AbstractKBestStructure&&	 	pKBest) = default;
	AbstractKBestStructure& operator=(AbstractKBestStructure const& pKBest) = default;

	virtual ~AbstractKBestStructure() = default;


	virtual void				addElement(Element const& pElement) = 0;
	virtual void				addElement(
									E const& 	pElement,
									S const& 	pScore);


	virtual Element const&		topElement()		const = 0;
	virtual Element				topElementCopy()	const;

	virtual void				popElement() 		= 0;
	virtual void				clear()				= 0;

	virtual KBestList			retrieveKBest();


	virtual void				setTopSize(size_t pTopSize);


	virtual size_t				getTopSize()	const;

	virtual Container const&	getContainer()	const;
	virtual Container&			getContainer();

	virtual size_t				size()			const;


private:
	Container	mContainer;
	size_t		mTopSize;
};


template <typename E, typename S, typename Container>
AbstractKBestStructure<E, S, Container>::AbstractKBestStructure(size_t pTopSize)
:
	mTopSize(pTopSize)
{

}


template <typename E, typename S, typename Container>
void AbstractKBestStructure<E, S, Container>::addElement(
	E const& 	pElement,
	S const& 	pScore)
{
	addElement(Element(pElement, pScore));
}


template <typename E, typename S, typename Container>
auto AbstractKBestStructure<E, S, Container>::topElementCopy() const -> Element
{
	return topElement();
}


template <typename E, typename S, typename Container>
auto AbstractKBestStructure<E, S, Container>::retrieveKBest() -> KBestList
{
	KBestList v;
	v.getData().resize(mContainer.size());

	size_t size = v.size();
	for (size_t i = 0; i < size; ++i)
	{
		v[size - i - 1] = topElement();
		popElement();
	}
	return v;
}


template <typename E, typename S, typename Container>
void AbstractKBestStructure<E, S, Container>::setTopSize(size_t pTopSize)
{
	mTopSize = pTopSize;
	while (mContainer.size() > mTopSize)
	{
		popElement();
	}
}


template <typename E, typename S, typename Container>
size_t AbstractKBestStructure<E, S, Container>::getTopSize() const
{
	return mTopSize;
}


template <typename E, typename S, typename Container>
auto AbstractKBestStructure<E, S, Container>::getContainer() const -> Container const&
{
	return mContainer;
}


template <typename E, typename S, typename Container>
auto AbstractKBestStructure<E, S, Container>::getContainer() -> Container&
{
	return mContainer;
}


template <typename E, typename S, typename Container>
size_t AbstractKBestStructure<E, S, Container>::size() const
{
	return mContainer.size();
}


}
