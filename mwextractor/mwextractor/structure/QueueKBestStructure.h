

#pragma once

#include <queue>
#include <functional>

#include "AbstractKBestStructure.h"


namespace structure
{


template <typename E, typename S, typename Comparator>
using QueueKBestStructureContainer = std::priority_queue<S, std::vector<KBestElement<E, S>>, Comparator>;


/**
 * \brief Klasa generująca rankingi k-najlepszych z wykorzystaniem kolejki priorytetowej.
 *
 * @see AbstractKBestStructure
 * @see MultisetKBestStructure
 */
template <typename E, typename S, typename Comparator = std::greater<KBestElement<E, S>>>
class QueueKBestStructure : public AbstractKBestStructure<E, S, QueueKBestStructureContainer<E, S, Comparator>>
{
private:
	typedef QueueKBestStructureContainer<E, S, Comparator> 	__Container;
	typedef AbstractKBestStructure<E, S, __Container> 		__Base;

public:
	typedef typename __Base::Element Element;

public:
	QueueKBestStructure(size_t pTopSize = __Base::mTopSize());

	QueueKBestStructure(QueueKBestStructure&& 					pKBest) = default;
	QueueKBestStructure(QueueKBestStructure const&				pKBest) = default;
	QueueKBestStructure& operator=(QueueKBestStructure&&		pKBest) = default;
	QueueKBestStructure& operator=(QueueKBestStructure const& 	pKBest) = default;

	virtual ~QueueKBestStructure() = default;

	virtual void			addElement(Element const& pElement) override;


	virtual Element const&	topElement() 	const override;

	virtual void			popElement()	override;
	virtual void			clear()			override;
};


template <typename E, typename S, typename C>
QueueKBestStructure<E, S, C>::QueueKBestStructure(size_t pTopSize)
:
	__Base(pTopSize)
{

}


template <typename E, typename S, typename C>
void QueueKBestStructure<E, S, C>::addElement(Element const& pElement)
{
	this->getContainer().push(pElement);
	if (this->getContainer().size() > this->getTopSize())
	{
		popElement();
	}
}


template <typename E, typename S, typename C>
auto QueueKBestStructure<E, S, C>::topElement() const -> Element const&
{
	return this->getContainer().top();
}


template <typename E, typename S, typename C>
void QueueKBestStructure<E, S, C>::popElement()
{
	this->getContainer().pop();
}


template <typename E, typename S, typename C>
void QueueKBestStructure<E, S, C>::clear()
{
	while(this->getContainer().size() > 0)
	{
		this->getContainer().pop();
	}
}


}
