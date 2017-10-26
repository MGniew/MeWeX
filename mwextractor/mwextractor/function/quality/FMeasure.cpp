
#include <sstream>

#include "../../utils/Textual.h"

#include "FMeasure.h"


namespace function
{
	namespace quality
	{


FMeasure::FMeasure(
	double 	pBeta,
	bool 	pUseSourceSize,
	size_t 	pLength)
:
	RecallBasedQualityFunction(pUseSourceSize, pLength),
	mBeta(pBeta)
{

}


auto FMeasure::retrieveFunctionParameters() const -> StringParameterMap
{
	return {
		{"beta", "1"},
		{"use_source_size", "1"}
	};
}


void FMeasure::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	mBeta = utils::toDouble(pParameters.find("beta")->second);
	RecallBasedQualityFunction::build(pParameters, pUnnamedParameters);
}


double FMeasure::valueFor(
	double pPrecision,
	double pRecall) const
{
	double nominator 	= (1.0 + mBeta * mBeta) * pPrecision * pRecall;
	double denominator 	= (mBeta * mBeta * pPrecision) + pRecall;
	return denominator != 0.0 ?
		nominator / denominator :
		0.0;
}


auto FMeasure::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	size_t length = std::min(getLength(), pKBest.size());

	QualityMatrix mtx(length);

	double relevantSize = getUseSourceSize() ?
		pRelevantSet.sourceSize() :
		pRelevantSet.size();

	double relevant	= 0.0;
	for(size_t k = 0; k < length; ++k)
	{
		if (pRelevantSet.has(pKBest[k].element))
		{
			++relevant;
		}
		mtx[k][0] = valueFor(
			relevant / static_cast<double>(k + 1),
			relevant / relevantSize);
	}

	return mtx;
}


std::string FMeasure::name() const
{
	return "f_measure";
}


std::string FMeasure::reprezentation() const
{
	std::stringstream str;
	utils::setStreamMaxDoublePrecision(str);
	str << name() << "(beta=" << mBeta << ",use_source_size=" << (getUseSourceSize() ? '1' : '0') << ')';
	return str.str();
}


	}
}
