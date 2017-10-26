
#include <sstream>

#include "../FunctionFactory.h"
#include "FairDispersionPointNormalization.h"


namespace function
{
	namespace association
	{


auto FairDispersionPointNormalization::copy() const -> AssociationMeasurePtrS
{
	std::shared_ptr<FairDispersionPointNormalization> result(new FairDispersionPointNormalization());
	result->setInnerAssociationFunction(copyInnerAssociationFunction());
	return result;
}


/*
 * f(x) == 0: ??
 */
double FairDispersionPointNormalization::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	typedef ContingencyTable::ContingencyValue 	__CV;
	typedef MatrixTupleStorage::TupleT			__Tuple;
	typedef MatrixTupleStorage::TupleIdVector	__TupleIdVector;

	size_t tupleSize = pContingencyTable.tupleSize();

	double result = 0.0;
	for (size_t i = 0; i < tupleSize - 1; ++i)
	{
		ContingencyTable tempTable = pContingencyTable.compressObservedToBigram(i);
		tempTable.computeExpected();

		result += (*getInnerAssociationFunction())(nullptr, tempTable);
	}

	return result / static_cast<double>(tupleSize - 1);
}


std::string	FairDispersionPointNormalization::name() const
{
	return "fair_dispersion_point_normalization";
}


	}
}
