
#pragma once

#include <memory>
#include <unordered_set>


namespace structure
{


template <typename T, typename C = std::unordered_set<T>>
class RelevantObjectSet
{
public:
	typedef typename C::const_iterator 				IteratorConst;
	typedef typename C::iterator 					Iterator;

	typedef std::pair<Iterator, Iterator>			IteratorPair;
	typedef std::pair<IteratorConst, IteratorConst>	IteratorConstPair;

	typedef RelevantObjectSet<T, C> 				MyType;
	typedef std::shared_ptr<MyType>					MyTypePtrS;

public:
	RelevantObjectSet(size_t pSourceSize = 0);

	RelevantObjectSet(RelevantObjectSet&& 					pRelevantSet)	= default;
	RelevantObjectSet(RelevantObjectSet const& 				pRelevantSet)	= delete;
	RelevantObjectSet& operator=(RelevantObjectSet&&		pRelevantSet)	= default;
	RelevantObjectSet& operator=(RelevantObjectSet const& 	pRelevantSet)	= delete;

	~RelevantObjectSet() = default;


	void 				insert(T&& 		pObject);
	void				insert(T const& pObject);

	IteratorConst		find(T const& pObject) const;
	Iterator			find(T const& pObject);

	bool 				has(T const& pObject) const;

	void 				erase(T const& pObject);

	void 				setSourceSize(size_t pSourceSize);

	/**
	 * \brief Liczba krotek zawartych w tym zbiorze.
	 */
	size_t 				size() 			const;

	/**
	 * \brief Liczba krotek wczytanych z pliku zawierającego jednostki uznane za wielowyrazowe.
	 */
	size_t 				sourceSize()	const;

	IteratorConst 		begin() const;
	Iterator 			begin();
	IteratorConst 		end() 	const;
	Iterator 			end();

	IteratorConstPair	range(T const& pObject) const;
	IteratorPair		range(T const& pObject);


	/**
	 * \brief Tworzy podzestaw relevantych krotek.
	 *
	 * Funkcja tworzy podzestaw relevantych krotek poprzez,
	 * wykonanie operacji przecięcia zbiorów z listą
	 * obiektów zadanych argumentem.
	 */
	template <typename DC>
	MyTypePtrS 			subset(DC const& pContainer) const;


private:
	C	 	mRelevantSet;
	size_t	mSourceSize;
};


template <typename T, typename C>
RelevantObjectSet<T, C>::RelevantObjectSet(size_t pSourceSize)
:
	mSourceSize(pSourceSize)
{

}


template <typename T, typename C>
void RelevantObjectSet<T, C>::insert(T&& pObject)
{
	mRelevantSet.insert(std::forward<T>(pObject));
}


template <typename T, typename C>
void RelevantObjectSet<T, C>::insert(T const& pObject)
{
	mRelevantSet.insert(pObject);
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::find(T const& pObject) const -> IteratorConst
{
	return mRelevantSet.find(pObject);
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::find(T const& pObject) -> Iterator
{
	return mRelevantSet.find(pObject);
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::range(T const& pObject) const -> IteratorConstPair
{
	return mRelevantSet.equal_range(pObject);
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::range(T const& pObject) -> IteratorPair
{
	return mRelevantSet.equal_range(pObject);
}


template <typename T, typename C>
bool RelevantObjectSet<T, C>::has(T const& pObject) const
{
	return mRelevantSet.find(pObject) != mRelevantSet.end();
}


template <typename T, typename C>
void RelevantObjectSet<T, C>::erase(T const& pObject)
{
	return mRelevantSet.erase(pObject);
}


template <typename T, typename C>
void RelevantObjectSet<T, C>::setSourceSize(size_t pSourceSize)
{
	mSourceSize = pSourceSize;
}


template <typename T, typename C>
size_t RelevantObjectSet<T, C>::size() const
{
	return mRelevantSet.size();
}


template <typename T, typename C>
size_t RelevantObjectSet<T, C>::sourceSize() const
{
	return mSourceSize;
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::begin() const -> IteratorConst
{
	return mRelevantSet.begin();
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::begin() -> Iterator
{
	return mRelevantSet.begin();
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::end() const -> IteratorConst
{
	return mRelevantSet.end();
}


template <typename T, typename C>
auto RelevantObjectSet<T, C>::end() -> Iterator
{
	return mRelevantSet.end();
}


template <typename T, typename C>
template <typename DC>
auto RelevantObjectSet<T, C>::subset(DC const& pContainer) const -> MyTypePtrS
{
	MyTypePtrS subset(new MyType());
	for (auto iter = pContainer.begin(); iter != pContainer.end(); ++iter)
	{
		if (has(*iter))
		{
			subset->insert(*iter);
		}
	}
	subset->setSourceSize(subset->size());
	return subset;
}


}
