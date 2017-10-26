/*
 * Config.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include <string>

#include <boost/program_options.hpp>

#include "../AbstractConfig.h"


namespace program
{
	namespace judger
	{


class Config : public AbstractConfig
{
public:
	std::string 				storageDirectory;
	std::string					filter;
	std::string					relevantSet;
	bool						tupleElementsFixedOrder;
	std::vector<std::string>	kbestToScoreVector;
	size_t						kbestToScoreMaxLength;
	std::vector<std::string>	qualityFunctions;
	std::string 				outputDirectory;


protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
