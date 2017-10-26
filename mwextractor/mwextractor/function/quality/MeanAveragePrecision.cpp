
#include "../../utils/Textual.h"

#include "MeanAveragePrecision.h"


namespace function
{
	namespace quality
	{


MeanAveragePrecision::MeanAveragePrecision(
	size_t pLength,
	double pFrom,
	double pTo)
:
	AveragePrecisionRecallCurve(pLength),
	mFrom(pFrom),
	mTo(pTo)
{

}


auto MeanAveragePrecision::retrieveFunctionParameters() const -> StringParameterMap
{
	return {
		{"length", "-1"},
		{"from", "0.0"},
		{"to", "1.0"}
	};
}


void MeanAveragePrecision::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	AveragePrecisionRecallCurve::build(pNamedParameters, pUnnamedParameters);

	mFrom = utils::toDouble(pNamedParameters.find("from")->second);
	mTo = utils::toDouble(pNamedParameters.find("to")->second);
}


auto MeanAveragePrecision::operator()(
	KBestTupleList const&		pKBest,
	RelevantTupleIdSet const&	pRelevantSet,
	TupleStorageConst const&	pStorage) const -> QualityMatrix
{
	QualityMatrix mtx = AveragePrecisionRecallCurve::operator()(pKBest, pRelevantSet, pStorage);
	QualityMatrix rmtx(1);

	size_t from = mFrom * static_cast<double>(mtx.size());
	size_t to = mTo * static_cast<double>(mtx.size());
	double diff = static_cast<double>(to - from + 1);
	while (from < to)
	{
		rmtx.getRowPart(0, 0) += mtx.getRowPart(from, 0);
		++from;
	}

	rmtx.getRowPart(0, 0) /= diff;
	return rmtx;
}


std::string	MeanAveragePrecision::name() const
{
	return "mean_average_precision";
}


std::string MeanAveragePrecision::reprezentation() const
{
	std::stringstream str;
	str << name() << "(length=" << getLength() << ",from=" << mFrom << ",to=" << mTo << ')';
	return str.str();
}


	}
}
