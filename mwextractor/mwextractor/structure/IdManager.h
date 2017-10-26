/*
 * IdManager.h
 *
 *  Created on: 30 maj 2014
 *      Author: michalw
 */

#pragma once

#include <queue>
#include <cstddef>


namespace structure
{


template <typename IdType = size_t>
class IdManager
{
private:
	typedef std::priority_queue<IdType, std::vector<IdType>, std::greater<IdType>> __PriorityQueue;

public:
	IdManager(IdType pFirstId = 0);

	IdManager(IdManager&& 					pManager) = default;
	IdManager(IdManager const&		 		pManager) = delete;
	IdManager& operator=(IdManager&&	 	pManager) = default;
	IdManager& operator=(IdManager const& 	pManager) = delete;

	~IdManager() = default;


	void 	freeId(IdType pId);
	IdType 	acquireId();


private:
	__PriorityQueue mIdsStore;
	IdType 			mNextHighest;
};


template <typename IdType>
IdManager<IdType>::IdManager(IdType pFirstId)
:
	mNextHighest(pFirstId)
{
	mIdsStore.push(pFirstId);
}


template <typename IdType>
void IdManager<IdType>::freeId(IdType pId)
{
	EXCEPTION(pId < mNextHighest, "IdManager::freeId: it seems that id which was never acquired (" << pId <<  ") is freeing");
	mIdsStore.push(pId);
}


template <typename IdType>
IdType IdManager<IdType>::acquireId()
{
	IdType top = mIdsStore.top();
	mIdsStore.pop();

	if (top == mNextHighest)
	{
		mIdsStore.push(++mNextHighest);
	}

	return top;
}


}
