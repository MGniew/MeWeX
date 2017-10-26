
#include <sstream>

#include "../../utils/Textual.h"

#include "Frequency.h"


namespace function
{
	namespace filter
	{


Frequency::Frequency(
	OperatorType 					pOperatorType,
	StringParameterVector const&	pParameters)
:
	FeatureFilter(pOperatorType, pParameters),
	mFrequency(0.0)
{

}


Frequency::Frequency()
:
	FeatureFilter(),
	mFrequency(0.0)
{

}


void Frequency::construct()
{
	mFrequency = getParameters().empty() ? 0.0 : utils::toDouble(getParameters()[0]);
}


std::string Frequency::name() const
{
	return "frequency";
}


bool Frequency::equal(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		getGlobalFrequency() == mFrequency;
}


bool Frequency::lower(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		getGlobalFrequency() < mFrequency;
}


bool Frequency::greater(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		getGlobalFrequency() > mFrequency;
}


bool Frequency::lowerEqual(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		getGlobalFrequency() <= mFrequency;
}


bool Frequency::greaterEqual(TupleId pTupleId) const
{
	return getMatrixTupleStorage()->findTuple(pTupleId).getMetadata().
		getGlobalFrequency() >= mFrequency;
}


	}
}
