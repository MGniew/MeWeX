
#include <sstream>

#include "../../utils/Math.h"
#include "../FunctionFactory.h"
#include "SmoothedBigram.h"


namespace function
{
	namespace association
{


auto SmoothedBigram::copy() const -> AssociationMeasurePtrS
{
	std::shared_ptr<SmoothedBigram> result(new SmoothedBigram());
	result->setInnerAssociationFunction(copyInnerAssociationFunction());
	return result;
}


/*
 * f(x) == 0: ??
 */
double SmoothedBigram::rankUsingTable(
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

	// bit setting - set integer value with bit representation: 000...011...100
	//															|-----||----|||
	// (2) zeros at the lowest bits, then (tuple_size - 2 - 1) ones and then (all) zeros
	size_t offset 	= (sizeof(size_t) << 3) - tupleSize;
	size_t index 	= (static_cast<size_t>(-2) << offset) >> offset;

	ContingencyTable table(pContingencyTable.size() >> 1);
	for (size_t i = 0; i < tupleSize - 1; ++i)
	{
		size_t tableIndex = utils::wrapShiftLeft(index, i, tupleSize - 1);
		table[tableIndex] = pContingencyTable.gatherObservedBigramData(i)[0].observed;
	}

	table[0] 				= pContingencyTable[0].observed;
	table[table.size() - 1]	= pContingencyTable.sumObserved() - table.sumObserved();

	table.computeExpected();

	return (*getInnerAssociationFunction())(nullptr, table);
}


std::string	SmoothedBigram::name() const
{
	return "smoothed_bigram";
}


	}
}
