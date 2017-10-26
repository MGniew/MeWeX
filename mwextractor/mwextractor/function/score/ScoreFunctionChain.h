
#pragma once

#include <vector>
#include <memory>

#include "ScoreFunction.h"


namespace function
{
	namespace score
	{


class ScoreFunctionChain : public ScoreFunction
{
public:
	typedef std::shared_ptr<ScoreFunction>	ScoreFunctionPtrS;
	typedef std::vector<ScoreFunctionPtrS>	ScoreFunctionPtrSVector;

public:
	ScoreFunctionChain(ScoreFunctionPtrSVector const& pScoreFunctionVector);

	ScoreFunctionChain()															= default;
	ScoreFunctionChain(ScoreFunctionChain&& pScoreFunctionChain)					= default;
	ScoreFunctionChain(ScoreFunctionChain const& pScoreFunctionChain)				= default;
	ScoreFunctionChain& operator=(ScoreFunctionChain&& pScoreFunctionChain)			= default;
	ScoreFunctionChain& operator=(ScoreFunctionChain const& pScoreFunctionChain)	= default;


	virtual void build(
		StringParameterMap const& pNamedParameters,
		StringParameterMap const& pUnnamedParameters) override;

	virtual void buildForFeatures(TupleFeatureStorage const& pFeatureStorage) override;


	void 							setScoreFunctionVector(ScoreFunctionPtrSVector const& pScoreFunctionVector);

	ScoreFunctionPtrS const&	 	getScoreFunction(size_t pIndex) const;
	ScoreFunctionPtrS& 				getScoreFunction(size_t pIndex);

	ScoreFunctionPtrSVector const& 	getScoreFunctionVector() 		const;
	ScoreFunctionPtrSVector& 		getScoreFunctionVector();

	size_t 							size() 							const;

	virtual std::string				name()			 				const override;
	virtual std::string 			reprezentation()			 	const override;
	virtual std::string 			usage()			 				const override;


	virtual void scoreKBest(KBestTupleList& 		pKBest) 			const override;
	virtual void scoreFeatures(TupleFeatureStorage& pFeatureStorage)	const override;


private:
	ScoreFunctionPtrSVector mScoreFunctionVector;
};


	}
}
