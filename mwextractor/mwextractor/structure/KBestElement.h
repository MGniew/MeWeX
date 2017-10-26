
#include <vector>
#include <memory>


namespace structure
{


/**
 * \brief Obiekty tej klasy wykorzystywane są do generowania rankingów elementów.
 */
template <typename E, typename S>
struct KBestElement
{
	E element;
	S score;

	KBestElement() = default;
	KBestElement(
		E const& pElement,
		S const& pScore);

	KBestElement(KBestElement&& 				pKBestElement) = default;
	KBestElement(KBestElement const& 			pKBestElement) = default;
	KBestElement& operator=(KBestElement&&		pKBestElement) = default;
	KBestElement& operator=(KBestElement const& pKBestElement) = default;

	bool operator==(KBestElement const& pElement)	const;
	bool operator!=(KBestElement const& pElement)	const;
	bool operator<(KBestElement const& pElement)	const;
	bool operator<=(KBestElement const& pElement)	const;
	bool operator>(KBestElement const& pElement) 	const;
	bool operator>=(KBestElement const& pElement) 	const;
};


template <typename E, typename S>
KBestElement<E, S>::KBestElement(
	E const& pElement,
	S const& pScore)
:
	element(pElement),
	score(pScore)
{

}


template <typename E, typename S>
bool KBestElement<E, S>::operator==(KBestElement const& pElement) const
{
	return score == pElement.score;
}


template <typename E, typename S>
bool KBestElement<E, S>::operator!=(KBestElement const& pElement) const
{
	return score != pElement.score;
}


template <typename E, typename S>
bool KBestElement<E, S>::operator<(KBestElement const& pElement) const
{
	return score < pElement.score;
}


template <typename E, typename S>
bool KBestElement<E, S>::operator<=(KBestElement const& pElement) const
{
	return score <= pElement.score;
}


template <typename E, typename S>
bool KBestElement<E, S>::operator>(KBestElement const& pElement) const
{
	return score > pElement.score;
}


template <typename E, typename S>
bool KBestElement<E, S>::operator>=(KBestElement const& pElement) const
{
	return score >= pElement.score;
}


}
