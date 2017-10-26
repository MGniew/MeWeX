
#pragma once

#include <string>
#include <unordered_set>

#include "Relation.h"
#include "../FastSetStorage.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Skład relacji.
 *
 * Obiekty tej klasy przechowują informacje o częściach mowy
 * pochodzących ze sparsowanych korpusów.
 *
 * @see Relation
 */
class RelationStorage
{
public:
	typedef Relation<std::string> 								RelationT;
	typedef FastSetStorage<RelationT>::ObjectId 				RelationId;
	typedef FastSetStorage<RelationT>::ContainerIteratorConst	RelationIteratorConst;
	typedef FastSetStorage<RelationT>::ContainerIterator		RelationIterator;

	typedef std::vector<RelationId>								RelationIdVector;
	typedef std::map<size_t, RelationIdVector>					RelationScheme;

private:
	typedef FastSetStorage<RelationT>::AddResult				AddResult;


public:
	RelationStorage()												= default;
	RelationStorage(RelationStorage&& 					pStorage) 	= default;
	RelationStorage(RelationStorage const& 				pStorage) 	= delete;
	RelationStorage& operator=(RelationStorage&&	 	pStorage)	= delete;
	RelationStorage& operator=(RelationStorage const& 	pStorage)	= delete;

	virtual ~RelationStorage() = default;


	size_t						getRelationCount()													const;

	RelationId 					findRelationId(RelationIteratorConst const& pIterator)				const;
	RelationId 					findRelationId(RelationT const& pRelation) 							const;
	RelationId					findRelationId(std::string const& pRelationName)					const;
	RelationId 					findRelationIdSilent(RelationT const& pRelation) 					const;
	RelationId					findRelationIdSilent(std::string const& pRelationName)				const;
	RelationId					findLongestRelationId()												const;

	RelationT const&			findRelation(RelationIteratorConst const& pIterator)				const;
	RelationT const&			findRelation(RelationId pRelationId) 								const;
	RelationT const&			findRelation(std::string pRelationName)								const;
	RelationT					findAndCopyRelation(RelationId pRelationId)							const;
	RelationT					findLongestRelation()												const;

	bool 						addRelation(RelationT&& pRelation);
	bool 						addRelation(RelationT const& pRelation);
	RelationId 					addRelationGetId(RelationT&& pRelation);
	RelationId 					addRelationGetId(RelationT const& pRelation);

	void						recomputeRelationsGlobalFrequency();

	std::string					createRelationReprezentation(RelationT const& pRelation)			const;
	std::string					createRelationReprezentation(RelationId const& pRelationId)			const;

	std::string					extractRelationName(std::string const& pNameWithMeta)				const;

	RelationId					findRelationByReprezentation(std::string const& pRelationString) 	const;

	RelationT					parseRelationReprezentation(std::string const& pRelationString) 	const;


	RelationIteratorConst		beginRelations() 		const;
	RelationIterator			beginRelations();
	RelationIteratorConst		endRelations() 			const;
	RelationIterator			endRelations();

	RelationScheme				buildRelationScheme() 	const;


private:
	void updateFrequencies(
		RelationT const& pInsertedRelation,
		AddResult const& pResult);


private:
	FastSetStorage<RelationT> mRelations;
};


	}
}
