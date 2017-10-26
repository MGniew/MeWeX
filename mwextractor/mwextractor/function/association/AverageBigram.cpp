
#include <sstream>

#include "../FunctionFactory.h"
#include "AverageBigram.h"


namespace function
{
	namespace association
	{


auto AverageBigram::copy() const -> AssociationMeasurePtrS
{
	std::shared_ptr<AverageBigram> result(new AverageBigram());
	result->setInnerAssociationFunction(copyInnerAssociationFunction());
	return result;
}

/*
 * f(x) == 0: ??
 */
double AverageBigram::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	typedef ContingencyTable::ContingencyValue 	__CV;
	typedef MatrixTupleStorage::TupleT			__Tuple;
	typedef MatrixTupleStorage::TupleIdVector	__TupleIdVector;

	size_t tupleSize = pContingencyTable.tupleSize();

	if (tupleSize == 2)
	{
		return (*getInnerAssociationFunction())(nullptr, pContingencyTable);
	}

	double observedSum	= pContingencyTable.sumObserved();
	double result 		= 0.0;
	for (size_t i = 0; i < tupleSize - 1; ++i)
	{
		ContingencyTable tempTable = pContingencyTable.gatherObservedBigramData(i);
		tempTable.computeExpected();

		result += (*getInnerAssociationFunction())(nullptr, tempTable);
	}

	return result / static_cast<double>(tupleSize - 1);
}


std::string	AverageBigram::name() const
{
	return "average_bigram";
}


	}
}
