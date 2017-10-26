
#include "MatrixTupleStorageManager.h"


namespace program
{
	namespace metatool
	{


MatrixTupleStorageManager::MatrixTupleStorageManager(Id pModuleId, std::string&& pName)
:
	DataManager(pModuleId, pName)
{

}


MatrixTupleStorageManager::MatrixTupleStorageManager(Id pModuleId, std::string const& pName)
:
	DataManager(pModuleId, pName)
{

}


auto MatrixTupleStorageManager::loadFromFile(std::string const& pPath) -> Id
{
	using namespace structure::io;
	return addObject(DecodedTupleStorageIO().read(pPath));
}


void MatrixTupleStorageManager::writeToFile(
	std::string const& 	pPath,
	Id 					pId) const
{
	using namespace structure::io;

	auto const& pObject = getObject(pId);
	DecodedTupleStorageIO().write(pPath, *pObject);
}


auto MatrixTupleStorageManager::copy(Id pId) -> Id
{
	EXCEPTION(false, "MatrixTupleStorageManager::copy(): Not implemented.");
	return 0;
}


	}
}
