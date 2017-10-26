
#pragma once

#include "FeatureFilter.h"


namespace function
{
	namespace filter
	{


class CorporaFrequency : public FeatureFilter
{
public:
	CorporaFrequency(
		OperatorType 					pOperatorType,
		StringParameterVector const&	pParameters);

	CorporaFrequency();
	CorporaFrequency(CorporaFrequency&& 					pFilter) 	= default;
	CorporaFrequency(CorporaFrequency const& 				pFilter) 	= default;
	CorporaFrequency& operator=(CorporaFrequency&& 		pFilter) 	= default;
	CorporaFrequency& operator=(CorporaFrequency const& 	pFilter) 	= default;

	virtual ~CorporaFrequency() = default;

	std::string name() const override;


protected:
	virtual void construct() override;

	virtual bool equal(TupleId pTupleId) 		const;
	virtual bool lower(TupleId pTupleId) 		const;
	virtual bool greater(TupleId pTupleId) 		const;
	virtual bool lowerEqual(TupleId pTupleId) 	const;
	virtual bool greaterEqual(TupleId pTupleId) const;

private:
	double mCorporaFrequency;
};


	}
}
