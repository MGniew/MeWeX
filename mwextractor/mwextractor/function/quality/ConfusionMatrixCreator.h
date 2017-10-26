
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


class ConfusionMatrixCreator : public QualityFunction
{
public:
	ConfusionMatrixCreator(size_t pLength = std::numeric_limits<size_t>::max());

	ConfusionMatrixCreator(ConfusionMatrixCreator&&					pConfusionMatrixCreator)	= default;
	ConfusionMatrixCreator(ConfusionMatrixCreator const& 			pConfusionMatrixCreator) 	= default;
	ConfusionMatrixCreator& operator=(ConfusionMatrixCreator&& 		pConfusionMatrixCreator)	= default;
	ConfusionMatrixCreator& operator=(ConfusionMatrixCreator const& pConfusionMatrixCreator)	= default;

	virtual ~ConfusionMatrixCreator() = default;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const override;

	virtual std::string	name() const override;

	virtual size_t getResultRowSize() const override;
};


	}
}
