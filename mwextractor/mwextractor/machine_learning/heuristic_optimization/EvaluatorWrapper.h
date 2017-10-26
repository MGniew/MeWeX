
#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SimpleIni/SimpleIni.h"

#include "Evaluator.h"
#include "Point.h"

#include "RandomSearch/CallPoliciesArgumentsRS.h"
#include "HillClimbing/CallPoliciesArgumentsHC.h"
#include "TabuSearch/CallPoliciesArgumentsTS.h"
#include "SimulatedAnnealing/CallPoliciesArgumentsSA.h"
#include "EvolutionaryAlgorithm/CallPoliciesArgumentsEA.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


class EvaluatorWrapper
{
public:
	typedef Evaluator*	EvaluatorPtrR;

	typedef RandomSearch::CallPoliciesArgumentsRS 			RSCallPolicy;
	typedef HillClimbing::CallPoliciesArgumentsHC 			HCCallPolicy;
	typedef TabuSearch::CallPoliciesArgumentsTS 			TSCallPolicy;
	typedef SimulatedAnnealing::CallPoliciesArgumentsSA 	SACallPolicy;
	typedef EvolutionaryAlgorithm::CallPoliciesArgumentsEA 	EACallPolicy;

	enum MethodType
	{
		RS, // Random Search
	    HC, // Hill Climbing
	    TS, // Tabu Search
	    SA, // Simulated Annealing
	    EA,  // Evolutionary Algorithm
	    EMPTY
	};

public:
	static MethodType parseMethodType(std::string const& pMethod);

public:
	EvaluatorWrapper(
		EvaluatorPtrR const&	pEvaluator,
		MethodType 				pMethodType,
		Point const&			pStartPoint);

	EvaluatorWrapper(
		EvaluatorPtrR const&	pEvaluator,
		MethodType 				pMethodType,
		Point const&			pStartPoint,
		RSCallPolicy const& 	pPolicy);

	EvaluatorWrapper(
		EvaluatorPtrR const&	pEvaluator,
		MethodType 				pMethodType,
		Point const&			pStartPoint,
		HCCallPolicy const& 	pPolicy);

	EvaluatorWrapper(
		EvaluatorPtrR const&	pEvaluator,
		MethodType 				pMethodType,
		Point const&			pStartPoint,
		TSCallPolicy const& 	pPolicy);

	EvaluatorWrapper(
		EvaluatorPtrR const&	pEvaluator,
		MethodType 				pMethodType,
		Point const&			pStartPoint,
		SACallPolicy const& 	pPolicy);

	EvaluatorWrapper(
		EvaluatorPtrR const&	pEvaluator,
		MethodType 				pMethodType,
		Point const&			pStartPoint,
		EACallPolicy const& 	pPolicy);


	Point start();

	void setRandomSearchPolicy(RSCallPolicy const& 			pPolicy);
	void setHillClimbingPolicy(HCCallPolicy const& 			pPolicy);
	void setTabuSearchPolicy(TSCallPolicy const& 			pPolicy);
	void setSimulatedAnnealingPolicy(SACallPolicy const& 	pPolicy);
	void setEvolutionaryAlgorithmPolicy(EACallPolicy const& pPolicy);


private:
	MethodType 		mMethodType;
	Point			mStartPoint;
	EvaluatorPtrR 	mEvaluator;

	RSCallPolicy mRSCPA;
	HCCallPolicy mHCCPA;
	TSCallPolicy mTSCPA;
	SACallPolicy mSACPA;
	EACallPolicy mEACPA;
};


	}
}
