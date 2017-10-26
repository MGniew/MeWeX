
#pragma once

#include <memory>

#include "Config.h"

#include "../../function/score/ScoreFunction.h"
#include "../../function/association/RankerData.h"

#include "../../machine_learning/multilayer_perceptron/MultilayerPerceptron.h"


namespace program
{
	namespace teacher
	{


class Teacher
{
public:
	typedef machine_learning::multilayer_perceptron::MultilayerPerceptron 	MultilayerPerceptron;
	typedef std::shared_ptr<MultilayerPerceptron>							MultilayerPerceptronPtrS;
	typedef std::vector<MultilayerPerceptronPtrS>							MultilayerPerceptronPtrSVector;

	typedef function::association::RankerData								RankerData;
	typedef std::shared_ptr<RankerData>										RankerDataPtrS;

	typedef std::shared_ptr<function::score::ScoreFunction>					ScoreFunctionPtrS;

public:
	void teach(Config const& pConfig);

private:
	RankerDataPtrS 	loadData() 									const;
	void			teach(RankerDataPtrS const& pRankerData)	const;

private:
	Config mConfig;
};


	}
}
