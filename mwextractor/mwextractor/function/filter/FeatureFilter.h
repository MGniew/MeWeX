
#pragma once

#include "Filter.h"


namespace function
{
	namespace filter
	{


class FeatureFilter : public Filter
{
public:
	typedef std::vector<std::string> StringParameterVector;

	enum class OperatorType
	{
		EQUAL = 0,
		LOWER,
		GREATER,
		LOWER_EQUAL,
		GREATER_EQUAL,
		IN
	};

private:
	typedef bool (FeatureFilter::*Operator)(TupleId pTupleId) const;

public:
	FeatureFilter(
		OperatorType 					pOperatorType,
		StringParameterVector const&	pParameters);

	FeatureFilter();
	FeatureFilter(FeatureFilter&& 					pFilter) 	= default;
	FeatureFilter(FeatureFilter const& 				pFilter) 	= default;
	FeatureFilter& operator=(FeatureFilter&& 		pFilter) 	= default;
	FeatureFilter& operator=(FeatureFilter const& 	pFilter) 	= default;

	virtual ~FeatureFilter() = default;


	virtual StringParameterMap retrieveFunctionParameters() const;

	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual bool meets(TupleId pTupleId) const override;


	OperatorType 	getOperatorType() 		const;
	std::string 	decodeOperatorType() 	const;

	virtual std::string reprezentation() 	const override;
	virtual std::string usage() 			const override;


protected:
	std::vector<std::string> const& getParameters() const;
	std::vector<std::string>& 		getParameters();

	std::string	const&				getParameterFile() const;
	std::string&					getParameterFile();

	virtual bool equal(TupleId pTupleId) 		const;
	virtual bool lower(TupleId pTupleId) 		const;
	virtual bool greater(TupleId pTupleId) 		const;
	virtual bool lowerEqual(TupleId pTupleId) 	const;
	virtual bool greaterEqual(TupleId pTupleId) const;
	virtual bool in(TupleId pTupleId) 			const;


private:
	OperatorType 	decodeOperatorName(std::string const& pOperatorName) const;
	void 			assignOperator(OperatorType pOperatorType);


private:
	std::vector<std::string> 	mParameters;
	std::string					mFile;
	OperatorType				mOperatorType;
	Operator					mOperator;
};


	}
}
