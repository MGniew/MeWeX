/*
 * Config.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include <vector>
#include <string>

#include <boost/program_options.hpp>

#include "../AbstractConfig.h"
#include "../../function/association/AssociationFunction.h"


namespace program
{
	namespace feature_maker
	{


class Config : public AbstractConfig
{
public:
	typedef function::association::AssociationFunction	AssociationFunction;
	typedef std::shared_ptr<AssociationFunction> 		AssociationFunctionPtrS;

public:
	std::string	inputDirectory;
	std::string outputFile;

	std::string	featureGenerator;
	std::string scoreFunction;

	std::string	fileWithRelevantSet;
	std::string	fileWithContingencyTable;
	std::string	fileWithTupleFrequencyIndex;

	// rankerData: important for rankers which scores are based on order (for ex. WOrder)
	std::string validStatisticTupleFilter;
	std::string	extractionFilter;

	bool		tupleElementsFixedOrder;

	size_t		indexTableCreationPolicy;
	size_t		threadCount;


protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
