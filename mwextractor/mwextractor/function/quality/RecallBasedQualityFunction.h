
#pragma once

#include "QualityFunction.h"


namespace function
{
	namespace quality
	{


class RecallBasedQualityFunction : public QualityFunction
{
public:
	RecallBasedQualityFunction(
		bool 	pUseSourceSize	= true,
		size_t 	pLength 		= std::numeric_limits<size_t>::max());

	RecallBasedQualityFunction(RecallBasedQualityFunction&&					pRecallCurve)	= default;
	RecallBasedQualityFunction(RecallBasedQualityFunction const& 			pRecallCurve) 	= default;
	RecallBasedQualityFunction& operator=(RecallBasedQualityFunction&& 		pRecallCurve)	= default;
	RecallBasedQualityFunction& operator=(RecallBasedQualityFunction const& pRecallCurve)	= default;

	virtual ~RecallBasedQualityFunction() = default;


	bool getUseSourceSize() const;

	void setUseSourceSize(bool pUseSourceSize);


	virtual StringParameterMap retrieveFunctionParameters() const;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);


	virtual std::string reprezentation() 	const override;
	virtual std::string usage() 			const override;



private:
	bool mUseSourceSize;
};


	}
}
