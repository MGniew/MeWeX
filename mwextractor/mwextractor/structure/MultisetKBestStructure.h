
#pragma once

#include <set>

#include "AbstractKBestStructure.h"
#include "../utils/Debug.h"


namespace structure
{


template <typename E, typename S, typename Comparator>
using MultisetKBestStructureContainer = std::multiset<KBestElement<S, E>, Comparator>;


/**
 * \brief Klasa generująca rankingi k-najlepszych z wykorzystaniem standardowej multi mapy.
 *
 * @see AbstractKBestStructure
 */
template <typename E, typename S, typename Comparator = std::less<KBestElement<E, S>>>
class MultisetKBestStructure : public AbstractKBestStructure<E, S, MultisetKBestStructureContainer<E, S, Comparator>>
{
public:
	typedef MultisetKBestStructureContainer<E, S, Comparator> 	__Container;
	typedef KBestAbstract<E, S, __Container> 					__Base;

public:
	typedef typename __Base::Element Element;

public:
	MultisetKBestStructure(size_t pTopSize = __Base::mTopSize());

	MultisetKBestStructure(MultisetKBestStructure&& 				pKBest) = default;
	MultisetKBestStructure(MultisetKBestStructure const&			pKBest) = default;
	MultisetKBestStructure& operator=(MultisetKBestStructure&&	 	pKBest) = default;
	MultisetKBestStructure& operator=(MultisetKBestStructure const& pKBest) = default;

	virtual ~MultisetKBestStructure() = default;

	virtual void				addElement(Element const& pElement) override;


	virtual Element const&		topElement() 	const override;

	virtual void				popElement()	override;
	virtual void				clear()			override;
};


template <typename E, typename S, typename C>
MultisetKBestStructure<E, S, C>::MultisetKBestStructure(size_t pTopSize)
:
	__Base(pTopSize)
{

}


template <typename E, typename S, typename C>
void MultisetKBestStructure<E, S, C>::addElement(Element const& pElement)
{
	this->getContainer().insert(pElement);
	if (this->getContainer().size() > this->getTopSize())
	{
		popElement();
	}
}


template <typename E, typename S, typename C>
auto auto MultisetKBestStructure<E, S, C>::topElement() const -> Element const&
{
	return *(this->getContainer()->begin());
}


template <typename E, typename S, typename C>
void MultisetKBestStructure<E, S, C>::popElement()
{
	this->getContainer()->erase(this->getContainer()->begin());
}


template <typename E, typename S, typename C>
void MultisetKBestStructure<E, S, C>::clear()
{
	this->getContainer().clear();
}


}
