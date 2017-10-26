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
	namespace web_tool
	{


class Config : public AbstractConfig
{
public:
	std::string 				corpusFilepathList;
	std::string 				tagsetName;
	std::string 				readerName;
	std::vector<std::string> 	wcclRelationsFile;
	std::string					kbestFilepath;

	std::string statisticDataFilter;
	std::string extractionDataFilter;
	std::string dispersionFunction;

	std::string ranker;
	std::string aggregator;
	std::string features;
	std::string featuresPreprocessor;

	size_t		rankLength;

	bool		extractOrths;

protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
