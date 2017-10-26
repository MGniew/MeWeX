/*
 * Config.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include <iostream>

#include "../../utils/Debug.h"
#include "Config.h"


namespace program
{
	namespace cover
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 								"Prints this message.")

		("input_directory,I", 					bpo::value<std::string>(), "Full path to input directory.")
		("output_stats_file,s",					bpo::value<std::string>(), "Stats output filename.")
		("output_relevant_set_file,r",			bpo::value<std::string>(), "Cover output filename.")

		("relevant_set,R", 						bpo::value<std::string>(), "Relevant tuple set used in computation.")
		("filter,F",							bpo::value<std::string>()->default_value(""), "Filter used in relevant set creation only (cover will be computed for all relations anyway).")
		("tuple_elements_fixed_order,e",		bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.");

	return options;
}


std::string Config::helpMessage() const
{
	return "Cover by Michal Wendelberger.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_directory") == 0)
	{
		setError("Input directory not set.", -1);
	}
	else if (pMap.count("output_stats_file") == 0)
	{
		setError("Output stats file must be set.", -2);
	}
	else if (pMap.count("output_relevant_set_file") == 0)
	{
		setError("Output relevant set file must be set.", -3);
	}
	else if (pMap.count("relevant_set") == 0)
	{
		setError("Relevant set not set.", -4);
	}

	if (pMap.count("filter") == 0)
	{
		std::cerr << "Filter not set, will compute for whole storage." << std::endl;
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputDirectory			= pMap["input_directory"].as<std::string>();
	outputStatsFile			= pMap["output_stats_file"].as<std::string>();
	outputRelevantSetFile	= pMap["output_relevant_set_file"].as<std::string>();

	fileWithRelevantSet		= pMap["relevant_set"].as<std::string>();
	filter					= pMap["filter"].as<std::string>();
	tupleElementsFixedOrder	= pMap["tuple_elements_fixed_order"].as<bool>();
}


	}
}


