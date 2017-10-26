
#include "../../utils/Math.h"

#include "../../exception/Exception.h"

#include "../../structure/storage/FrequencyStorage.h"

#include "LynesD3.h"


namespace function
{
	namespace dispersion
	{


LynesD3::LynesD3()
:
	mRankerData(new RankerData())
{
	mPx2.setRankerData(mRankerData);
}


double LynesD3::disperse(TupleId pTupleId) const
{
	XASSERT(
		getDispersionData()->hasMatrixTupleStorage(),
		"DistributionalConsistency::disperse(): Matrix tuple storage not set.");

	EXCEPTION(
		getDispersionData()->hasContingencyTableSource(),
		"DistributionalConsistency::disperse(): Contingency table source not set.")

	structure::storage::FrequencyStorage storage =
		getDispersionData()->getMatrixTupleStorage()->findTuple(pTupleId).getMetadata();

	if (mRankerData->getMatrixTupleStorage() != getDispersionData()->getMatrixTupleStorage())
	{
		mRankerData->setMatrixTupleStorage(getDispersionData()->getMatrixTupleStorage());
	}
	if (mRankerData->getContingencyTableSource() != getDispersionData()->getContingencyTableSource())
	{
		mRankerData->setContingencyTableSource(getDispersionData()->getContingencyTableSource());
	}

	double res 	= 1.0 - mPx2.rank(pTupleId);
	double frequencyDividedBy4 = storage.sumLocalFrequencies() * 0.25;
	return res / frequencyDividedBy4;
}


std::string	LynesD3::name() const
{
	return "lynes_d3";
}


	}
}
