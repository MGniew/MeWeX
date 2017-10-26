/*
 * FastSetStorage.h
 *
 *  Created on: 08-07-2014
 *      Author: michalw
 */

#pragma once

#include <unordered_set>

#include "../utils/Debug.h"
#include "../exception/Exception.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Implementacja szybkiego kontenera indeksującego
 * dwustronnie przy zachowaniu oszczędności pamięci.
 *
 * Klasa stworzona z myślą o składowniu dużej ilości
 * danych przy jednoczesnym zapewnieniu szybkiego dostępu
 * do zawartych w niej danych.
 * Klasa jest dwustronnym indeksem - szybki dostęp do
 * zawartych w niej obiektów zarówno przez wartość jak
 * i przez identyfikator unikalny dla każdego obiektu.
 * Klasa bazuje na konterze typu unordered_set -
 * zestaw hashowalny, ale ze względy na zastosowanie
 * szablonu można zmienić go na zwykły set (drzewo) jeśli
 * wymagane jest zachowanie kolejności elementów
 * składowych.
 * Klasa zapewnia szybki dostęp do elementów w niej
 * składowanych zarówno przez wartość (w zależności od
 * zasosowanego kontenera - domyślnie O(1), hash) jak i
 * przez identyfikator (zawsze szybkie O(1)).
 * Zużycie pamięci zostało zmniejszone dzięki nie
 * tworzeniu struktur do podtrzymywania indeksu
 * odwrotnego poprzez wykorzystanie wskaźników, które
 * są od razu identyfikatorami obiektów zawartych w
 * tej strukturze.
 * Wykorzystanie wskaźników zapewnia brak problemów
 * z rozmiarem zmiennej określającej identyfikator
 * oraz pomija konieczność własnoręcznego zarządzania
 * identyfikatorami.
 */
template <typename Type, typename Container = std::unordered_set<Type>>
class FastSetStorage {
public:
	typedef Type								Object;
	typedef Object const* 						ObjectId;

	typedef typename Container::iterator		ContainerIterator;
	typedef typename Container::const_iterator	ContainerIteratorConst;
	typedef std::pair<ContainerIterator, bool> 	AddResult;

public:
	FastSetStorage()												= default;
	FastSetStorage(FastSetStorage&& 					pMapping) 	= default;
	FastSetStorage(FastSetStorage const& 				pMapping) 	= delete;
	FastSetStorage& operator=(FastSetStorage&& 			pMapping)	= default;
	FastSetStorage& operator=(FastSetStorage const& 	pMapping)	= delete;

	virtual ~FastSetStorage() = default;


	Container const&		getContainer() const;
	Container&				getContainer();

	size_t					size()		const;

	ObjectId 				findObjectId(ContainerIteratorConst const& pIterator)	const;
	ObjectId 				findObjectId(Object const& pObject) 					const;
	ObjectId 				findObjectIdSilent(Object const& pObject)				const;

	Object const&			findObject(ContainerIteratorConst const& pIterator)		const;
	Object const&			findObject(ObjectId pObjectId) 							const;
	Object					findAndCopyObject(ObjectId pObjectId)					const;

	AddResult				addObjectGetResult(Object&& pObject);
	AddResult				addObjectGetResult(Object const& pObject);
	bool 					addObject(Object&& pObject);
	bool 					addObject(Object const& pObject);
	ObjectId 				addObjectGetId(Object&& pObject);
	ObjectId 				addObjectGetId(Object const& pObject);

	void					removeObject(Object const& 	pObject);
	void					removeObject(ObjectId		pObjectId);


	ContainerIteratorConst	begin() 	const;
	ContainerIterator		begin();
	ContainerIteratorConst	end() 		const;
	ContainerIterator		end();


private:
	Container mObjects;
};


template <typename Type, typename Container>
Container const& FastSetStorage<Type, Container>::getContainer() const
{
	return mObjects;
}


template <typename Type, typename Container>
Container& FastSetStorage<Type, Container>::getContainer()
{
	return mObjects;
}


template <typename Type, typename Container>
size_t FastSetStorage<Type, Container>::size() const
{
	return mObjects.size();
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::findObjectId(ContainerIteratorConst const& pIterator)	const -> ObjectId
{
	return &(*pIterator);
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::findObjectId(Object const& pObject) const -> ObjectId
{
	auto i = mObjects.find(pObject);
	XASSERT(i != mObjects.end(), "FastSetStorage<Type, Container>::findObjectId(): object not found.");
	return findObjectId(i);
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::findObjectIdSilent(Object const& pObject) const -> ObjectId
{
	auto i = mObjects.find(pObject);
	if (i == mObjects.end())
	{
		return nullptr;
	}
	return findObjectId(i);
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::findObject(ContainerIteratorConst const& pIterator) const -> Object const&
{
	return *pIterator;
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::findObject(ObjectId pObjectId) const -> Object const&
{
	XASSERT(pObjectId != nullptr, "FastSetStorage<Type, Container>::findObject(): Null object id passed as argument.");
	return *pObjectId;
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::findAndCopyObject(ObjectId pObjectId) const -> Object
{
	return findObject(pObjectId);
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::addObjectGetResult(Object&& pObject) -> AddResult
{
	return mObjects.insert(std::forward<Type>(pObject));
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::addObjectGetResult(Object const& pObject) -> AddResult
{
	return mObjects.insert(pObject);
}


template <typename Type, typename Container>
bool FastSetStorage<Type, Container>::addObject(Object&& pObject)
{
	return mObjects.insert(std::forward<Type>(pObject)).second;
}


template <typename Type, typename Container>
bool FastSetStorage<Type, Container>::addObject(Object const& pObject)
{
	return mObjects.insert(pObject).second;
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::addObjectGetId(Object&& pObject) -> ObjectId
{
	/* Should be fast because it try to find object id using an iterator */
	return findObjectId(mObjects.insert(std::forward<Type>(pObject)).first);
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::addObjectGetId(Object const& pObject) -> ObjectId
{
	/* Should be fast because it try to find object id using an iterator */
	return findObjectId(mObjects.insert(pObject).first);
}


template <typename Type, typename Container>
void FastSetStorage<Type, Container>::removeObject(Object const& pObject)
{
	mObjects.erase(pObject);
}


template <typename Type, typename Container>
void FastSetStorage<Type, Container>::removeObject(ObjectId pObjectId)
{
	removeObject(findObject(pObjectId));
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::begin() const -> ContainerIteratorConst
{
	return mObjects.begin();
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::begin() -> ContainerIterator
{
	return mObjects.begin();
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::end() const -> ContainerIteratorConst
{
	return mObjects.end();
}


template <typename Type, typename Container>
auto FastSetStorage<Type, Container>::end() -> ContainerIterator
{
	return mObjects.end();
}


	}
}
