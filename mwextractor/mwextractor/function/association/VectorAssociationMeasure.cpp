
#include <sstream>

#include "../../utils/Textual.h"

#include "../FunctionFactory.h"

#include "VectorAssociationMeasure.h"


namespace function
{
	namespace association
	{


VectorAssociationMeasure::VectorAssociationMeasure(
	AssociationMeasurePtrSVector const& pAssociationMeasurePtrSVector)
:
	mAssociationMeasures(pAssociationMeasurePtrSVector)
{

}


VectorAssociationMeasure::VectorAssociationMeasure(VectorAssociationMeasure const& pVectorAssociationMeasure)
:
	AbstractRanker(pVectorAssociationMeasure)
{
	for (size_t i = 0; i < pVectorAssociationMeasure.size(); ++i)
	{
		mAssociationMeasures.push_back(pVectorAssociationMeasure.getAssociationMeasureVector()[i]->copy());
	}
}


VectorAssociationMeasure& VectorAssociationMeasure::operator=(VectorAssociationMeasure const& pVectorAssociationMeasure)
{
	for (size_t i = 0; i < pVectorAssociationMeasure.size(); ++i)
	{
		mAssociationMeasures.push_back(pVectorAssociationMeasure.getAssociationMeasureVector()[i]->copy());
	}
	setRankerData(pVectorAssociationMeasure.getRankerData());
	return (*this);
}


auto VectorAssociationMeasure::copy() const -> VectorAssociationMeasurePtrS
{
	return VectorAssociationMeasurePtrS(new VectorAssociationMeasure(*this));
}


void VectorAssociationMeasure::initialize(RankerDataPtrS const& pRankerData)
{
	AbstractRanker::initialize(pRankerData);
	for (size_t i = 0; i < mAssociationMeasures.size(); ++i)
	{
		mAssociationMeasures[i]->initialize(pRankerData);
	}
}


auto VectorAssociationMeasure::getAssociationMeasureVector() const -> AssociationMeasurePtrSVector const&
{
	return mAssociationMeasures;
}


auto VectorAssociationMeasure::getAssociationMeasureVector() -> AssociationMeasurePtrSVector&
{
	return mAssociationMeasures;
}


void VectorAssociationMeasure::build(
	StringParameterMap const& pNamedParameters,
	StringParameterMap const& pUnnamedParameters)
{
	FunctionFactory ff;

	mAssociationMeasures.resize(pUnnamedParameters.size());

	for (auto iter = pUnnamedParameters.begin(); iter != pUnnamedParameters.end(); ++iter)
	{
		size_t idx = utils::toSizeT(iter->first);
		mAssociationMeasures[idx] = ff.createAssociationFunction(iter->second);
	}
}


std::vector<double> VectorAssociationMeasure::rankUsingTable(
	TupleId 				pTupleId,
	ContingencyTable const&	pContingencyTable) const
{
	std::vector<double> result(size());

	for (size_t i = 0; i < size(); ++i)
	{
		result[i] = getAssociationMeasureVector()[i]->rankUsingTable(pTupleId, pContingencyTable);
	}

	return result;
}


std::vector<double> VectorAssociationMeasure::rank(TupleId pTupleId) const
{
	return rankUsingTable(
		pTupleId,
		getRankerData()->constructContingencyTable(pTupleId));
}


std::vector<double> VectorAssociationMeasure::operator()(TupleId pTupleId) const
{
	return rank(pTupleId);
}


size_t VectorAssociationMeasure::size() const
{
	return mAssociationMeasures.size();
}


std::string	VectorAssociationMeasure::name() const
{
	return "vector_association_measure";
}


std::string VectorAssociationMeasure::reprezentation() const
{
	std::stringstream str;
	utils::setStreamMaxDoublePrecision(str);
	str << name() << '(';

	for (size_t i = 0; i < mAssociationMeasures.size(); ++i)
	{
		str << mAssociationMeasures[i]->reprezentation();
		if (i < mAssociationMeasures.size() - 1)
		{
			str << ',';
		}
	}

	str << ')';

	return str.str();
}


std::string VectorAssociationMeasure::usage() const
{
	std::stringstream str;
	str << name() << "(<association_function_definition>[,<association_function_definition>][, ...])";
	return str.str();
}


	}
}
