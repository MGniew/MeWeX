
#pragma once

#include "DispersionFunction.h"


namespace function
{
	namespace dispersion
	{


class TermFrequencyInverseDocumentFrequency : public DispersionFunction
{
public:
	typedef structure::storage::FrequencyStorage FrequencyStorage;

public:
	TermFrequencyInverseDocumentFrequency()																									= default;
	TermFrequencyInverseDocumentFrequency(TermFrequencyInverseDocumentFrequency&& 					pTermFrequencyInverseDocumentFrequency)	= default;
	TermFrequencyInverseDocumentFrequency(TermFrequencyInverseDocumentFrequency const& 				pTermFrequencyInverseDocumentFrequency)	= default;
	TermFrequencyInverseDocumentFrequency& operator=(TermFrequencyInverseDocumentFrequency&& 		pTermFrequencyInverseDocumentFrequency)	= default;
	TermFrequencyInverseDocumentFrequency& operator=(TermFrequencyInverseDocumentFrequency const& 	pTermFrequencyInverseDocumentFrequency)	= default;

	virtual ~TermFrequencyInverseDocumentFrequency() = default;


	virtual double disperse(TupleId pTupleId) const override;

	virtual std::string	name() const override;
};


	}
}
