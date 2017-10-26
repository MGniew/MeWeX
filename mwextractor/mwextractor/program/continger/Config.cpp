/*
 * Config.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include <iostream>

#include "../../utils/Debug.h"
#include "Config.h"
#include "../../structure/builder/ContingencyTableStorageBuilder.h"


namespace program
{
	namespace continger
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 				"Prints this message.")
		("storage_directory,i", bpo::value<std::string>(), "Storage directory.")
		("output_filename,o", 	bpo::value<std::string>(), "Output filename for contingency table, will be stored in storage folder.")
		("filter,f",			bpo::value<std::string>()->default_value(""), "Only tuples which meets filter requirements will be used to create contingency table.");
	return options;
}


std::string Config::helpMessage() const
{
	return 	"Continger by Michal Wendelberger.\n"
			"Used to create contingency table.\n.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("storage_directory") == 0)
	{
		setError("Storage directory not set.", -1);
	}
	else if (pMap.count("output_filename") == 0)
	{
		setError("Output file not set.", -2);
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	storageDirectory 	= pMap["storage_directory"].as<std::string>();
	outputFilename	 	= pMap["output_filename"].as<std::string>();
	filter				= pMap["filter"].as<std::string>();
}


	}
}


