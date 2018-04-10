
#include <sstream>

#include "../../utils/Math.h"
#include "../../utils/Textual.h"
#include "../../utils/Debug.h"
#include "MatrixTupleStorage.h"


namespace structure
{
	namespace storage
	{



MatrixTupleStorage::MatrixTupleStorage()
:
	WordStorage(),
	RelationStorage()
{

}


size_t MatrixTupleStorage::getDistinctTupleCount() const
{
	return mTuples.size();
}


double MatrixTupleStorage::getTupleGlobalFrequency() const
{
	return mCorporaGlobalTupleFrequency.getGlobalFrequency();
}


double MatrixTupleStorage::getCorporaGlobalTupleFrequency(size_t pCorporaIndex) const
{
	XASSERT(
		pCorporaIndex < mCorporaGlobalTupleFrequency.getSourceCount(),
		"MatrixTupleStorage::getTupleCorporaFrequency(): No such corpora " << pCorporaIndex << '.');
	return mCorporaGlobalTupleFrequency.getLocalFrequency(pCorporaIndex);
}


void MatrixTupleStorage::setTupleGlobalFrequency(double pTupleGlobalFrequency)
{
	mCorporaGlobalTupleFrequency.setGlobalFrequency(pTupleGlobalFrequency);
}


auto MatrixTupleStorage::findTupleId(TupleIteratorConst const& pIterator) const -> TupleId
{
	return mTuples.findObjectId(pIterator);
}


auto MatrixTupleStorage::findTupleId(TupleT const& pTuple) const -> TupleId
{
	return mTuples.findObjectId(pTuple);
}


auto MatrixTupleStorage::findTupleIdSilent(TupleT const& pTuple) const -> TupleId
{
	return mTuples.findObjectIdSilent(pTuple);
}


auto MatrixTupleStorage::findTupleIdAnyRelationSilent(TupleT const& pTuple) const -> TupleId
{
	auto iter = beginTuplesForAnyRelation(pTuple);
	return iter != endTuples() ? findTupleId(iter) : nullptr;
}


auto MatrixTupleStorage::findTupleIdAnyRelation(TupleT const& pTuple) const -> TupleId
{
	TupleId id = findTupleIdAnyRelationSilent(pTuple);
	EXCEPTION(id != nullptr, "MatrixTupleStorage::findTupleIdAnyRelation(): Tuple not found.");
	return id;
}


auto MatrixTupleStorage::findTupleIdsAllRelations(TupleT const& pTuple) const -> TupleIdVector
{
	TupleIdVector ids;
	{
		auto iterPair = range(pTuple);
		for (auto iter = iterPair.first; iter != iterPair.second; ++iter)
		{
			ids.push_back(findTupleId(iter));
		}
	}

	return ids;
}


auto MatrixTupleStorage::findTuple(TupleIteratorConst const& pIterator)	const -> TupleT const&
{
	return mTuples.findObject(pIterator);
}


auto MatrixTupleStorage::findTuple(TupleId pTupleId) const -> TupleT const&
{
	return mTuples.findObject(pTupleId);
}


auto MatrixTupleStorage::findAndCopyTuple(TupleId pTupleId) const -> TupleT
{
	return mTuples.findAndCopyObject(pTupleId);
}


void MatrixTupleStorage::removeTuple(TupleId pTupleId)
{
	subtractFrequencies(findTuple(pTupleId));
	mTuples.removeObject(pTupleId);
}


bool MatrixTupleStorage::addTuple(TupleT&& pTuple)
{
	auto res = mTuples.addObjectGetResult(std::forward<TupleT>(pTuple));
	updateFrequencies(pTuple, res);
	return res.second;
}


bool MatrixTupleStorage::addTuple(TupleT const& pTuple)
{
	auto res = mTuples.addObjectGetResult(pTuple);
	updateFrequencies(pTuple, res);
	return res.second;
}


auto MatrixTupleStorage::addTupleGetId(TupleT&& pTuple) -> TupleId
{
	auto res = mTuples.addObjectGetResult(std::forward<TupleT>(pTuple));
	updateFrequencies(pTuple, res);
	return findTupleId(res.first);
}


auto MatrixTupleStorage::addTupleGetId(TupleT const& pTuple) -> TupleId
{
	auto res = mTuples.addObjectGetResult(pTuple);
	updateFrequencies(pTuple, res);
	return findTupleId(res.first);
}


auto MatrixTupleStorage::retrieveTupleIdVector() const -> TupleIdVector
{
	TupleIdVector ids;
	ids.reserve(getDistinctTupleCount());

	for (auto iter = beginTuples(); iter != endTuples(); ++iter)
	{
		ids.push_back(findTupleId(iter));
	}

	return ids;
}


void MatrixTupleStorage::recomputeTuplesGlobalFrequency()
{
	mCorporaGlobalTupleFrequency.setGlobalFrequency(0.0);
	for (auto i = beginTuples(); i != endTuples(); ++i)
	{
		i->getMetadata().computeGlobalFrequency();
		mCorporaGlobalTupleFrequency.modifyGlobalFrequency(
			i->getMetadata().getGlobalFrequency());
	}
}


std::string	MatrixTupleStorage::createTupleReprezentationWebTool(TupleT const& pTuple) const
{
	std::stringstream str;
	str << pTuple.getMetadata().getGlobalFrequency();
	str << '\t' << pTuple.getRelationCopy()->getName() << '\t';
	for (size_t i = 0; i < pTuple.size(); ++i)
	{
		str << createWordReprezentation(pTuple[i]) << ' ';
	}
	return str.str();
}

std::string	MatrixTupleStorage::createTupleReprezentation(TupleT const& pTuple) const
{
	std::stringstream str;
	str << createRelationReprezentation(pTuple.getRelationCopy());
	for (size_t i = 0; i < pTuple.size(); ++i)
	{
		str << '\t' << createWordReprezentation(pTuple[i]);
	}
	return str.str();
}


std::string MatrixTupleStorage::createTupleReprezentationWebTool(TupleId const& pTupleId) const
{
	return createTupleReprezentationWebTool(findTuple(pTupleId));
}


std::string MatrixTupleStorage::createTupleReprezentation(TupleId const& pTupleId) const
{
	return createTupleReprezentation(findTuple(pTupleId));
}


auto MatrixTupleStorage::parseTupleReprezentation(std::string const& pTupleString) const -> TupleId
{
	size_t 		end 	= pTupleString.find_first_of('\t', pTupleString.find_first_of('\t') + 1);
	RelationId 	relId 	= findRelationByReprezentation(pTupleString.substr(0, end));

	TupleT tuple(findRelation(relId).getArity(), relId, 0, 0);

	for (size_t i = 0; i < tuple.size(); ++i)
	{
		++end;
		size_t curEnd 	= std::min(pTupleString.find_first_of('\t', end), pTupleString.length());
		tuple[i] 		= parseWordReprezentation(pTupleString.substr(end, curEnd - end));
		end = curEnd;
	}

	return findTupleId(tuple);
}


std::string MatrixTupleStorage::createTupleWordChain(TupleT const& pTuple) const
{
	std::stringstream str;
	for (size_t e = 0; e < pTuple.size(); ++e)
	{
		str << findWord(pTuple[e]).getContent();
		if (e < pTuple.size() - 1)
		{
			str << ' ';
		}
	}
	return str.str();
}


std::string MatrixTupleStorage::createTupleWordChain(TupleId const& pTupleId) const
{
	return createTupleWordChain(findTuple(pTupleId));
}


std::string MatrixTupleStorage::createTuplePosWordChain(TupleT const& pTuple) const
{
	std::stringstream str;
	for (size_t e = 0; e < pTuple.size(); ++e)
	{
		str << createWordReprezentation(pTuple[e]);
		if (e < pTuple.size() - 1)
		{
			str << ' ';
		}
	}
	return str.str();
}


std::string MatrixTupleStorage::createTuplePosWordChain(TupleId const& pTupleId) const
{
	return createTuplePosWordChain(findTuple(pTupleId));
}


auto MatrixTupleStorage::beginTuples() const -> TupleIteratorConst
{
	return mTuples.begin();
}


auto MatrixTupleStorage::beginTuples() -> TupleIterator
{
	return mTuples.begin();
}


auto MatrixTupleStorage::endTuples() const -> TupleIteratorConst
{
	return mTuples.end();
}


auto MatrixTupleStorage::endTuples() -> TupleIterator
{
	return mTuples.end();
}


auto MatrixTupleStorage::beginTuplesForAnyRelation(TupleT pTuple) const -> TupleIteratorConst
{
	pTuple.setRelation(nullptr);
	return mTuples.getContainer().lower_bound(pTuple);
}


auto MatrixTupleStorage::beginTuplesForAnyRelation(TupleT pTuple) -> TupleIterator
{
	pTuple.setRelation(nullptr);
	return mTuples.getContainer().lower_bound(pTuple);
}


auto MatrixTupleStorage::endTuplesForAnyRelation(TupleT pTuple) const -> TupleIteratorConst
{
	pTuple.setRelation(nullptr);
	--pTuple.getRelation();
	return mTuples.getContainer().upper_bound(pTuple); // upper_bound maybe? It should be better in theory but in practice it shouldn't be any difference
}


auto MatrixTupleStorage::endTuplesForAnyRelation(TupleT pTuple) -> TupleIterator
{
	pTuple.setRelation(nullptr);
	--pTuple.getRelation();
	return mTuples.getContainer().upper_bound(pTuple); // upper_bound maybe?
}


auto MatrixTupleStorage::range(TupleT pTuple) const -> TupleIteratorConstPair
{
	TupleIteratorConstPair pair;

	pTuple.setRelation(nullptr);
	pair.first = mTuples.getContainer().lower_bound(pTuple);

	--pTuple.getRelation();
	pair.second = mTuples.getContainer().upper_bound(pTuple);

	return pair;
}


auto MatrixTupleStorage::range(TupleT pTuple) -> TupleIteratorPair
{
	TupleIteratorPair pair;

	pTuple.setRelation(nullptr);
	pair.first = mTuples.getContainer().lower_bound(pTuple);

	--pTuple.getRelation();
	pair.second = mTuples.getContainer().upper_bound(pTuple);

	return pair;
}


auto MatrixTupleStorage::buildTupleByWordMapping() const -> TuplesByWordMapPtrS
{
	TuplesByWordMapPtrS map(new TuplesByWordMap());
	map->reserve(getWordCount());

	for (auto tuple = beginTuples(); tuple != endTuples(); ++tuple)
	{
		TupleId	tid = findTupleId(tuple);
		for (size_t e = 0; e < tuple->size(); ++e)
		{
			map->insert(std::pair<WordId, TupleIdVector>(
				tuple->getElementCopy(e), TupleIdVector())).first->second.push_back(tid);
		}
	}

	return map;
}


auto MatrixTupleStorage::buildTupleByWordByPositionMapping() const -> TuplesByWordByPositionPtrS
{
	TuplesByWordByPositionPtrS 	mapVector(new TuplesByWordByPosition(findLongestRelation().getArity()));
	TuplesByWordByPosition& 	vector = *mapVector;

	for (auto tuple = beginTuples(); tuple != endTuples(); ++tuple)
	{
		if (tuple->size() > vector.size())
		{
			vector.resize(tuple->size());
		}

		TupleId tid = findTupleId(tuple);
		for (size_t e = 0; e < tuple->size(); ++e)
		{
			vector[e].insert(std::pair<WordId, TupleIdVector>(
				tuple->getElementCopy(e), TupleIdVector())).first->second.push_back(tid);
		}
	}

	return mapVector;
}


auto MatrixTupleStorage::buildTupleByTupleMapping() const -> TuplesByTupleMapPtrS
{
	TuplesByTupleMapPtrS tuples(new TuplesByTupleMap());
	tuples->reserve(getDistinctTupleCount());

	TuplesByWordMapPtrS words(buildTupleByWordMapping());

	std::unordered_set<TupleId> banned;
	for (auto tuple = beginTuples(); tuple != endTuples(); ++tuple)
	{
		TupleId	tid = findTupleId(tuple);
		banned.insert(tid);

		TupleIdVector& vector = tuples->insert(
			std::pair<TupleId, TupleIdVector>(tid, TupleIdVector())).first->second;

		for (size_t e = 0; e < tuple->size(); ++e)
		{
			TupleIdVector const& tuplesForWord = words->find(tuple->getElementCopy(e))->second;
			for (size_t it = 0; it < tuplesForWord.size(); ++it)
			{
				if (banned.insert(tuplesForWord[it]).second)
				{
					vector.push_back(tuplesForWord[it]);
				}
			}
		}

		banned.clear();
	}

	return tuples;
}


void MatrixTupleStorage::updateFrequencies(
	TupleT const& 		pInsertedTuple,
	AddResult const& 	pResult)
{
	if(!pResult.second)
	{
		pResult.first->getMetadata().addFrequencies(pInsertedTuple.getMetadata());
	}
	mCorporaGlobalTupleFrequency.addFrequencies(pInsertedTuple.getMetadata());
	findRelation(pInsertedTuple.getRelationCopy()).getMetadata().addFrequencies(pInsertedTuple.getMetadata());
}


void MatrixTupleStorage::subtractFrequencies(
	TupleT const& pTuple)
{
	mCorporaGlobalTupleFrequency.subtractFrequencies(pTuple.getMetadata());
	findRelation(pTuple.getRelationCopy()).getMetadata().subtractFrequencies(pTuple.getMetadata());
}


	}
}
