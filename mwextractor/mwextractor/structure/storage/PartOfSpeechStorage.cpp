
#include "PartOfSpeechStorage.h"


namespace structure
{
	namespace storage
	{


size_t PartOfSpeechStorage::getPartOfSpeechCount() const
{
	return mPartsOfSpeech.size();
}


auto PartOfSpeechStorage::findPartOfSpeechId(PartOfSpeechIteratorConst const& pIterator) const -> PartOfSpeechId
{
	return mPartsOfSpeech.findObjectId(pIterator);
}


auto PartOfSpeechStorage::findPartOfSpeechId(PartOfSpeechT const& pPartOfSpeech) const -> PartOfSpeechId
{
	return mPartsOfSpeech.findObjectId(pPartOfSpeech);
}


auto PartOfSpeechStorage::findPartOfSpeechIdSilent(PartOfSpeechT const& pPartOfSpeech) const -> PartOfSpeechId
{
	return mPartsOfSpeech.findObjectIdSilent(pPartOfSpeech);
}


auto PartOfSpeechStorage::findPartOfSpeech(PartOfSpeechIteratorConst const& pIterator) const -> PartOfSpeechT const&
{
	return mPartsOfSpeech.findObject(pIterator);
}


auto PartOfSpeechStorage::findPartOfSpeech(PartOfSpeechId pPartOfSpeechId) const -> PartOfSpeechT const&
{
	return mPartsOfSpeech.findObject(pPartOfSpeechId);
}


auto PartOfSpeechStorage::findAndCopyPartOfSpeech(PartOfSpeechId pPartOfSpeechId) const -> PartOfSpeechT
{
	return mPartsOfSpeech.findAndCopyObject(pPartOfSpeechId);
}


bool PartOfSpeechStorage::addPartOfSpeech(PartOfSpeechT&& pPartOfSpeech)
{
	auto res = mPartsOfSpeech.addObjectGetResult(std::forward<PartOfSpeechT>(pPartOfSpeech));
	updateFrequencies(pPartOfSpeech, res);
	return res.second;
}


bool PartOfSpeechStorage::addPartOfSpeech(PartOfSpeechT const& pPartOfSpeech)
{
	auto res = mPartsOfSpeech.addObjectGetResult(pPartOfSpeech);
	updateFrequencies(pPartOfSpeech, res);
	return res.second;
}


auto PartOfSpeechStorage::addPartOfSpeechGetId(PartOfSpeechT&& pPartOfSpeech) -> PartOfSpeechId
{
	auto res = mPartsOfSpeech.addObjectGetResult(std::forward<PartOfSpeechT>(pPartOfSpeech));
	updateFrequencies(pPartOfSpeech, res);
	return findPartOfSpeechId(res.first);
}


auto PartOfSpeechStorage::addPartOfSpeechGetId(PartOfSpeechT const& pPartOfSpeech) -> PartOfSpeechId
{
	auto res = mPartsOfSpeech.addObjectGetResult(pPartOfSpeech);
	updateFrequencies(pPartOfSpeech, res);
	return findPartOfSpeechId(res.first);
}


void PartOfSpeechStorage::recomputePartsOfSpeechGlobalFrequency()
{
	for (auto i = beginPartsOfSpeech(); i != endPartsOfSpeech(); ++i)
	{
		i->getMetadata().computeGlobalFrequency();
	}
}


std::string PartOfSpeechStorage::createPartOfSpeechReprezentation(PartOfSpeechT const& pPartOfSpeech) const
{
	return pPartOfSpeech.getContent();
}


std::string PartOfSpeechStorage::createPartOfSpeechReprezentation(PartOfSpeechId const& pPartOfSpeechId) const
{
	return createPartOfSpeechReprezentation(findPartOfSpeech(pPartOfSpeechId));
}


auto PartOfSpeechStorage::parsePartOfSpeechReprezentation(std::string const& pPartOfSpeech) const -> PartOfSpeechId
{
	return mPartsOfSpeech.findObjectId(PartOfSpeechT(pPartOfSpeech, 0, 0));
}


auto PartOfSpeechStorage::beginPartsOfSpeech() const -> PartOfSpeechIteratorConst
{
	return mPartsOfSpeech.begin();
}


auto PartOfSpeechStorage::beginPartsOfSpeech() -> PartOfSpeechIterator
{
	return mPartsOfSpeech.begin();
}


auto PartOfSpeechStorage::endPartsOfSpeech() const -> PartOfSpeechIteratorConst
{
	return mPartsOfSpeech.end();
}


auto PartOfSpeechStorage::endPartsOfSpeech() -> PartOfSpeechIterator
{
	return mPartsOfSpeech.end();
}


void PartOfSpeechStorage::updateFrequencies(
	PartOfSpeechT const& 	pInsertedPartOfSpeech,
	AddResult const& 		pResult)
{
	if(!pResult.second)
	{
		pResult.first->getMetadata().addFrequencies(pInsertedPartOfSpeech.getMetadata());
	}
}


	}
}
