/*
 * Config.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include <iostream>

#include "Config.h"


namespace program
{
	namespace judger
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 							"Prints this message")
		("storage_directory,s",	 			bpo::value<std::string>(), "Storage directory")
		("filter,f",						bpo::value<std::string>()->default_value(""), "Filter")
		("kbest_list,l",					bpo::value<std::vector<std::string>>()->multitoken(), "KBest list to score, can be more than one.")
		("kbest_to_score_max_length,m",		bpo::value<size_t>()->default_value(-1), "Restrict kbest list size.")
		("relevant_set,r",					bpo::value<std::string>(), "Relevant set")
		("tuple_elements_fixed_order,e",	bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.")
		("quality_function,q",				bpo::value<std::vector<std::string>>()->multitoken(), "Quality function to use")
		("output_directory,o",	 			bpo::value<std::string>(), "Output directory");
	return options;
}


std::string Config::helpMessage() const
{
	return 	"Judger by Michal Wendelberger.\n"
			"Check kbest list quality.\n.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("storage_directory") == 0)
	{
		setError("Storage directory not set.", -1);
	}
	else if (pMap.count("kbest_list") == 0)
	{
		setError("KBest list not set.", -2);
	}
	else if (pMap.count("quality_function") == 0)
	{
		setError("Quality function not set.", -3);
	}
	else if (pMap.count("output_directory") == 0)
	{
		setError("Output directory must be set.", -4);
	}
	else if (pMap.count("relevant_set") == 0)
	{
		setError("Relevant set not set.", -5);
	}

	if (pMap["filter"].as<std::string>().empty())
	{
		std::cerr << "No filter set, will compute measures for every relation." << std::endl;
	}
}



void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	storageDirectory		= pMap["storage_directory"].as<std::string>();
	filter					= pMap["filter"].as<std::string>();
	kbestToScoreVector		= pMap["kbest_list"].as<std::vector<std::string>>();
	kbestToScoreMaxLength	= pMap["kbest_to_score_max_length"].as<size_t>();
	relevantSet				= pMap["relevant_set"].as<std::string>();
	tupleElementsFixedOrder	= pMap["tuple_elements_fixed_order"].as<bool>();
	qualityFunctions		= pMap["quality_function"].as<std::vector<std::string>>();
	outputDirectory			= pMap["output_directory"].as<std::string>();
}


	}
}


