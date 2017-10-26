
#pragma once

#include <map>
#include <vector>

#include "../../utils/Debug.h"
#include "../../utils/Types.h"
#include "SingleIterator.h"


namespace structure
{
	namespace container
	{


/*
 * \brief Skompresowany wektor.
 *
 * Obiekt klasy ma imitować wektor, ale w wersji skompresowanej.
 * Ma zachowywać kolejność wartości oraz redukować zużycie pamięci.
 * Wykorzystana została mapa standardowa, w której nie są przechowywane
 * elementy o wartości domyślnej (domyślnie 0).
 * Obiekt klasy redukuje złożoność pamięciową w przypadku, gdy wśród
 * wartości w nim przechowywanych często występuje wartość domyślna.
 * Zastosowanie mapy pozwala zachować kolejność i umożliwić dość szybki
 * dostęp do konkretnych elementów.
 */
template <typename T, T D = 0, typename CT = std::map<size_t, T>>
class CompressedVector
{
public:
	typedef typename CT::iterator												Iterator;
	typedef typename CT::const_iterator											IteratorConst;

	typedef SingleIterator<Iterator, T, SecondValueGetter<size_t, T>>			ValueIterator;
	typedef SingleIterator<IteratorConst, T, SecondValueGetter<size_t, T>> 		ValueIteratorConst;

	typedef SingleIterator<Iterator, size_t, FirstValueGetter<size_t, T>>		IndexIterator;
	typedef SingleIterator<IteratorConst, size_t, FirstValueGetter<size_t, T>> 	IndexIteratorConst;

	typedef std::vector<T>														UncompressedVector;

private:
	typedef std::pair<size_t, T> __Insert;


public:
	CompressedVector(size_t pSize = 0);

	CompressedVector(CompressedVector&& 				pCompressedVector)	= default;
	CompressedVector(CompressedVector const& 			pCompressedVector)	= default;
	CompressedVector& operator=(CompressedVector&& 		pCompressedVector)	= default;
	CompressedVector& operator=(CompressedVector const& pCompressedVector)	= default;

	~CompressedVector() = default;


	T 		get(size_t pIndex) 	const;

	void	set(size_t pIndex, T const& pValue);
	void	set(size_t pIndex, T&& 		pValue);

	void 	add(size_t pIndex, T const& pValue);

	T 		operator[](size_t pIndex) const;

	size_t 	size() 				const;
	size_t 	sizeNonDefault()	const;


	void				resize(size_t pNewSize);

	UncompressedVector 	uncompress() const;


	ValueIteratorConst 	beginValues()	const;
	ValueIterator 		beginValues();
	ValueIteratorConst 	endValues()		const;
	ValueIterator 		endValues();

	IndexIteratorConst 	beginIndices()	const;
	IndexIterator 		beginIndices();
	IndexIteratorConst 	endIndices()	const;
	IndexIterator 		endIndices();

	IteratorConst 		begin()	const;
	Iterator 			begin();
	IteratorConst 		end()	const;
	Iterator 			end();

private:
	CT 		mContainer;
	size_t	mSize;
};


/*
 *	Implementation
 */
template <typename T, T D, typename CT>
CompressedVector<T, D, CT>::CompressedVector(size_t pSize)
:
	mSize(pSize)
{

}


template <typename T, T D, typename CT>
T CompressedVector<T, D, CT>::get(size_t pIndex) const
{
	auto ret = mContainer.find(pIndex);
	return ret == mContainer.end() ? D : ret->second;
}


template <typename T, T D, typename CT>
void CompressedVector<T, D, CT>::set(size_t pIndex, T const& pValue)
{
	if (pValue != D)
	{
		mContainer[pIndex] = pValue;
	}
	else
	{
		mContainer.erase(pIndex);
	}
}


template <typename T, T D, typename CT>
void CompressedVector<T, D, CT>::set(size_t pIndex, T&& pValue)
{
	if (pValue != D)
	{
		mContainer[pIndex] = pValue;
	}
	else
	{
		mContainer.erase(pIndex);
	}
}


template <typename T, T D, typename CT>
void CompressedVector<T, D, CT>::add(size_t pIndex, T const& pValue)
{
	set(pIndex, get(pIndex) + pValue);
}


template <typename T, T D, typename CT>
T CompressedVector<T, D, CT>::operator[](size_t pIndex) const
{
	return get(pIndex);
}


template <typename T, T D, typename CT>
size_t CompressedVector<T, D, CT>::size() const
{
	return mSize;
}


template <typename T, T D, typename CT>
size_t CompressedVector<T, D, CT>::sizeNonDefault() const
{
	return mContainer.size();
}


template <typename T, T D, typename CT>
void CompressedVector<T, D, CT>::resize(size_t pNewSize)
{
	if (pNewSize < mSize)
	{
		for (auto i = begin(); i != end();)
		{
			if (i->first >= pNewSize)
			{
				i = mContainer.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	mSize = pNewSize;
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::uncompress() const -> UncompressedVector
{
	UncompressedVector vector(mSize, D);

	for (auto i = begin(); i != end(); ++i)
	{
		vector[i->first] = i->second;
	}

	return vector;
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::beginValues() const -> ValueIteratorConst
{
	return ValueIteratorConst(mContainer.begin());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::beginValues() -> ValueIterator
{
	return ValueIterator(mContainer.begin());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::endValues() const -> ValueIteratorConst
{
	return ValueIteratorConst(mContainer.end());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::endValues() -> ValueIterator
{
	return ValueIterator(mContainer.end());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::beginIndices() const -> IndexIteratorConst
{
	return IndexIteratorConst(mContainer.begin());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::beginIndices() -> IndexIterator
{
	return IndexIterator(mContainer.begin());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::endIndices() const -> IndexIteratorConst
{
	return IndexIteratorConst(mContainer.end());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::endIndices() -> IndexIterator
{
	return IndexIterator(mContainer.end());
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::begin() const -> IteratorConst
{
	return mContainer.begin();
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::begin() -> Iterator
{
	return mContainer.begin();
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::end() const -> IteratorConst
{
	return mContainer.end();
}


template <typename T, T D, typename CT>
auto CompressedVector<T, D, CT>::end() -> Iterator
{
	return mContainer.end();
}


	}
}


/*
 * Hash function for CompressedVector, umm... should be improved.
 */
namespace std
{

template <typename ET>
struct hash<structure::container::CompressedVector<ET>>
{
	typedef structure::container::CompressedVector<ET> __CV;

	size_t operator()(__CV const& pCv) const
	{
		hash<ET>	hasher;
		size_t		hashval = 0;
		for (auto i = pCv.begin(); i != pCv.end(); ++i)
		{
			hashval += hasher(i->second);
		}
		return hashval;
	}
};

}
