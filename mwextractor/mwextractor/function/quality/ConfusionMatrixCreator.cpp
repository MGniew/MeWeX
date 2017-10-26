
#include "ConfusionMatrixCreator.h"


namespace function
{
	namespace quality
	{


ConfusionMatrixCreator::ConfusionMatrixCreator(size_t pLength)
:
	QualityFunction(pLength)
{

}


auto ConfusionMatrixCreator::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length 	= std::min(getLength(), pKBest.size());
	size_t size		= pStorage.getDistinctTupleCount();

	QualityMatrix mtx(length, 4, 0.0);

	/******************************************************************************\
	| idx	| interp	| formula				| comment
	|------------------------------------------------------------------------------
	| 0 	| TP 		| relevants				|
	| 1 	| FN 		| length - TP			|
	| 2 	| FP 		| FN					| // it will be equal to FN i think
	| 3 	| TN 		| size - length - FN	|
	-------------------------------------------------------------------------------
	\******************************************************************************/
	double relevants = 0.0;
	for (size_t i = 0; i < length; ++i)
	{
		if (pRelevantSet.has(pKBest[i].element))
		{
			++relevants;
		}

		mtx[i][0] = relevants;
		mtx[i][1] = length - mtx[i][0];
		mtx[i][2] = mtx[i][1];
		mtx[i][3] = size - length - mtx[i][2];
	}

	return mtx;
}


std::string	ConfusionMatrixCreator::name() const
{
	return "confusion_matrix_creator";
}


size_t ConfusionMatrixCreator::getResultRowSize() const
{
	return 4;
}


	}
}
