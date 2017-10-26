
#include <sstream>

#include "../FunctionFactory.h"
#include "MinimalBigram.h"


namespace function
{
	namespace association
	{


auto MinimalBigram::copy() const -> AssociationMeasurePtrS
{
	std::shared_ptr<MinimalBigram> result(new MinimalBigram());
	result->setInnerAssociationFunction(copyInnerAssociationFunction());
	return result;
}


/*
 * f(x) == 0: ??
 */
double MinimalBigram::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	typedef ContingencyTable::ContingencyValue 	__CV;
	typedef MatrixTupleStorage::TupleT			__Tuple;
	typedef MatrixTupleStorage::TupleIdVector	__TupleIdVector;

	if (pContingencyTable.size() <= 4)
	{
		return (*getInnerAssociationFunction())(nullptr, pContingencyTable);
	}

	size_t tupleSize 	= pContingencyTable.tupleSize();
	double observedSum	= pContingencyTable.sumObserved();
	double result 		= std::numeric_limits<double>::max();

	// for every bigram generate a contingency table 2x2 based on bigger table //
	for (size_t i = 0; i < tupleSize - 1; ++i)
	{
		ContingencyTable tempTable = pContingencyTable.gatherObservedBigramData(i);
		tempTable.computeExpected();

		double score = (*getInnerAssociationFunction())(nullptr, tempTable);
		result = std::min(result, score);
	}

	return result;
}


std::string	MinimalBigram::name() const
{
	return "minimal_bigram";
}


	}
}
