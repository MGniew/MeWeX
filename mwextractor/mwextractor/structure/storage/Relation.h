
#pragma once

#include "FrequencyStorage.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Klasa przechowująca opis relacji i jej częstości.
 *
 * Klasa przechowuje opis relacji (np. tekst) oraz
 * informacje o liczbie wystąpień tej relacji w badancyh
 * źródłach.
 *
 * @see FrequencyStorage
 */
template <typename RelationType>
class Relation {
public:
	template <typename T>
	friend std::ostream& operator<<(std::ostream& pStream, Relation<T> const& pRelation);

public:
	/**
	 * \brief Konstruktor tworzący relacje o zadanej
	 * nazwie.
	 *
	 * @param pName nazwa relacji.
	 * @param pArity rozmiar krotki, liczba elementów, które są opisywane przez relację.
	 * @param pFrequency częstość relacji.
	 * @param pSources liczba źródeł relacji.
	 *
	 * @see FrequencyStorage
	 */
	Relation(
		size_t				pGroup,
		RelationType const& pName,
		size_t				pArity,
		size_t				pFrequency,
		size_t				pSources);

	Relation(Relation&& 				pRelation) = default;
	Relation(Relation const& 			pRelation) = default;
	Relation& operator=(Relation&&	 	pRelation) = default;
	Relation& operator=(Relation const& pRelation) = default;

	~Relation() = default;


	size_t				getGroup()		const;

	RelationType const& getName() 		const;
	RelationType& 		getName();

	/**
	 * \brief Zwraca arność krotki.
	 *
	 * Arność oznacza liczbę elementów, które dana
	 * relacja bierze pod uwagę (są przez nią opisywane).
	 */
	size_t				getArity() 		const;

	FrequencyStorage&	getMetadata()	const;


	void setName(RelationType const& pName);


	bool operator==(Relation const& pRelation) 	const;
	bool operator!=(Relation const& pRelation) 	const;
	bool operator>(Relation const& pRelation) 	const;
	bool operator<(Relation const& pRelation) 	const;
	bool operator>=(Relation const& pRelation) 	const;
	bool operator<=(Relation const& pRelation) 	const;


private:
	mutable	FrequencyStorage	mMetadata;
	size_t						mGroup;
	RelationType 				mName;
	size_t						mArity;
};


template <typename T>
std::ostream& operator<<(std::ostream& pStream, Relation<T> const& pRelation)
{
	return (pStream << pRelation.mGroup << '\t' << pRelation.mName << '\t' << pRelation.mArity << '\t' << pRelation.mMetadata.frequency);
}


template <typename RelationType>
Relation<RelationType>::Relation(
	size_t				pGroup,
	RelationType const& pName,
	size_t				pArity,
	size_t				pFrequency,
	size_t				pSources)
:
	mMetadata(pFrequency, pSources),
	mGroup(pGroup),
	mName(pName),
	mArity(pArity)
{

}


template <typename RelationType>
size_t Relation<RelationType>::getGroup() const
{
	return mGroup;
}


template <typename RelationType>
RelationType const& Relation<RelationType>::getName() const
{
	return mName;
}


template <typename RelationType>
RelationType& Relation<RelationType>::getName()
{
	return mName;
}


template <typename RelationType>
size_t Relation<RelationType>::getArity() const
{
	return mArity;
}


template <typename RelationType>
FrequencyStorage& Relation<RelationType>::getMetadata() const
{
	return mMetadata;
}


template <typename RelationType>
void Relation<RelationType>::setName(RelationType const& pName)
{
	mName = pName;
}


template <typename RelationType>
bool Relation<RelationType>::operator==(Relation const& pRelation) const
{
	/*return
		(mMetadata.arity 	== pRelation.mMetadata.arity) &&
		(mName 				== pRelation.mName);*/
	return mName == pRelation.mName;
}


template <typename RelationType>
bool Relation<RelationType>::operator!=(Relation const& pRelation) const
{
	return !((*this) == pRelation);
}


template <typename RelationType>
bool Relation<RelationType>::operator>(Relation const& pRelation) const
{
	/*return
		(mMetadata.arity	> pRelation.mMetadata.arity) ||
		(mName 				> pRelation.mName);*/
	return mName > pRelation.mName;
}


template <typename RelationType>
bool Relation<RelationType>::operator<(Relation const& pRelation) const
{
	/*return
		(mMetadata.arity	< pRelation.mMetadata.arity) ||
		(mName 				< pRelation.mName);*/
	return mName < pRelation.mName;
}


template <typename RelationType>
bool Relation<RelationType>::operator>=(Relation const& pRelation) const
{
	return !((*this) < pRelation);
}


template <typename RelationType>
bool Relation<RelationType>::operator<=(Relation const& pRelation) const
{
	return !((*this) > pRelation);
}


	}
}


namespace std
{
	template <typename T>
	struct hash<structure::storage::Relation<T>>
	{
		typedef structure::storage::Relation<T> __Relation;

		size_t operator()(__Relation const& pRelation) const
		{
			return std::hash<T>()(pRelation.getName());
		}
	};
}
