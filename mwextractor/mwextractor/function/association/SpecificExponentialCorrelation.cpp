
#include <cmath>
#include <sstream>

#include "../../utils/Textual.h"
#include "SpecificExponentialCorrelation.h"


namespace function
{
	namespace association
	{


auto SpecificExponentialCorrelation::copy() const -> AssociationMeasurePtrS
{
	return AssociationMeasurePtrS(new SpecificExponentialCorrelation(*this));
}


SpecificExponentialCorrelation::SpecificExponentialCorrelation(double pExponent)
:
	mExponent(pExponent)
{

}


double SpecificExponentialCorrelation::getExponent() const
{
	return mExponent;
}


double SpecificExponentialCorrelation::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const& pContingencyTable) const
{
	size_t tupleSize	= pContingencyTable.tupleSize();
	double oneByDiv		= 1.0 / pContingencyTable.sumObserved();

	double nominator 	= pContingencyTable[0].observed * oneByDiv;
	double denominator	= 1.0;

	for (size_t i = 0; i < tupleSize; ++i)
	{
		double elementFrequency = pContingencyTable.gatherObservedNgramData(i, 1)[0].observed;
		denominator *= elementFrequency * oneByDiv;
	}

	return log2(std::pow(nominator, getExponent()) / denominator);
}


auto SpecificExponentialCorrelation::retrieveFunctionParameters() const -> StringParameterMap
{
	return {{"e", "1.0"}};
}


void SpecificExponentialCorrelation::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	mExponent = utils::toDouble(pNamedParameters.find("e")->second);
}


std::string	SpecificExponentialCorrelation::name() const
{
	return "specific_exponential_correlation";
}


std::string SpecificExponentialCorrelation::reprezentation() const
{
	std::stringstream str;
	str << name() << "(e=" << mExponent << ')';
	return str.str();
}


std::string SpecificExponentialCorrelation::usage() const
{
	std::stringstream str;
	str << name() << "(e=<exponent_double_value>)";
	return str.str();
}


	}
}
