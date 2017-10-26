
#include <sstream>
#include <limits>

#include "../../utils/Textual.h"
#include "../../utils/Math.h"
#include "ContingencyTable.h"


namespace structure
{
	namespace storage
	{


ContingencyTable::ContingencyValue::ContingencyValue(
	double pObserved,
	double pExpected)
:
	observed(pObserved),
	expected(pExpected)
{

}



ContingencyTable::ContingencyTable(
	size_t pSpace)
:
	mValues(pSpace)
{

}


ContingencyTable::ContingencyTable(
	size_t 					pSpace,
	ContingencyValue const& pValue)
:
	mValues(pSpace, pValue)
{

}


auto ContingencyTable::operator[](size_t pIndex) const -> ContingencyValue const&
{
	return mValues[pIndex];
}


auto ContingencyTable::operator[](size_t pIndex) -> ContingencyValue&
{
	return mValues[pIndex];
}


auto ContingencyTable::data() const -> ContingencyValue const*
{
	return mValues.data();
}


auto ContingencyTable::data() -> ContingencyValue*
{
	return mValues.data();
}


size_t ContingencyTable::size() const
{
	return mValues.size();
}


size_t ContingencyTable::tupleSize() const
{
	return static_cast<size_t>(std::rint(std::log2(static_cast<double>(size()))));
}


ContingencyTable ContingencyTable::gatherObservedBigramData(size_t pBigramIndex) const
{
	/* each mask is used to sum parts of different table field (accumulate information in bigger table to fit 2x2 table)
	 * output 2x2 table ( A  B) = sum (input_contingency_table[(m + 0)] for m in masks)
	 * output 2x2 table (~A  B) = sum (input_contingency_table[(m + 1)] for m in masks)
	 * output 2x2 table ( A ~B) = sum (input_contingency_table[(m + 2)] for m in masks)
	 *
	 * if ABC is considered then to count BC instead of AB a shift operation on mask must be applied
	 * output 2x2 table ( B  C) = sum (input_contingency_table[(m + 0) circural_shift 1] for m in masks)
	 * output 2x2 table (~B  C) = sum (input_contingency_table[(m + 1) circural_shift 1] for m in masks)
	 * output 2x2 table ( B ~C) = sum (input_contingency_table[(m + 2) circural_shift 1] for m in masks)
	 *
	 * for ABCD and so on shift must be bigger:
	 * AB - shift 0
	 * BC - shift 1
	 * CD - shift 2
	 * ...
	 */

	ContingencyTable bigramTable(4, ContingencyValue(0.0, 0.0));

	size_t sizeOfTuple 	= tupleSize();
	size_t maskCount 	= (1 << (sizeOfTuple - 2)); // each mask is i << 2 for i in [0 : ...]

	/* for every bigram generate a contingency table 2x2 based on bigger table */
	for (size_t m = 0; m < maskCount; ++m)
	{
		size_t mask = (m << 2);

		/* sum part of:  A B or  B C or  C D ... (depends on i value) */
		size_t tableIndex = utils::wrapShiftLeft(mask, pBigramIndex, sizeOfTuple);
		bigramTable[0].observed += mValues[tableIndex].observed;

		/* sum part of: ~A B or ~B C or ~C D ... (depends on i value) */
		tableIndex = utils::wrapShiftLeft(mask | 1, pBigramIndex, sizeOfTuple);
		bigramTable[1].observed += mValues[tableIndex].observed;

		/* sum part of: A ~B or B ~C or C ~D ... (depends on i value) */
		tableIndex = utils::wrapShiftLeft(mask | 2, pBigramIndex, sizeOfTuple);
		bigramTable[2].observed += mValues[tableIndex].observed;
	}

	/* count ~A ~B */
	bigramTable[3] = sumObserved() - bigramTable.sumObserved();

	return bigramTable;
}


ContingencyTable ContingencyTable::gatherObservedNgramData(
	size_t pNgramIndex,
	size_t pNgramLength) const
{
	/* example: cast to 3-element tuple
	 *
	 * each mask is used to sum parts of different table field (accumulate information in bigger table to fit 2x2x2 table.
	 * mask count is equivalent to element count to sum (how many fields in input table must be sum to receive single value in output table).
	 *
	 * Mask has few bits at the beggining equal to 0s. It has as many 0s as output tuple length.
	 * If you will add any value (offset) from 0 to ((2^tuple_length) - 1) to mask then u will be able to sum values for other output table element.
	 * Explained below:
	 *														 	mask-\   /-offset
	 * output 2x2x2 table ( A  B  C) = sum (input_contingency_table[(m + 0)] for m in masks)
	 * output 2x2x2 table (~A  B  C) = sum (input_contingency_table[(m + 1)] for m in masks)
	 * output 2x2x2 table ( A ~B  C) = sum (input_contingency_table[(m + 2)] for m in masks)
	 * output 2x2x2 table (~A ~B  C) = sum (input_contingency_table[(m + 3)] for m in masks)
	 *
	 * output 2x2x2 table ( A  B ~C) = sum (input_contingency_table[(m + 4)] for m in masks)
	 * output 2x2x2 table (~A  B ~C) = sum (input_contingency_table[(m + 5)] for m in masks)
	 * output 2x2x2 table ( A ~B ~C) = sum (input_contingency_table[(m + 6)] for m in masks)
	 * output 2x2x2 table (~A ~B ~C) = sum (input_contingency_table[(m + 7)] for m in masks)
	 *
	 * Mask count is equivalent to: 2^(input_tuple_size - output_tuple_size).
	 *
	 * if ABCD is considered then to count BCD instead of ABC a shift operation on mask must be applied
	 * output 2x2x2 table ( B  C  D) = sum (input_contingency_table[(m + 0) circural_shift 1] for m in masks)
	 * output 2x2x2 table (~B  C  D) = sum (input_contingency_table[(m + 1) circural_shift 1] for m in masks)
	 * output 2x2x2 table ( B ~C  D) = sum (input_contingency_table[(m + 2) circural_shift 1] for m in masks)
	 * ...
	 *
	 * for ABCDE... and so on shift must be bigger:
	 * ABC - shift 0
	 * BCD - shift 1
	 * CDE - shift 2
	 * ...
	 */

	ContingencyTable ngramTable(1 << pNgramLength, ContingencyValue(0.0, 0.0));

	size_t sizeOfTuple 	= tupleSize();
	size_t maskCount 	= (1 << (sizeOfTuple - pNgramLength));
	size_t partCount	= ngramTable.size() - 1;

	for (size_t m = 0; m < maskCount; ++m)
	{
		size_t mask = (m << pNgramLength);
		for (size_t p = 0; p < partCount; ++p)
		{
			size_t tableIndex = utils::wrapShiftLeft(mask | p, pNgramIndex, sizeOfTuple);
			ngramTable[p].observed += mValues[tableIndex].observed;
		}
	}

	/* count ~A ~B ~C ... */
	ngramTable[ngramTable.size() - 1] = sumObserved() - ngramTable.sumObserved();

	return ngramTable;
}


ContingencyTable ContingencyTable::compressObservedToBigram(size_t pDispersionPoint) const
{
	ContingencyTable table(4);

	size_t firstPart = 0;
	for (size_t i = 0; i <= pDispersionPoint; ++i)
	{
		firstPart |= (1 << i);
	}

	size_t secondPart = (size() - 1) ^ firstPart;

	table[0].observed = mValues[0].observed;
	table[1].observed = mValues[firstPart].observed;
	table[2].observed = mValues[secondPart].observed;
	table[3].observed = sumObserved() - table.sumObserved();

	return table;
}


void ContingencyTable::computeExpected(size_t pObservedSum)
{
	size_t sizeOfTuple = tupleSize();

	/* Gather probabilities of x, y, z... */
	std::vector<double> probabilities(sizeOfTuple);
	for (size_t i = 0; i < sizeOfTuple; ++i)
	{
		probabilities[i] = (gatherObservedNgramData(i, 1)[0].observed / pObservedSum);
	}

	/*
	 * expected value is equal to:
	 * N * (p(x) or !p(x)) * (p(y) or !p(y)) * ...
	 */
	for (size_t diffMask = 0; diffMask < size(); ++diffMask)
	{
		mValues[diffMask].expected = pObservedSum;
		for (size_t e = 0; e < sizeOfTuple; ++e)
		{
			/* check if bit on i-th position is not set then multiply by p(x) else !p(x) */
			if (((1 << e) & diffMask) == 0)
			{
				mValues[diffMask].expected *= (probabilities[e]);
			}
			else
			{
				mValues[diffMask].expected *= (1.0 - probabilities[e]);
			}
		}

		/* kind of smoothing - unnecessary */
		/*
		if (mValues[diffMask].expected == 0.0)
		{
			mValues[diffMask].expected = std::numeric_limits<double>::min();
		}
		*/
	}
}


void ContingencyTable::computeExpected()
{
	computeExpected(sumObserved());
}


double ContingencyTable::sumObserved() const
{
	double sum = 0.0;
	for (size_t i = 0; i < mValues.size(); ++i)
	{
		sum += mValues[i].observed;
	}
	return sum;
}


double ContingencyTable::sumExpected() const
{
	double sum = 0.0;
	for (size_t i = 0; i < mValues.size(); ++i)
	{
		sum += mValues[i].expected;
	}
	return sum;
}


/*
 *	return string:
 *	[obs0:exp0,obs1:exp1,...,obsN:expN]
 */
std::string ContingencyTable::createReprezentation() const
{
	std::stringstream str;
	utils::setStreamMaxDoublePrecision(str);
	str << '[';
	for (size_t i = 0; i < mValues.size(); ++i)
	{
		str << mValues[i].observed << ':' << mValues[i].expected;
		if (i < mValues.size() - 1)
		{
			str << ',';
		}
	}
	str << ']';
	return str.str();
}


	}
}
