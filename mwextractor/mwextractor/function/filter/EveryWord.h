
#pragma once

#include <unordered_set>

#include "FeatureFilter.h"


namespace function
{
	namespace filter
	{


class EveryWord : public FeatureFilter
{
private:
	typedef TupleStorage::WordT		WordT;
	typedef TupleStorage::WordIdSet	WordIdSet;

public:
	EveryWord(
		OperatorType 					pOperatorType,
		StringParameterVector const&	pWords);

	EveryWord()											= default;
	EveryWord(EveryWord&& 					pFilter) 	= default;
	EveryWord(EveryWord const& 				pFilter) 	= default;
	EveryWord& operator=(EveryWord&& 		pFilter) 	= default;
	EveryWord& operator=(EveryWord const& 	pFilter) 	= default;

	virtual ~EveryWord() = default;

	virtual std::string name() const override;

protected:
	virtual void construct() override;

	virtual bool in(TupleId pTupleId) const override;

private:
	WordIdSet mWordIdSet;
};


	}
}
