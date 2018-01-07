
#include <sstream>
#include <fstream>

#include "../../utils/Debug.h"
#include "../../utils/Textual.h"
#include "../../utils/Time.h"
#include "../../utils/File.h"

#include "../../function/FunctionFactory.h"

#include "LinearCombination.h"

#include "DoubleParameter.h"
#include "DoubleEvaluationPerformance.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


LinearCombination::LinearCombination(
	std::string const&					pMethodName,
	std::string const&					pMethodsConfig,
	VectorAssociationMeasurePtrS const& pVectorAssociationFunction,
	AggregationFunctionPtrS const& 		pAggregationFunction,
	QualityFunctionPtrS	const& 			pQualityFunction,
	size_t								pKBestQualityLength,
	size_t 								pWorkerThreadCount,
	double								pMinParameterValue,
	double								pMaxParameterValue,
	double								pParameterStepValue)
:
	mMethodName(pMethodName),
	mMethodsConfig(pMethodsConfig),
	mVectorAssociationFunction(pVectorAssociationFunction),
	mAggregationFunction(pAggregationFunction),
	mQualityFunction(pQualityFunction),
	mKBestQualityLength(pKBestQualityLength),
	mWorkerThreadCount(pWorkerThreadCount),
	mMinParameterValue(pMinParameterValue),
	mMaxParameterValue(pMaxParameterValue),
	mParameterStepValue(pParameterStepValue),
	mTempTupleData(nullptr)
{

}


LinearCombination::LinearCombination(LinearCombination const& pLinearCombination)
:
	mMethodName(pLinearCombination.mMethodName),
	mMethodsConfig(pLinearCombination.mMethodsConfig),
	mVectorAssociationFunction(pLinearCombination.mVectorAssociationFunction->copy()),
	mAggregationFunction(pLinearCombination.mAggregationFunction),
	mQualityFunction(pLinearCombination.mQualityFunction),
	mKBestQualityLength(pLinearCombination.mKBestQualityLength),
	mWorkerThreadCount(pLinearCombination.mWorkerThreadCount),
	mTempTupleData(pLinearCombination.mTempTupleData),
	mMinParameterValue(pLinearCombination.mMinParameterValue),
	mMaxParameterValue(pLinearCombination.mMaxParameterValue),
	mParameterStepValue(pLinearCombination.mParameterStepValue)
{

}


LinearCombination& LinearCombination::operator=(LinearCombination const& pLinearCombination)
{
	mMethodName					= pLinearCombination.mMethodName;
	mMethodsConfig				= pLinearCombination.mMethodsConfig;
	mVectorAssociationFunction 	= pLinearCombination.mVectorAssociationFunction->copy();
	mAggregationFunction 		= pLinearCombination.mAggregationFunction;
	mQualityFunction 			= pLinearCombination.mQualityFunction;
	mKBestQualityLength 		= pLinearCombination.mKBestQualityLength;
	mWorkerThreadCount 			= pLinearCombination.mWorkerThreadCount;
	mTempTupleData  			= pLinearCombination.mTempTupleData;
	mMinParameterValue			= pLinearCombination.mMinParameterValue;
	mMaxParameterValue			= pLinearCombination.mMaxParameterValue;
	mParameterStepValue			= pLinearCombination.mParameterStepValue;
	return *this;
}


void LinearCombination::initialize(RankerDataPtrS const& pRankerDataPtrS)
{
	AbstractRanker::initialize(pRankerDataPtrS);
	mVectorAssociationFunction->initialize(getRankerData());
	construct();
}


auto LinearCombination::retrieveFunctionParameters() const -> StringParameterMap
{
	return
	{
		{"method", "EA"},
		{"methods_config", ""},
		{"vam", ""},
		{"aggregator", ""},
		{"quality_function", ""},
		{"quality_kbest_length", "-1"},
		{"threads", "1"},
		{"min_value", "-1.0"},
		{"max_value", "1.0"},
		{"step_value", "0.05"}
	};
}


void LinearCombination::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	function::FunctionFactory ff;

	mMethodName			 		= pParameters.find("method")->second;
	mMethodsConfig	 			= pParameters.find("methods_config")->second;

	mVectorAssociationFunction 	= ff.createVectorAssociationMeasure(pParameters.find("vam")->second);
	mAggregationFunction 		= ff.createAggregationFunction(pParameters.find("aggregator")->second);
	mQualityFunction 			= ff.createQualityFunction(pParameters.find("quality_function")->second);

	mKBestQualityLength 		= utils::toSizeT(pParameters.find("quality_kbest_length")->second);
	mWorkerThreadCount 			= utils::toSizeT(pParameters.find("threads")->second);

	mMinParameterValue 			= utils::toDouble(pParameters.find("min_value")->second);
	mMaxParameterValue			= utils::toDouble(pParameters.find("max_value")->second);
	mParameterStepValue			= utils::toDouble(pParameters.find("step_value")->second);

	mWorkerThreadCount			= utils::toSizeT(pParameters.find("threads")->second);

	mTempTupleData 				= nullptr;
}


std::string LinearCombination::name() const
{
	return "linear_combination";
}


