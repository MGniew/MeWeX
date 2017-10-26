
#pragma once

#include <memory>

#include "RankerData.h"

#include "../Function.h"


namespace function
{
	namespace association
	{


class AbstractRanker : public Function
{
public:
	typedef std::shared_ptr<RankerData> RankerDataPtrS;

public:
	AbstractRanker()													= default;
	AbstractRanker(AbstractRanker&& 				pAbstractRanker)	= default;
	AbstractRanker(AbstractRanker const& 			pAbstractRanker)	= default;
	AbstractRanker& operator=(AbstractRanker&& 		pAbstractRanker)	= default;
	AbstractRanker& operator=(AbstractRanker const& pAbstractRanker)	= default;

	virtual ~AbstractRanker() = default;


	RankerDataPtrS const& getRankerData() const;

	bool hasRankerData() const;

	void setRankerData(RankerDataPtrS const& pRankerDataPtrS);


	virtual void initialize(RankerDataPtrS const& pRankerDataPtrS);


private:
	RankerDataPtrS mRankerData;
};


	}
}
