/*
 * Config.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include "Config.h"


namespace program
{
	namespace metatool
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help", "Prints this message.");

	return options;
}


std::string Config::helpMessage() const
{
	return "MetaTool by Michal Wendelberger.";
}


void Config::validateParameters(VariableMap& pMap)
{

}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{

}


	}
}


