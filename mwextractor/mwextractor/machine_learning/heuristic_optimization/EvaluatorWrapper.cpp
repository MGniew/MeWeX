
#include <boost/algorithm/string.hpp>

#include "../../exception/Exception.h"

#include "EvaluatorWrapper.h"

#include "Evaluator.h"
#include "Step.h"
#include "Timer.h"
#include "HypersphereNeighbourhood.h"

#include "RandomSearch/RandomSearch.h"
#include "RandomSearch/ReportRS.h"

#include "HillClimbing/Neighbourhood.h"
#include "HillClimbing/ReportHC.h"
#include "HillClimbing/HillClimbing.h"

#include "TabuSearch/TabuSearch.h"
#include "TabuSearch/NeighbourhoodTS.h"
#include "TabuSearch/ReportTS.h"
#include "TabuSearch/TabuList.h"

#include "SimulatedAnnealing/SimulatedAnnealing.h"
#include "SimulatedAnnealing/Geometric.h"
#include "SimulatedAnnealing/Metropolis.h"
#include "SimulatedAnnealing/ReportSA.h"

#include "EvolutionaryAlgorithm/EvolutionaryAlgorithm.h"
#include "EvolutionaryAlgorithm/Population.h"
#include "EvolutionaryAlgorithm/UniformCrossover.h"
#include "EvolutionaryAlgorithm/Mutation.h"
#include "EvolutionaryAlgorithm/TournamentSelection.h"
#include "EvolutionaryAlgorithm/ReportEA.h"

#include "PSO/ParticleSwarmOptimization.h"
#include "PSO/ReportPSO.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator)
{

}


EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint,
	RSCallPolicy const& 	pPolicy)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator),
	mRSCPA(pPolicy)
{

}


EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint,
	HCCallPolicy const& 	pPolicy)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator),
	mHCCPA(pPolicy)
{

}


EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint,
	TSCallPolicy const& 	pPolicy)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator),
	mTSCPA(pPolicy)
{

}


EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint,
	SACallPolicy const& 	pPolicy)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator),
	mSACPA(pPolicy)
{

}


EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint,
	EACallPolicy const& 	pPolicy)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator),
	mEACPA(pPolicy)
{

}

EvaluatorWrapper::EvaluatorWrapper(
	EvaluatorPtrR const&	pEvaluator,
	MethodType 				pMethodType,
	Point const&			pStartPoint,
	PSOCallPolicy const& 	pPolicy)
:
	mMethodType(pMethodType),
	mStartPoint(pStartPoint),
	mEvaluator(pEvaluator),
	mPSOCPA(pPolicy)
{

}


auto EvaluatorWrapper::parseMethodType(std::string const& pMethod) -> MethodType
{
	if(boost::iequals(pMethod, "RS"))
	{
		return RS;
	}
	else if(boost::iequals(pMethod, "HC"))
	{
		return HC;
	}
	else if(boost::iequals(pMethod, "TS"))
	{
		return TS;
	}
	else if(boost::iequals(pMethod, "SA"))
	{
		return SA;
	}
	else if(boost::iequals(pMethod, "EA"))
	{
		return EA;
	}
	else if(boost::iequals(pMethod, "PSO"))
	{
		return PSO;
	}

	return EMPTY;
}


void EvaluatorWrapper::setRandomSearchPolicy(RSCallPolicy const& pPolicy)
{
	mRSCPA = pPolicy;
}


void EvaluatorWrapper::setHillClimbingPolicy(HCCallPolicy const& pPolicy)
{
	mHCCPA = pPolicy;
}


void EvaluatorWrapper::setTabuSearchPolicy(TSCallPolicy const& pPolicy)
{
	mTSCPA = pPolicy;
}


void EvaluatorWrapper::setSimulatedAnnealingPolicy(SACallPolicy const& pPolicy)
{
	mSACPA = pPolicy;
}


void EvaluatorWrapper::setEvolutionaryAlgorithmPolicy(EACallPolicy const& pPolicy)
{
	mEACPA = pPolicy;
}

void EvaluatorWrapper::setParticleSwarmOptimizationPolicy(PSOCallPolicy const& pPolicy)
{
	mPSOCPA = pPolicy;
}


auto EvaluatorWrapper::start() -> Point
{
	typedef RandomSearch::RandomSearch<
				RandomSearch::CallPoliciesArgumentsRS,
				unsigned int,
				Step,
				time_t,
				Timer,
				RandomSearch::ReportRS> RSAlgorithm;

	typedef HillClimbing::HillClimbing<
				HillClimbing::CallPoliciesArgumentsHC,
				HypersphereNeighbourhood,
				HillClimbing::Neighbourhood,
				unsigned int,
				Step,
				time_t,
				Timer,
				HillClimbing::ReportHC> HCAlgorithm;

	typedef TabuSearch::TabuSearch<
				TabuSearch::CallPoliciesArgumentsTS,
				HypersphereNeighbourhood,
				TabuSearch::NeighbourhoodTS,
				TabuSearch::TabuList,
				unsigned int,
				Step,
				time_t,
				Timer,
				TabuSearch::ReportTS> TSAlgorithm;

	typedef SimulatedAnnealing::SimulatedAnnealing<
				SimulatedAnnealing::CallPoliciesArgumentsSA,
				HypersphereNeighbourhood,
				double,
				SimulatedAnnealing::Geometric,
				SimulatedAnnealing::Metropolis,
				unsigned int,
				Step,
				time_t,
				Timer,
				SimulatedAnnealing::ReportSA> SAAlgorithm;

	typedef EvolutionaryAlgorithm::EvolutionaryAlgorithm<
				EvolutionaryAlgorithm::CallPoliciesArgumentsEA,
				EvolutionaryAlgorithm::Population,
				EvolutionaryAlgorithm::TournamentSelection,
				EvolutionaryAlgorithm::Mutation,
				EvolutionaryAlgorithm::UniformCrossover,
				unsigned int,
				Step,
				time_t,
				Timer,
				EvolutionaryAlgorithm::ReportEA> EAAlgorithm;

	typedef particle_swarm_optimization::ParticleSwarmOptimization<
				particle_swarm_optimization::CallPoliciesArgumentsPSO,
				unsigned int,
				Step,
				time_t,
				Timer,
				particle_swarm_optimization::ReportPSO> PSOAlgorithm;

    try
    {
        switch(mMethodType)
        {
			case RS:
			{
				return RSAlgorithm(mStartPoint, mEvaluator, mRSCPA).start();
			}
			break;
			case HC:
			{
				return HCAlgorithm(mStartPoint, mEvaluator, mHCCPA).start();
			}
			break;
			case TS:
			{
				return TSAlgorithm(mStartPoint, mEvaluator, mTSCPA).start();
			}
			break;
			case SA:
			{
				return SAAlgorithm(mStartPoint, mEvaluator, mSACPA).start();
			}
			break;
			case EA:
			{
				return EAAlgorithm(mStartPoint, mEvaluator, mEACPA).start();
			}
			break;
			case PSO:
			{
				return PSOAlgorithm(mStartPoint, mEvaluator, mPSOCPA).start();
			}
			break;
			default:
			{
				EXCEPTION(false, "EvaluatorWrapper::start(): Method type not set.");
			}
        }
    }
    catch(std::exception const& pException)
    {
        std::cerr << pException.what() << std::endl;
        throw;
    }
    catch(...)
    {
        std::cerr << "ERROR: An unknown exception was thrown." << std::endl;
        throw;
    }

    EXCEPTION(false, "EvaluatorWrapper::start(): It is impossible...");
    return Point();
}


	}
}