std::string LinearCombination::reprezentation() const
{
	std::stringstream str;
	str << name()
		<< '('
		<< "method=" << mMethodName << ','
		<< "methods_config=" << mMethodsConfig << ','
		<< "vam=" << mVectorAssociationFunction->reprezentation() << ','
		<< "aggregator=" << mAggregationFunction->reprezentation() << ','
		<< "quality_function=" << mQualityFunction->reprezentation() << ','
		<< "quality_kbest_length=" << mKBestQualityLength << ','
		<< "threads=" << mWorkerThreadCount << ','
		<< "min_value=" << mMinParameterValue << ','
		<< "max_value=" << mMaxParameterValue << ','
		<< "step_value=" << mParameterStepValue
		<< ')';
	return str.str();
}


std::string LinearCombination::usage() const
{
	std::stringstream str;
	str << name()
		<< '('
		<< "method=<[RS|HC|TS|SA|EA]method_type>,"
		<< "methods_config=<file_with_methods_config>,"
		<< "vam=<vector_association_measure>,"
		<< "aggregator=<aggregation_function>,"
		<< "quality_function=<quality_function>,"
		<< "quality_kbest_length=<[int_value]length_of_kbest_used_for_quality_function>,"
		<< "threads=<[int_value]max_available_worker_thread_count>,"
		<< "min_value=<[double_value]min_parameter_value>,"
		<< "max_value=<[double_value]max_parameter_value>,"
		<< "step_value=<[double_value]step_parameter_value>"
		<< ')';
	return str.str();
}


void LinearCombination::optimize(TupleIdVector const& pData) const
{
	mTempTupleData = &pData;

	mOptimizationResultMap.clear();
	mEvaluatorWrapper->start();

	mTempTupleData = nullptr;
}


double LinearCombination::evaluateIndividual(Point const& pPoint)
{
	updateWeights(pPoint);

	Extractor::KBestTupleListVector kbestVector = Extractor().extract(
		mVectorAssociationFunction, *mTempTupleData, mKBestQualityLength, mWorkerThreadCount);

	Extractor::KBestTupleList kbest = (*mAggregationFunction)(kbestVector, mWorkerThreadCount);

	function::quality::QualityMatrix quality = (*mQualityFunction)(
		kbest, *getRankerData()->getRelevantTupleIdSet(), *getRankerData()->getMatrixTupleStorage());

	double score = quality.getRowPart(quality.size() - 1, 0);

	mOptimizationResultMap.insert(std::make_pair(score, mAggregationFunction->getWeightVector()));

	return score;
}


void LinearCombination::construct()
{
	Point startPoint = buildStartPoint();

	mEvaluatorWrapper.reset(new EvaluatorWrapper(
		this,
		EvaluatorWrapper::parseMethodType(mMethodName),
		startPoint));

	EvaluatorWrapper::RSCallPolicy rscp;
	rscp.readFromFile(mMethodsConfig);
	rscp.setStartStep(0);
	rscp.setTargetName("target_name");
	rscp.setReportFileName("report_file");
	mEvaluatorWrapper->setRandomSearchPolicy(rscp);

	EvaluatorWrapper::HCCallPolicy hccp;
	hccp.readFromFile(mMethodsConfig);
	hccp.setStartStep(0);
	hccp.setTargetName("target_name");
	hccp.setReportFileName("report_file");
	mEvaluatorWrapper->setHillClimbingPolicy(hccp);

	EvaluatorWrapper::TSCallPolicy tscp;
	tscp.readFromFile(mMethodsConfig);
	tscp.setStartStep(0);
	tscp.setTargetName("target_name");
	tscp.setReportFileName("report_file");
	mEvaluatorWrapper->setTabuSearchPolicy(tscp);

	EvaluatorWrapper::SACallPolicy sacp;
	sacp.readFromFile(mMethodsConfig);
	sacp.setStartStep(0);
	sacp.setTargetName("target_name");
	sacp.setReportFileName("report_file");
	mEvaluatorWrapper->setSimulatedAnnealingPolicy(sacp);

	EvaluatorWrapper::EACallPolicy eacp;
	eacp.readFromFile(mMethodsConfig);
	eacp.setStartStep(0);
	eacp.setTargetName("target_name");
	eacp.setReportFileName("report_file");
	mEvaluatorWrapper->setEvolutionaryAlgorithmPolicy(eacp);

	EvaluatorWrapper::PSOCallPolicy psocp;
	psocp.readFromFile(mMethodsConfig);
	psocp.setStartStep(0);
	psocp.setTargetName("target_name");
	psocp.setReportFileName("report_file");
	mEvaluatorWrapper->setParticleSwarmOptimizationPolicy(psocp);
}


Point LinearCombination::buildStartPoint() const
{
	Point pt;

	BaseParameter* param = nullptr;
	for (size_t i = 0; i < mAggregationFunction->getWeightVector().size(); ++i)
	{
		pt.addParameter(DoubleParameter(
			mVectorAssociationFunction->getAssociationMeasureVector()[i]->reprezentation(),
			std::vector<double>(1, mMinParameterValue),
			std::vector<double>(1, mMaxParameterValue),
			std::vector<double>(1, mAggregationFunction->getWeightVector()[i]),
			std::vector<double>(1, mParameterStepValue)));
	}

	pt.setEvaluationPerformance(DoubleEvaluationPerformance(0.0));

	return pt;
}


void LinearCombination::updateWeights(Point const& pPoint)
{
	for (size_t i = 0; i < pPoint.getNumberOfParameters(); ++i)
	{
		pPoint.getParameterAt(i).getValueAt(0).get(mAggregationFunction->getWeightVector()[i]);
	}
}


	}
}
