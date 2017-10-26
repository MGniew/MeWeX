
#pragma once

#include <map>

#include "../../exception/Exception.h"
#include "../../structure/IdManager.h"

#include "Module.h"


namespace program
{
	namespace metatool
	{


template <typename StorageType>
class DataManager : public Module
{
public:
	typedef structure::IdManager<Id>	IdManager;
	typedef std::map<Id, StorageType> 	StorageMap;

public:
	DataManager(Id pModuleId, std::string&& 		pName);
	DataManager(Id pModuleId, std::string const& 	pName);


	virtual Id loadFromFile(std::string const& pPath) = 0;

	virtual void writeToFile(std::string const& pPath, Id pId) const = 0;

	virtual Id copy(Id pId) = 0;


	Id addObject(StorageType const& pObject);

	bool removeObject(Id pId);

	StorageType const& 	getObject(Id pId) const;
	StorageType& 		getObject(Id pId);

private:
	IdManager	mIdManager;
	StorageMap 	mStorage;
};


template <typename StorageType>
DataManager<StorageType>::DataManager(Id pModuleId, std::string&& pName)
:
	Module(pModuleId, pName)
{

}


template <typename StorageType>
DataManager<StorageType>::DataManager(Id pModuleId, std::string const& pName)
:
	Module(pModuleId, pName)
{

}


template <typename StorageType>
auto DataManager<StorageType>::addObject(StorageType const& pObject) -> Id
{
	Id id = mIdManager.acquireId();
	mStorage.insert(std::make_pair(id, pObject));
	return id;
}


template <typename StorageType>
bool DataManager<StorageType>::removeObject(Id pId)
{
	bool released = mStorage.erase(pId) == 1;
	if (released)
	{
		mIdManager.freeId(pId);
	}
	return released;
}


template <typename StorageType>
StorageType const& DataManager<StorageType>::getObject(Id pId) const
{
	auto iter = mStorage.find(pId);
	EXCEPTION(iter != mStorage.end(), "DataManager<StorageType>::getObject(): Object with id " << pId << " doesn't exists.");
	return iter->second;
}


template <typename StorageType>
StorageType& DataManager<StorageType>::getObject(Id pId)
{
	auto iter = mStorage.find(pId);
	EXCEPTION(iter != mStorage.end(), "DataManager<StorageType>::getObject(): Object with id " << pId << " doesn't exists.");
	return iter->second;
}


	}
}
