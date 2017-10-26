
#pragma once

#include "QualityMatrix.h"
#include "../association/Extractor.h"
#include "../../structure/io/WordnetRelevantChainWordSetLoader.h"


namespace function
{
	namespace quality
	{


class QualityFunction : public Function
{
public:
	typedef structure::io::WordnetRelevantChainWordSetLoader	Loader;
	typedef Loader::RelevantTupleIdSet							RelevantTupleIdSet;
	typedef structure::storage::KBestTupleList					KBestTupleList;


public:
	QualityFunction(size_t pLength = std::numeric_limits<size_t>::max());

	QualityFunction(QualityFunction&& 					pQualityFunction)	= default;
	QualityFunction(QualityFunction const& 				pQualityFunction) 	= default;
	QualityFunction& operator=(QualityFunction&& 		pQualityFunction)	= default;
	QualityFunction& operator=(QualityFunction const& 	pQualityFunction)	= default;

	virtual ~QualityFunction() = default;


	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;


	virtual std::string reprezentation() 	const override;
	virtual std::string usage() 			const override;


	virtual QualityMatrix operator()(
		KBestTupleList const&		pKBest,
		RelevantTupleIdSet const&	pRelevantSet,
		TupleStorageConst const&	pStorage) const = 0;

	size_t 			getLength() 		const;
	virtual size_t 	getResultRowSize()	const;

private:
	size_t mLength;
};


	}
}
