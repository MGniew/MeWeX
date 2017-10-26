
#pragma once

#include "../Classifier.h"


namespace machine_learning
{
	namespace support_vector_machine
	{


class SupportVectorMachine : public Classifier
{
public:
	SupportVectorMachine();

	SupportVectorMachine(SupportVectorMachine&& 				pSupportVectorMachine)  = default;
	SupportVectorMachine(SupportVectorMachine const& 			pSupportVectorMachine)  = default;
	SupportVectorMachine& operator=(SupportVectorMachine&&	 	pSupportVectorMachine)  = default;
	SupportVectorMachine& operator=(SupportVectorMachine const& pSupportVectorMachine)  = default;

	virtual ~SupportVectorMachine() = default;


	virtual ClassifierPtrS clone() const override;

	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters) override;


	virtual std::string	name() 				const override;
	virtual std::string	reprezentation() 	const override;

	virtual void construct(TupleIdVector const& pTrainData) override;

	virtual double rankInstance(Instance const& pInstance) 	const override;
	virtual double rank(TupleId pTupleId)					const override;
	virtual double rankTuple(TupleT const& pTupleT) 		const override;

	virtual size_t classify(Instance const& pInstance) 		const override;
	virtual size_t classify(TupleId pTupleId)				const override;
	virtual size_t classify(TupleT const& pTupleT)			const override;


private:
	size_t 		mSvmType;
	size_t 		mKernelType;
	std::string	mModelFile;
	std::string mWorkspace;
	std::string mIdentifier;
};


	}
}
