
#include <sstream>

#include "../../utils/Textual.h"

#include "CorporaFrequency.h"


namespace function
{
	namespace filter
	{


CorporaFrequency::CorporaFrequency(
	OperatorType 					pOperatorType,
	StringParameterVector const&	pParameters)
:
	FeatureFilter(pOperatorType, pParameters),
	mCorporaFrequency(0.0)
{

}


CorporaFrequency::CorporaFrequency()
:
	FeatureFilter(),
	mCorporaFrequency(0.0)
{

}


void CorporaFrequency::construct()
{
	mCorporaFrequency = utils::toDouble(getParameters()[0]);
}


std::string CorporaFrequency::name() const
{
	return "corpora_frequency";
}


bool CorporaFrequency::equal(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		sumLocalFrequencies() == mCorporaFrequency;
}


bool CorporaFrequency::lower(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		sumLocalFrequencies() < mCorporaFrequency;
}


bool CorporaFrequency::greater(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		sumLocalFrequencies() > mCorporaFrequency;
}


bool CorporaFrequency::lowerEqual(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		sumLocalFrequencies() <= mCorporaFrequency;
}


bool CorporaFrequency::greaterEqual(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		sumLocalFrequencies() >= mCorporaFrequency;
}


	}
}
