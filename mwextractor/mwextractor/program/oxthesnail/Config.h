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
	std::vector<std::string> 	associationVectorFunctions;
	std::vector<std::string> 	aggregationFunctions;
	std::vector<std::string> 	qualityFunctions;

	std::string					fileWithRelevantSet;
	std::string					fileWithContingencyTable;
	std::string					fileWithTupleFrequencyIndex;
	std::string					filter;
	bool						tupleElementsFixedOrder;

	size_t						indexTableCreationPolicy;
	size_t						kbestLength;
	size_t						threadCount;
	bool						speedItUp;

	std::string					tagsetName;
	std::string					readerName;
	std::string					fileWithWcclOperators;
	std::string					fileWithCorporas;


protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
