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
	namespace reductor
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 								"Prints this message.")

		("input_directory,i", 					bpo::value<std::string>(), "Full path to input directory.")
		("output_directory,o",					bpo::value<std::string>(), "Output storage directory.")

		("relevant_set,r", 						bpo::value<std::string>()->default_value(""), "Relevant tuple set used to determine relevant tuples.")
		("tuple_elements_fixed_order,e",		bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.")
		("positive_to_negative_ratio,p",		bpo::value<double>()->default_value(0.0), "All positive tuples will remain and negative will be subsampled until ratio will be satisfied.")

		("filter,f",							bpo::value<std::string>()->default_value(""), "Only tuples which fill requirements will remain.");

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
	else if (pMap.count("output_directory") == 0)
	{
		setError("Output directory must be set.", -2);
	}
	else if (
			(pMap["relevant_set"].as<std::string>().empty() && pMap["filter"].as<std::string>().empty()) ||
			(!pMap["relevant_set"].as<std::string>().empty() && pMap["positive_to_negative_ratio"].as<double>() == 0.0))
	{
		setError("No relevant nor filter set or relevant set set but ratio is 0.0. So... There is nothing to do at all.", -3);
	}

	if (pMap.count("filter") == 0)
	{
		std::cerr << "Filter not set, will compute for whole storage." << std::endl;
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputDirectory				= pMap["input_directory"].as<std::string>();
	outputDirectory				= pMap["output_directory"].as<std::string>();

	fileWithRelevantTupleSet	= pMap["relevant_set"].as<std::string>();
	tupleElementFixedOrder		= pMap["tuple_elements_fixed_order"].as<bool>();
	positiveToNegativeRatio		= pMap["positive_to_negative_ratio"].as<double>();

	filter						= pMap["filter"].as<std::string>();
}


	}
}


