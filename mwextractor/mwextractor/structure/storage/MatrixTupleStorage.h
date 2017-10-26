
#pragma once

#include <set>
#include <unordered_map>
#include <memory>

#include "WordStorage.h"
#include "RelationStorage.h"
#include "CorporaStorage.h"
#include "Tuple.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Klasa podstawowa w procesach przetwarzania.
 *
 * Obiekty tej klasy przechowują pięć typów danych pozyskanych
 * ze sparsowanych korpusów tekstowych.
 * Pierwsza to części mowy słów, druga to słowa, trzecia to
 * metadane o korpusach, czwarta wykorzystane relacje -- operatory
 * WCCL oraz piąta -- wydobyte krotki.
 *
 * @see Corpus
 * @see Relation
 * @see PartOfSpeech
 * @see Word
 * @see Tuple
 *
 * @see CorporaStorage
 * @see RelationStorage
 * @see PartOfSpeechStorage
 * @see WordStorage
 */
class MatrixTupleStorage : public WordStorage, public RelationStorage, public CorporaStorage
{
public:
	typedef Tuple<WordT, RelationT>						DecodedTuple;
	typedef Tuple<WordId, RelationId>					TupleT;

	typedef FastSetStorage<TupleT, std::set<TupleT>>	FastTupleStorage;
	typedef FastTupleStorage::ObjectId 					TupleId;

	typedef FastTupleStorage::ContainerIteratorConst	TupleIteratorConst;
	typedef FastTupleStorage::ContainerIterator			TupleIterator;

	typedef std::pair<TupleIteratorConst, TupleIteratorConst> 	TupleIteratorConstPair;
	typedef std::pair<TupleIterator, TupleIterator> 			TupleIteratorPair;

	typedef std::vector<TupleId>						TupleIdVector;
	typedef std::unordered_set<WordId>					WordIdSet;
	typedef std::unordered_set<RelationId>				RelationIdSet;
	typedef std::unordered_set<TupleId>					TupleIdSet;

	typedef std::unordered_map<WordId, TupleIdVector>	TuplesByWordMap;
	typedef std::shared_ptr<TuplesByWordMap>			TuplesByWordMapPtrS;
	typedef std::vector<TuplesByWordMap>				TuplesByWordByPosition;
	typedef std::shared_ptr<TuplesByWordByPosition>		TuplesByWordByPositionPtrS;

	typedef std::unordered_map<TupleId, TupleIdVector>	TuplesByTupleMap;
	typedef std::shared_ptr<TuplesByTupleMap>			TuplesByTupleMapPtrS;


private:
	typedef FastTupleStorage::AddResult					AddResult;


public:
	MatrixTupleStorage();
	MatrixTupleStorage(MatrixTupleStorage&& 				pStorage) 	= default;
	MatrixTupleStorage(MatrixTupleStorage const& 			pStorage) 	= delete;
	MatrixTupleStorage& operator=(MatrixTupleStorage&&	 	pStorage)	= default;
	MatrixTupleStorage& operator=(MatrixTupleStorage const& pStorage)	= delete;

	virtual ~MatrixTupleStorage() = default;


	size_t					getDistinctTupleCount()										const;
	double					getTupleGlobalFrequency()									const;
	double 					getCorporaGlobalTupleFrequency(size_t pCorporaIndex)		const;

	void					setTupleGlobalFrequency(double pTupleGlobalFrequency);

	TupleId 				findTupleId(TupleIteratorConst const& pIterator)			const;
	TupleId 				findTupleId(TupleT const& pTuple) 							const;
	TupleId 				findTupleIdSilent(TupleT const& pTuple) 					const;
	TupleId 				findTupleIdAnyRelationSilent(TupleT const& pTuple) 			const;
	TupleId 				findTupleIdAnyRelation(TupleT const& pTuple) 				const;
	TupleIdVector			findTupleIdsAllRelations(TupleT const& pTuple) 				const;

	TupleT const&			findTuple(TupleIteratorConst const& pIterator)				const;
	TupleT const&			findTuple(TupleId pTupleId) 								const;
	TupleT					findAndCopyTuple(TupleId pTupleId)							const;

	void					removeTuple(TupleId pTupleId);

	bool 					addTuple(TupleT&& pTuple);
	bool 					addTuple(TupleT const& pTuple);
	TupleId 				addTupleGetId(TupleT&& pTuple);
	TupleId 				addTupleGetId(TupleT const& pTuple);

	TupleIdVector			retrieveTupleIdVector()										const;

	void					recomputeTuplesGlobalFrequency();

	std::string				createTupleReprezentation(TupleT const& pTuple)				const;
	std::string				createTupleReprezentation(TupleId const& pTupleId)			const;

	TupleId					parseTupleReprezentation(std::string const& pTupleString)	const;

	std::string				createTupleWordChain(TupleT const& pTuple)					const;
	std::string				createTupleWordChain(TupleId const& pTupleId)				const;

	std::string				createTuplePosWordChain(TupleT const& pTuple)				const;
	std::string				createTuplePosWordChain(TupleId const& pTupleId)			const;

	TupleIteratorConst		beginTuples() 	const;
	TupleIterator			beginTuples();
	TupleIteratorConst		endTuples() 	const;
	TupleIterator			endTuples();

	TupleIteratorConst 		beginTuplesForAnyRelation(TupleT pTuple) 	const;
	TupleIterator 			beginTuplesForAnyRelation(TupleT pTuple);
	TupleIteratorConst 		endTuplesForAnyRelation(TupleT pTuple) 		const;
	TupleIterator			endTuplesForAnyRelation(TupleT pTuple);

	TupleIteratorConstPair	range(TupleT pTuple) const;
	TupleIteratorPair		range(TupleT pTuple);

	TuplesByWordMapPtrS 		buildTupleByWordMapping() 			const;
	TuplesByWordByPositionPtrS	buildTupleByWordByPositionMapping()	const;
	TuplesByTupleMapPtrS 		buildTupleByTupleMapping() 			const;


private:
	void updateFrequencies(
		TupleT const& 		pInsertedTuple,
		AddResult const& 	pResult);

	void subtractFrequencies(TupleT const& pTuple);


private:
	FastTupleStorage mTuples;
	FrequencyStorage mCorporaGlobalTupleFrequency;
};


	}
}
