
#pragma once

#include <ostream>
#include <map>
#include <vector>

#include "FrequencyStorage.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Reprezentuje zbiór N powiązanych ze sobą elementów za pomocą relacji.
 *
 * Krotka reprezentuje zbiór N elementów powiązanych ze sobą
 * za pomocą pewnej relacji opisującej ich związek.
 * Elementy w krotce znajdują się w określonej kolejności.
 * Krotka zawiera zestaw elementów, relację oraz informacji o
 * częstościach elementów składowych krotki.
 *
 * @see FrequencyStorage
 */
template <
	typename ElementType,
	typename RelationType,
	typename Container = std::vector<ElementType>>
class Tuple
{
public:
	typedef size_t DifferenceMask;


public:
	template <typename E, typename R, typename C>
	friend std::ostream& operator<<(std::ostream& pStream, Tuple<E, R, C> const& pTuple);


public:
	/**
	 * \brief Konstruktor tworzący pustą krotkę o zadanym rozmiarze.
	 *
	 * @param pSize rozmiar krotki, liczba elementów.
	 * @param pRelation relacja dla elementów krotki.
	 * @param pFrequency częstość krotki.
	 * @param pSources liczba źródeł krotki.
	 *
	 * @see FrequencyStorage
	 */
	Tuple(
		size_t 			pSize,
		RelationType	pRelation,
		double 			pFrequency,
		size_t			pSources);

	/**
	 * \brief Konstruktor tworzący krotkę z zadanymi elementami.
	 *
	 * @param pElements uporządkowany zestaw elementów krotki.
	 * @param pRelation relacja dla elementów krotki.
	 * @param pFrequency częstość krotki.
	 * @param pSources liczba źródeł krotki
	 *
	 * @see FrequencyStorage
	 */
	Tuple(
		Container const&	pElements,
		RelationType		pRelation,
		double 				pFrequency,
		size_t				pSources);

	Tuple(Tuple&& 					pTuple)	= default;
	Tuple(Tuple const& 				pTuple)	= default;
	Tuple& operator=(Tuple&& 		pTuple) = default;
	Tuple& operator=(Tuple const& 	pTuple) = default;

	~Tuple() = default;


	Container const&	getElements() 					const;

	ElementType			getElementCopy(size_t pIndex) 	const;
	ElementType const& 	getElement(size_t pIndex) 		const;
	ElementType& 		getElement(size_t pIndex);

	RelationType		getRelationCopy() 				const;
	RelationType const& getRelation() 					const;
	RelationType& 		getRelation();

	FrequencyStorage&	getMetadata()					const;

	size_t				size() 							const;

	/**
	 * \brief Funkcja zwraca liczbę wszystkich subkrotek.
	 *
	 * Funkcja zwraca liczbę wszystkich możliwych do utworzenia
	 * subkrotek przy zachowaniu kolejności elementów,
	 * łącznie z krotką pustą jak i nią samą.
	 * Przykładowo dla krotki trójelementowej ABC funkcja zwróci
	 * 2^3 = 8, ponieważ można z niej utworzyć następujące krotki
	 * xxx Axx xBx xxC ABx xBC AxC ABC.
	 * Funkcja nie bierze pod uwagę relacji.
	 */
	size_t				subtupleCount()					const;


	void setElement(
		size_t 				pIndex,
		ElementType const& 	pElement);

	void setRelation(RelationType const& pRelation);


	ElementType const& 	operator[](size_t pIndex) const;
	ElementType& 		operator[](size_t pIndex);

	/**
	 * \brief Funkcja buduje maskę określającą różnice pomiędzy
	 * 		  dwiema krotkami.
	 *
	 * Funkcja na podstawie krotki z argumentu zbuduje maskę
	 * określającą, na którch elementach krotki się różnią elementami.
	 * Maska jest liczbą całkowitą, a na poszczególncyh bitach
	 * zakodowana jest informacja o tym czy dany element jest
	 * taki sam w obu krotkach czy nie. Wartość 1 na N-tej pozycji
	 * bitowej symbolizuje, że N-te elementy w obu krotkach są
	 * różne. Wartość 0 natomiast określa identyczność elementów
	 * w obu krotkach na danej pozycji.
	 * Funkcja nie bierze pod uwagę relacji.
	 *
	 * @see DifferenceMask
	 */
	DifferenceMask 		buildDifferenceMask(Tuple const& pTuple) const;

