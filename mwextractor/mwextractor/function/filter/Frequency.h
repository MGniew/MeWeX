
#pragma once

#include "FeatureFilter.h"


namespace function
{
	namespace filter
	{


class Frequency : public FeatureFilter
{
public:
	Frequency(
		OperatorType 					pOperatorType,
		StringParameterVector const&	pParameters);

	Frequency();
	Frequency(Frequency&& 					pFilter) 	= default;
	Frequency(Frequency const& 				pFilter) 	= default;
	Frequency& operator=(Frequency&& 		pFilter) 	= default;
	Frequency& operator=(Frequency const& 	pFilter) 	= default;

	virtual ~Frequency() = default;

	std::string name() const override;


protected:
	virtual void construct() override;

	virtual bool equal(TupleId pTupleId) 		const;
	virtual bool lower(TupleId pTupleId) 		const;
	virtual bool greater(TupleId pTupleId) 		const;
	virtual bool lowerEqual(TupleId pTupleId) 	const;
	virtual bool greaterEqual(TupleId pTupleId) const;

private:
	double mFrequency;
};


	}
}
