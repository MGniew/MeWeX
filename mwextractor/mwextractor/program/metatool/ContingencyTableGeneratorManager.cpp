
#include "ContingencyTableGeneratorManager.h"


namespace program
{
	namespace metatool
	{


ContingencyTableGeneratorManager::ContingencyTableGeneratorManager(Id pModuleId, std::string&& pName)
:
	DataManager(pModuleId, pName)
{

}


ContingencyTableGeneratorManager::ContingencyTableGeneratorManager(Id pModuleId, std::string const& pName)
:
	DataManager(pModuleId, pName)
{

}


auto ContingencyTableGeneratorManager::loadFromFile(std::string const& pPath) -> Id
{
	using namespace structure::io;
	return addObject(ContingencyTableGeneratorIO().read(pPath));
}


void ContingencyTableGeneratorManager::writeToFile(
	std::string const& 	pPath,
	Id 					pId) const
{
	using namespace structure::io;

	auto const& pObject = getObject(pId);
	DecodedTupleStorageIO().write(pPath, *pObject);
}


auto ContingencyTableGeneratorManager::copy(Id pId) -> Id
{
	EXCEPTION(false, "ContingencyTableGeneratorManager::copy(): Not implemented.");
	return 0;
}


	}
}