	/**
	 * \brief Funkcja buduje subkrotkę na podstawie maski różnicy.
	 *
	 * Funkcja wykorzystuje zadaną maskę różnicy i krotkę do
	 * utworzenia subkrotki. Subkrotka będzie tego samego rozmiaru
	 * co krotka na podstawie, której ją utworzono.
	 * Elementy, którym odpowiadające bity maski różnicy są równe
	 * 0 zostaną przekopiowane do nowej subkrotki.
	 * Elementy, którym odpowiadające bity maski różnicy są równe
	 * 1 zostaną pominięte, a w subkrotce wstawiona zostanie warotść
	 * zero (nullptr).
	 * Relacja zostnaie przekopiowana do nowej subkrotki.
	 *
	 * @see buildDifferenceMask
	 * @see DifferenceMask
	 */
	void				createSubtuple(
							DifferenceMask 	pMask,
							Tuple&			pResult) const;

	/**
	 * \brief Funkcja sprawdza czy krotki są częściowo podobne.
	 *
	 * Funkcja sprawdza wszystkie elementy obu krotek.
	 * Zwróci true tylko wtedy jeśli wszystkie elementy, których
	 * odpowiadające bity maski różnicy są równe 0 będą takie same
	 * w obu krotkach i jednoczeście wszystkie te elementy, dla
	 * których odpowiadające bity maski są równe 1 będą różne w obu
	 * krotkach.
	 * Relacja jest brana pod uwagę tylko jeśli parameter
	 * pConsiderRelation jest ustawiony na true.
	 * W innym wypadku relacja jest pomijana.
	 */
	bool isSimilar(
		Tuple const& 	pTuple,
		DifferenceMask 	pMask,
		bool			pConsiderRelation = true) const;

	/**
	 * \brief Funkcja sprawdza czy krotki są częściowo podobne.
	 *
	 * Funkcja sprawdza wszystkie elementy krotek, którym
	 * odpowiadające bity maski różnicy są równe 0 (w granicach
	 * krotki).
	 * Jeśli każdy z rozpatrywancyh elementów (0 w masce) będzie
	 * taki sam w obu krotkach to funkcja zwraca true.
	 * Elementy, dla których odpowiadające wartości bitowe maski są
	 * równe 1 są pomijane w procesie sprawdzania podobieństwa
	 * krotek.
	 * Relacja jest brana pod uwagę tylko jeśli parameter
	 * pConsiderRelation jest ustawiony na true.
	 * W innym wypadku relacja jest pomijana.
	 */
	bool isPartiallyEqual(
		Tuple const& 	pTuple,
		DifferenceMask 	pMask,
		bool			pConsiderRelation = true) const;

	bool hasSameSize(Tuple const& pTuple) 		const;
	bool hasSameRelation(Tuple const& pTuple) 	const;
	bool hasSameElements(Tuple const& pTuple)	const;

	bool operator==(Tuple const& pTuple) 	const;
	bool operator!=(Tuple const& pTuple) 	const;
	bool operator>(Tuple const& pTuple)		const;
	bool operator<(Tuple const& pTuple)		const;
	bool operator>=(Tuple const& pTuple)	const;
	bool operator<=(Tuple const& pTuple)	const;


private:
	mutable FrequencyStorage	mMetadata;
	Container 					mElements;
	RelationType				mRelation;
};


template <typename E, typename R, typename C>
std::ostream& operator<<(std::ostream& pStream, Tuple<E, R, C> const& pTuple)
{
	pStream << pTuple.mRelation << '\t' << pTuple.mElements.size();
	for (size_t i = 0; i < pTuple.mElements.size(); ++i)
	{
		pStream << '\t' << pTuple.mElements[i];
	}
	return (pStream << '\t' << pTuple.mMetadata.getGlobalFrequency());
}


template <typename ElementType, typename RelationType, typename Container>
Tuple<ElementType, RelationType, Container>::Tuple(
	size_t 			pSize,
	RelationType	pRelation,
	double 			pFrequency,
	size_t			pSources)
:
	mMetadata(pFrequency, pSources),
	mElements(pSize),
	mRelation(pRelation)
{

}


template <typename ElementType, typename RelationType, typename Container>
Tuple<ElementType, RelationType, Container>::Tuple(
	Container const& 	pContainer,
	RelationType		pRelation,
	double 				pFrequency,
	size_t				pSources)
