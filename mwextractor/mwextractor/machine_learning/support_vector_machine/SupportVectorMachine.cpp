
#include <sstream>
#include <cstdlib>

#include "../../utils/Textual.h"
#include "../../utils/Debug.h"

#include "SupportVectorMachine.h"


namespace machine_learning
{
	namespace support_vector_machine
	{


SupportVectorMachine::SupportVectorMachine()
:
	mModelFile(""),
	mSvmType(2),
	mKernelType(0)
{

}


auto SupportVectorMachine::clone() const -> ClassifierPtrS
{
	return ClassifierPtrS(new SupportVectorMachine(*this));
}


auto SupportVectorMachine::retrieveFunctionParameters() const -> StringParameterMap
{
	return
	{
		{"model", "none"},
		{"svm_type", "2"},
		{"kernel_type", "0"},
		{"workspace", ""},
		{"unique_identifier", ""}
	};
}


void SupportVectorMachine::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	auto iter = pParameters.find("workspace");
	EXCEPTION(iter != pParameters.end(), "No workspace specified.");

	mWorkspace 	= iter->second;
	mModelFile 	= pParameters.find("model")->second;
	mIdentifier = pParameters.find("unique_identifier")->second;

	if (mModelFile.empty())
	{
		XASSERT(
			pParameters.find("svm_type") != pParameters.end(),
			"SupportVectorMachine::build(): SVM type parameter not set.");
		XASSERT(
			pParameters.find("kernel_type") != pParameters.end(),
			"SupportVectorMachine::build(): Kernel type parameter not set.");

		mSvmType 	= utils::toSizeT(pParameters.find("svm_type")->second);
		mKernelType	= utils::toSizeT(pParameters.find("kernel_type")->second);
	}
}


std::string	SupportVectorMachine::name() const
{
	return "support_vector_machine";
}


std::string	SupportVectorMachine::reprezentation() const
{
	std::stringstream str;
	utils::setStreamMaxDoublePrecision(str);
	str << name() << "(svm_type=" << mSvmType << ",kernel_type=" << mKernelType << ",workspace=" << mWorkspace << ')';
	return str.str();
}


void SupportVectorMachine::construct(TupleIdVector const& pTrainData)
{
	std::stringstream trainStr;
	trainStr << mWorkspace << '/' << mIdentifier << ".trs";
	std::string trainSet = trainStr.str();

	std::stringstream mdlStr;
	mdlStr << mWorkspace << '/' << mIdentifier << ".mdl";
	std::string modelFile = mdlStr.str();

	std::stringstream callString;
	callString << mWorkspace << "/svm-train"
		<< " -s " << mSvmType
		<< " -t " << mKernelType
		<< " -q"
		<< ' ' << trainSet
		<< ' ' << modelFile;

	int retCode = std::system(callString.str().c_str());
}


double SupportVectorMachine::rankInstance(Instance const& pInstance) const
{

}


double SupportVectorMachine::rank(TupleId pTupleId) const
{
	return rankInstance(getRankerData()->constructInstance(pTupleId));
}


double SupportVectorMachine::rankTuple(TupleT const& pTupleT) const
{
	return rankInstance(getRankerData()->constructInstance(pTupleT));
}


size_t SupportVectorMachine::classify(Instance const& pInstance) const
{
	EXCEPTION(false, "Classify function is not implemented.");
}


size_t SupportVectorMachine::classify(TupleId pTupleId) const
{
	return classify(getRankerData()->constructInstance(pTupleId));
}


size_t SupportVectorMachine::classify(TupleT const& pTupleT) const
{
	return classify(getRankerData()->constructInstance(pTupleT));
}


	}
}
