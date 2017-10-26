
#include <sstream>

#include "../../utils/Textual.h"
#include "RelationStorage.h"


namespace structure
{
	namespace storage
	{


size_t RelationStorage::getRelationCount() const
{
	return mRelations.size();
}


auto RelationStorage::findRelationId(RelationIteratorConst const& pIterator) const -> RelationId
{
	return mRelations.findObjectId(pIterator);
}


auto RelationStorage::findRelationId(RelationT const& pRelation) const -> RelationId
{
	return mRelations.findObjectId(pRelation);
}


auto RelationStorage::findRelationId(std::string const& pRelationName) const -> RelationId
{
	return findRelationId(RelationT(
		0,
		extractRelationName(pRelationName),
		0,
		0.0,
		0));
}


auto RelationStorage::findRelationIdSilent(RelationT const& pRelation) const -> RelationId
{
	return mRelations.findObjectIdSilent(pRelation);
}


auto RelationStorage::findRelationIdSilent(std::string const& pRelationName) const -> RelationId
{
	return findRelationIdSilent(RelationT(
		0,
		extractRelationName(pRelationName),
		0,
		0.0,
		0));
}


auto RelationStorage::findLongestRelationId() const -> RelationId
{
	size_t		longest		= 0;
	RelationId 	longestId 	= nullptr;
	for (auto i = beginRelations(); i != endRelations(); ++i)
	{
		RelationId id = findRelationId(i);
		if (findRelation(i).getArity() > longest)
		{
			longestId = id;
		}
	}
	return longestId;
}


auto RelationStorage::findRelation(RelationIteratorConst const& pIterator) const -> RelationT const&
{
	return mRelations.findObject(pIterator);
}


auto RelationStorage::findRelation(RelationId pRelationId) const -> RelationT const&
{
	return mRelations.findObject(pRelationId);
}


auto RelationStorage::findRelation(std::string pRelationName) const -> RelationT const&
{
	return findRelation(findRelationId(pRelationName));
}


auto RelationStorage::findAndCopyRelation(RelationId pRelationId) const -> RelationT
{
	return mRelations.findAndCopyObject(pRelationId);
}


auto RelationStorage::findLongestRelation() const -> RelationT
{
	RelationId longest = findLongestRelationId();
	return longest != nullptr ? findRelation(longest) : RelationT(0, "", 0, 0, 0);
}


bool RelationStorage::addRelation(RelationT&& pRelation)
{
	auto res = mRelations.addObjectGetResult(std::forward<RelationT>(pRelation));
	updateFrequencies(pRelation, res);
	return res.second;
}


bool RelationStorage::addRelation(RelationT const& pRelation)
{
	auto res = mRelations.addObjectGetResult(pRelation);
	updateFrequencies(pRelation, res);
	return res.second;
}


auto RelationStorage::addRelationGetId(RelationT&& pRelation) -> RelationId
{
	auto res = mRelations.addObjectGetResult(std::forward<RelationT>(pRelation));
	updateFrequencies(pRelation, res);
	return findRelationId(res.first);
}


auto RelationStorage::addRelationGetId(RelationT const& pRelation) -> RelationId
{
	auto res = mRelations.addObjectGetResult(pRelation);
	updateFrequencies(pRelation, res);
	return findRelationId(res.first);
}


void RelationStorage::recomputeRelationsGlobalFrequency()
{
	for (auto i = beginRelations(); i != endRelations(); ++i)
	{
		i->getMetadata().computeGlobalFrequency();
	}
}


std::string RelationStorage::createRelationReprezentation(RelationT const& pRelation) const
{
	std::stringstream str;
	str << pRelation.getGroup() << '\t' << pRelation.getName() << '\t' << pRelation.getArity();
	return str.str();
}


std::string RelationStorage::createRelationReprezentation(RelationId const& pRelationId) const
{
	return createRelationReprezentation(findRelation(pRelationId));
}


std::string RelationStorage::extractRelationName(std::string const& pNameWithMeta) const
{
	size_t first = pNameWithMeta.find_first_of('_');
	size_t last = pNameWithMeta.find_last_of('_');

	return pNameWithMeta.substr(first + 1, last - first - 1);
}


auto RelationStorage::findRelationByReprezentation(std::string const& pRelationString) const -> RelationId
{
	return findRelationId(parseRelationReprezentation(pRelationString));
}


auto RelationStorage::parseRelationReprezentation(std::string const& pRelationString) const -> RelationT
{
	size_t split1 = pRelationString.find_first_of('\t');
	size_t split2 = pRelationString.find_first_of('\t', split1 + 1);
	return RelationT(
			utils::toSizeT(pRelationString.substr(0, split1)),
			pRelationString.substr(split1 + 1, split2 - split1 - 1),
			utils::toSizeT(pRelationString.substr(split2 + 1)),
			0,
			0);
}


auto RelationStorage::beginRelations() const -> RelationIteratorConst
{
	return mRelations.begin();
}


auto RelationStorage::beginRelations() -> RelationIterator
{
	return mRelations.begin();
}


auto RelationStorage::endRelations() const -> RelationIteratorConst
{
	return mRelations.end();
}


auto RelationStorage::endRelations() -> RelationIterator
{
	return mRelations.end();
}



auto RelationStorage::buildRelationScheme() const -> RelationScheme
{
	RelationScheme scheme;

	for (auto iter = beginRelations(); iter != endRelations(); ++iter)
	{
		scheme[iter->getGroup()].push_back(findRelationId(iter));
	}

	return scheme;
}


void RelationStorage::updateFrequencies(
	RelationT const& pInsertedRelation,
	AddResult const& pResult)
{
	if (!pResult.second)
	{
		pResult.first->getMetadata().addFrequencies(pInsertedRelation.getMetadata());
	}
}


	}
}
