
#include <sstream>

#include "../../utils/Textual.h"
#include "CorporaStorage.h"


namespace structure
{
	namespace storage
	{


size_t CorporaStorage::getCorporaCount() const
{
	return mCorporas.size();
}


auto CorporaStorage::findCorporaId(CorporaIteratorConst const& pIterator) const -> CorporaId
{
	return mCorporas.findObjectId(pIterator);
}


auto CorporaStorage::findCorporaId(CorporaT const& pCorpora) const -> CorporaId
{
	return mCorporas.findObjectId(pCorpora);
}


auto CorporaStorage::findCorporaIdSilent(CorporaT const& pCorpora) const -> CorporaId
{
	return mCorporas.findObjectIdSilent(pCorpora);
}


auto CorporaStorage::findCorpora(CorporaIteratorConst const& pIterator)	const -> CorporaT const&
{
	return mCorporas.findObject(pIterator);
}


auto CorporaStorage::findCorpora(CorporaId pCorporaId) const -> CorporaT const&
{
	return mCorporas.findObject(pCorporaId);
}


auto CorporaStorage::findAndCopyCorpora(CorporaId pCorporaId) const -> CorporaT
{
	return mCorporas.findAndCopyObject(pCorporaId);
}


bool CorporaStorage::addCorpora(CorporaT&& pCorpora)
{
	auto res = mCorporas.addObjectGetResult(std::forward<CorporaT>(pCorpora));
	updateFrequencies(pCorpora, res);
	return res.second;
}


bool CorporaStorage::addCorpora(CorporaT const& pCorpora)
{
	auto res = mCorporas.addObjectGetResult(pCorpora);
	updateFrequencies(pCorpora, res);
	return res.second;
}


auto CorporaStorage::addCorporaGetId(CorporaT&& pCorpora) -> CorporaId
{
	auto res = mCorporas.addObjectGetResult(std::forward<CorporaT>(pCorpora));
	updateFrequencies(pCorpora, res);
	return findCorporaId(res.first);
}


auto CorporaStorage::addCorporaGetId(CorporaT const& pCorpora) -> CorporaId
{
	auto res = mCorporas.addObjectGetResult(pCorpora);
	updateFrequencies(pCorpora, res);
	return findCorporaId(res.first);
}


std::string CorporaStorage::createCorporaReprezentation(CorporaT const& pCorpora) const
{
	std::stringstream str;
	str << pCorpora.getName() << '\t' << pCorpora.getSequenceNumber();
	return str.str();
}


std::string CorporaStorage::createCorporaReprezentation(CorporaId const& pCorporaId) const
{
	return createCorporaReprezentation(findCorpora(pCorporaId));
}


auto CorporaStorage::parseCorporaReprezentation(std::string const& pCorpora) const -> CorporaId
{
	size_t split = pCorpora.find_first_of('\t');
	return findCorporaId(CorporaT(
		{
			pCorpora.substr(0, split),
			utils::toSizeT(pCorpora.substr(split + 1))
		}));
}


auto CorporaStorage::beginCorporas() const -> CorporaIteratorConst
{
	return mCorporas.begin();
}


auto CorporaStorage::beginCorporas() -> CorporaIterator
{
	return mCorporas.begin();
}


auto CorporaStorage::endCorporas() const -> CorporaIteratorConst
{
	return mCorporas.end();
}


auto CorporaStorage::endCorporas() -> CorporaIterator
{
	return mCorporas.end();
}


void CorporaStorage::updateFrequencies(
	CorporaT const& 	pInsertedCorpora,
	AddResult const& 	pResult)
{
	if(!pResult.second)
	{
		pResult.first->modifyTokenCount(pInsertedCorpora.getTokenCount());
	}
}


	}
}
