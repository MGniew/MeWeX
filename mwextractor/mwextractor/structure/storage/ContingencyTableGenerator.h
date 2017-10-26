
#pragma once

#include <map>

#include "ContingencyTableSource.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Generator tablic wielodzielnych.
 *
 * Zadaniem tej klasy jest generowanie tablic wielodzielnych (Contingency Table)
 * na podstawie danych ze składu krotek według określonej polityki ich tworzenia.
 * Generator tworzy tablice na bieżąco i za każdym razem na nowo.
 *
 * @see ContingencyTable
 */
class ContingencyTableGenerator : public ContingencyTableSource
{
public:
	typedef MatrixTupleStorage::TupleT TupleT;

	typedef std::set<TupleT>						Container;
	typedef std::pair<Container::iterator, bool>	InsertResult;

	typedef Container::const_iterator				ContainerIteratorConst;
	typedef Container::iterator						ContainerIterator;

	typedef std::pair<ContainerIteratorConst, ContainerIteratorConst> 	ContainerIteratorConstPair;
	typedef std::pair<ContainerIterator, ContainerIterator> 			ContainerIteratorPair;

	/**
	 * \brief Polityki tworzenia contingency table.
	 *
	 * Lista dostępnych polityk tworzenia contingecy table.
	 */
	enum class TableCreationPolicy
	{
		JOIN_NONE = 0,
		// JOIN_SAME_CONTENT,
		JOIN_SAME_SIZE_RELATIONS
	};

public:
	ContingencyTableGenerator(
		size_t				pTupleFrequencySum 		= 0,
		TableCreationPolicy pTableCreationPolicy 	= TableCreationPolicy::JOIN_SAME_SIZE_RELATIONS);

	ContingencyTableGenerator(ContingencyTableGenerator&& 					pContingencyTableGenerator) 	= default;
	ContingencyTableGenerator(ContingencyTableGenerator const& 				pContingencyTableGenerator) 	= delete;
	ContingencyTableGenerator& operator=(ContingencyTableGenerator&&	 	pContingencyTableGenerator) 	= default;
	ContingencyTableGenerator& operator=(ContingencyTableGenerator const& 	pContingencyTableGenerator) 	= delete;

	virtual ~ContingencyTableGenerator() = default;


	InsertResult				insert(TupleT&& pInsert);
	InsertResult				insert(TupleT const& pInsert);

	ContainerIteratorConst		find(TupleT const& pTupleT) const;
	ContainerIterator			find(TupleT const& pTupleT);

	bool						has(TupleT const& pTupleT) const;

	void						setTupleFrequencySum(double pTupleFrequencySum);

	/**
	 * \brief Funkcja tworzy contingency table
	 *
	 * Funkcja tworzy contingency table na podstawie danych
	 * zawartych w indeksie i określonej polityki tworzenia
	 * tej właśnie tablicy.
	 *
	 * @see TableCreationPolicy
	 */
	ContingencyTable 			createTable(TupleT const& pTupleT) const;

	virtual ContingencyTable 	constructTable(
									TupleId 						pTupleId,
									MatrixTupleStoragePtrS const&	pTupleStorage) const override;

	virtual ContingencyTable 	constructTable(
									TupleT const&					pTupleT,
									MatrixTupleStoragePtrS const&	pTupleStorage) const override;


	void						setTableCreationPolicy(TableCreationPolicy pTableCreationPolicy);
	TableCreationPolicy			getTableCreationPolicy() const;

	size_t						size() 	const;

	ContainerIteratorConst		begin() const;
	ContainerIterator			begin();
	ContainerIteratorConst		end() 	const;
	ContainerIterator			end();

	/**
	 * \brief Zwraca iterator na pierwszą krotkę zadaną argumentem
	 * bez względu na jej relację.
	 *
	 * Funkcja zwraca iterator na pierwszą krotkę, która ma
	 * identyczne elementy co krotka zadana argumentem, ale
	 * dowolną relację.
	 * Funkcja może zwrócić end (brak krotki) jeśli nie znajdzie
	 * zadanej krotki w żadej z relacji.
	 * Funkcja razem z endForAnyRelation pozwala szybko
	 * przeiterować krotki mające te same elementy,
	 * ale różne relacje.
	 *
	 * @see endForAnyRelation
	 */
	ContainerIteratorConst		beginForAnyRelation(TupleT pTuple) const;
	ContainerIterator			beginForAnyRelation(TupleT pTuple);

	/**
	 * \brief Zwraca iterator na krotkę po tej zadanej
	 * argumentem, bez względu na relacje.
	 *
	 * Funkcja zwraca iterator na następną po ostatniej krotce,
	 * która ma identyczne elementy co krotka zadana argumentem,
	 * ale dowolną relację.
	 * Funkcja może zwrócić end (brak krotki) jeśli nie znajdzie
	 * zadanej krotki w żadej z relacji lub trafi na krotkę znajdującą się na
	 * końcu kontenera.
	 * Funkcja razem z beginForAnyRelation pozwala szybko
	 * przeiterować krotki mające te same elementy,
	 * ale różne relacje.
	 *
	 * @see beginForAnyRelation
	 */
	ContainerIteratorConst		endForAnyRelation(TupleT pTuple) const;
	ContainerIterator			endForAnyRelation(TupleT pTuple);


	ContainerIteratorConstPair	range(TupleT pTuple) const;
	ContainerIteratorPair		range(TupleT pTuple);


private:
	ContingencyTable createTableJoinNoneRelations(TupleT const& pTupleT) 		const;
	ContingencyTable createTableJoinSameSizeRelations(TupleT const& pTupleT) 	const;

private:
	Container 			mContainer;
	double				mTupleFrequencySum;
	TableCreationPolicy	mTableCreationPolicy;
};


	}
}