:
	mMetadata(pFrequency, pSources),
	mElements(pContainer),
	mRelation(pRelation)
{

}


template <typename ElementType, typename RelationType, typename Container>
Container const& Tuple<ElementType, RelationType, Container>::getElements() const
{
	return mElements;
}


template <typename ElementType, typename RelationType, typename Container>
ElementType Tuple<ElementType, RelationType, Container>::getElementCopy(size_t pIndex) const
{
	return mElements[pIndex];
}


template <typename ElementType, typename RelationType, typename Container>
ElementType const& Tuple<ElementType, RelationType, Container>::getElement(size_t pIndex) const
{
	return mElements[pIndex];
}


template <typename ElementType, typename RelationType, typename Container>
ElementType& Tuple<ElementType, RelationType, Container>::getElement(size_t pIndex)
{
	return mElements[pIndex];
}


template <typename ElementType, typename RelationType, typename Container>
RelationType Tuple<ElementType, RelationType, Container>::getRelationCopy() const
{
	return mRelation;
}


template <typename ElementType, typename RelationType, typename Container>
RelationType const& Tuple<ElementType, RelationType, Container>::getRelation() const
{
	return mRelation;
}


template <typename ElementType, typename RelationType, typename Container>
RelationType& Tuple<ElementType, RelationType, Container>::getRelation()
{
	return mRelation;
}


template <typename ElementType, typename RelationType, typename Container>
FrequencyStorage& Tuple<ElementType, RelationType, Container>::getMetadata() const
{
	return mMetadata;
}


template <typename ElementType, typename RelationType, typename Container>
size_t Tuple<ElementType, RelationType, Container>::size() const
{
	return mElements.size();
}


template <typename ElementType, typename RelationType, typename Container>
size_t Tuple<ElementType, RelationType, Container>::subtupleCount() const
{
	return (1 << mElements.size());
}


template <typename ElementType, typename RelationType, typename Container>
void Tuple<ElementType, RelationType, Container>::setElement(
	size_t 				pIndex,
	ElementType const& 	pElement)
{
	mElements[pIndex] = pElement;
}


template <typename ElementType, typename RelationType, typename Container>
void Tuple<ElementType, RelationType, Container>::setRelation(RelationType const& pRelation)
{
	mRelation = pRelation;
}


template <typename ElementType, typename RelationType, typename Container>
ElementType const& Tuple<ElementType, RelationType, Container>::operator[](size_t pIndex) const
{
	return mElements[pIndex];
}


template <typename ElementType, typename RelationType, typename Container>
ElementType& Tuple<ElementType, RelationType, Container>::operator[](size_t pIndex)
{
	return mElements[pIndex];
}


/*
 *	Creates difference mask
 *	0 - elements are identical
 *	1 - elements are different
 *
 *	bits are set from right to left but words are considered from left to right
 *	in other words mask is reversed
 */
template <typename ElementType, typename RelationType, typename Container>
auto Tuple<ElementType, RelationType, Container>::buildDifferenceMask(Tuple const& pTuple) const -> DifferenceMask
{
	bool 			different 	= !hasSameSize(pTuple);
	DifferenceMask 	mask 		= 0;
	for (size_t i = 0; i < size(); ++i)
	{
		if(different || (getElementCopy(i) != pTuple.getElementCopy(i)))
		{
			mask |= (1 << i);
		}
	}
	return mask;
}


/*
 * Create tuple based on difference mask.
 * 0 - element will be copied from this tuple to pResult
 * 1 - element in pResult will be nullptr
 */
