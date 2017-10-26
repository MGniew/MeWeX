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
	namespace digger
	{


class Config : public AbstractConfig
{
public:
	typedef function::association::AssociationFunction	AssociationFunction;
	typedef std::shared_ptr<AssociationFunction> 		AssociationFunctionPtrS;

public:
	std::string					inputDirectory;
	std::string 				outputDirectory;

	std::vector<std::string> 	associationFunctions;

	std::vector<std::string> 	vectorAssociationMeasures;
	std::vector<std::string> 	aggregationFunctions;

	std::vector<std::string>	classifiers;
	std::vector<std::string>	features;
	std::vector<std::string>	preprocessors;

	std::vector<std::string> 	qualityFunctions;

	std::string					relevantSetFilepath;
	std::string					contingencyTableStorageFilepath;
	std::string					contingencyTableGeneratorFilepath;

	// rankerData: important for rankers which scores are based on order (for ex. WOrder)
	std::string					validStatisticTupleFilter;

	std::string					extractionFilter;
	bool						tupleElementsFixedOrder;

	size_t						indexTableCreationPolicy;
	size_t						kbestLength;
	size_t						threadCount;

	std::string					tagsetName;
	std::string					readerName;
	std::vector<std::string>	fileWithWcclOperators;
	std::string					fileWithCorporas;

	bool						speedItUp;


protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