template <typename ElementType, typename RelationType, typename Container>
void Tuple<ElementType, RelationType, Container>::createSubtuple(
	DifferenceMask 	pMask,
	Tuple&			pResult) const
{
	pResult.setRelation(getRelation());

	for (size_t i = 0; i < size(); ++i)
	{
		if ((pMask & (1 << i)) > 0)
		{
			pResult[i] = nullptr;
		}
		else
		{
			pResult[i] = getElement(i);
		}
	}
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::isSimilar(
	Tuple const& 	pTuple,
	DifferenceMask 	pMask,
	bool			pConsiderRelation) const
{
	bool 			isok = (!pConsiderRelation) || (mRelation == pTuple.mRelation);
	DifferenceMask 	mask = 0x1;

	for (size_t i = 0; isok && (i < pTuple.size()); ++i)
	{
		isok =
			( ((pMask & mask) != 0) && (getElementCopy(i) != pTuple.getElementCopy(i)) ) ||
			( ((pMask & mask) == 0) && (getElementCopy(i) == pTuple.getElementCopy(i)) );
		mask <<= 1;
	}

	return isok;
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::isPartiallyEqual(
	Tuple const& 	pTuple,
	DifferenceMask 	pMask,
	bool			pConsiderRelation) const
{
	bool isok = (!pConsiderRelation) || (mRelation == pTuple.mRelation);
	DifferenceMask mask = 0x1;

	for (size_t i = 0; isok && (i < size()); ++i)
	{
		isok = ((pMask & mask) != 0) || (getElementCopy(i) == pTuple.getElementCopy(i));
		mask <<= 1;
	}

	return isok;
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::hasSameSize(Tuple const& pTuple) const
{
	return (mElements.size() == pTuple.mElements.size());
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::hasSameRelation(Tuple const& pTuple) const
{
	return (mRelation == pTuple.mRelation);
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::hasSameElements(Tuple const& pTuple) const
{
	bool eq = (size() == pTuple.size());
	for (size_t i = 0; (i < size()) && eq; ++i)
	{
		eq = (mElements[i] == pTuple.mElements[i]);
	}
	return eq;
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::operator==(Tuple const& pTuple) const
{
	return hasSameRelation(pTuple) && hasSameElements(pTuple);
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::operator!=(Tuple const& pTuple) const
{
	return !((*this) == pTuple);
}


// TODO Simplify this
template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::operator>(Tuple const& pTuple) const
{
	/*if (mRelation > pTuple.mRelation)
	{
		return true;
	}

	if (mRelation < pTuple.mRelation)
	{
		return false;
	}

	size_t min = std::min(mElements.size(), pTuple.size());
	for (size_t i = 0; i < min; ++i)
	{
		if (mElements[i] < pTuple[i])
		{
			return false;
		}
		if (mElements[i] > pTuple[i])
		{
			return true;
		}
	}
	return mElements.size() > pTuple.size();*/

	size_t min = std::min(mElements.size(), pTuple.size());
	for (size_t i = 0; i < min; ++i)
	{
		if (mElements[i] < pTuple[i])
		{
			return false;
		}
		if (mElements[i] > pTuple[i])
		{
			return true;
		}
	}

	if (mElements.size() > pTuple.size())
	{
		return true;
	}
	if (mElements.size() < pTuple.size())
	{
		return false;
	}

	return (mRelation > pTuple.mRelation);
}


// TODO Simplify this
template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::operator<(Tuple const& pTuple) const
{
	/*if (mRelation < pTuple.mRelation)
	{
		return true;
	}

	if (mRelation > pTuple.mRelation)
	{
		return false;
	}

	size_t min = std::min(mElements.size(), pTuple.size());
	for (size_t i = 0; i < min; ++i)
	{
		if (mElements[i] > pTuple[i])
		{
			return false;
		}
		if (mElements[i] < pTuple[i])
		{
			return true;
		}
	}
	return mElements.size() < pTuple.size();*/

	size_t min = std::min(mElements.size(), pTuple.size());
	for (size_t i = 0; i < min; ++i)
	{
		if (mElements[i] > pTuple[i])
		{
			return false;
		}
		if (mElements[i] < pTuple[i])
		{
			return true;
		}
	}

	if (mElements.size() < pTuple.size())
	{
		return true;
	}
	if (mElements.size() > pTuple.size())
	{
		return false;
	}

	return (mRelation < pTuple.mRelation);
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::operator>=(Tuple const& pTuple) const
{
	return !((*this) < pTuple);
}


template <typename ElementType, typename RelationType, typename Container>
bool Tuple<ElementType, RelationType, Container>::operator<=(Tuple const& pTuple) const
{
	return !((*this) > pTuple);
}


	}
}


namespace std
{

// Improve hash (change addition to... sth)
template <typename ElementType, typename RelationType, typename Container>
struct hash<structure::storage::Tuple<ElementType, RelationType, Container>>
{
	typedef structure::storage::Tuple<ElementType, RelationType, Container> __Tuple;

	size_t operator()(__Tuple const& pTuple) const
	{
		size_t 				hashValue = hash<RelationType>()(pTuple.getRelation());
		hash<ElementType>	hasher;

		for (size_t i = 0; i < pTuple.size(); ++i)
		{
			hashValue += hasher(pTuple.getElement(i));
		}

		return hashValue;
	}
};


}
