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
	namespace heuristic
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 							"Prints this message.")

		("storage,I", 						bpo::value<std::string>(), 						"Storage directory.")
		("output_filepath,O",				bpo::value<std::string>(), 						"Output filepath.")

		("table_generator,g",				bpo::value<std::string>()->default_value(""), 	"Tuple frequency index (generator).")
		("table_storage,s",					bpo::value<std::string>()->default_value(""), 	"Contingency table.")
		("filter,f",						bpo::value<std::string>()->default_value(""), 	"Filter.")

		("linear_combination_command,c",	bpo::value<std::string>(), 						"Linear combination command.")

		("relevant_tuple_set,r",			bpo::value<std::string>(), 						"Relevant tuple set.")
		("tuple_elements_fixed_order,e",	bpo::value<bool>()->default_value(true),		"Tuple element order set to be fixed.");
	return options;
}


std::string Config::helpMessage() const
{
	return 	"Heuristic by Michal Wendelberger.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("storage") == 0)
	{
		setError("Storage not set.", -1);
	}
	else if (pMap.count("output_filepath") == 0)
	{
		setError("Output file not set.", -2);
	}
	else if (pMap["table_generator"].as<std::string>().empty() && pMap["table_storage"].as<std::string>().empty())
	{
		setError("No index nor table set.", -3);
	}
	else if (pMap.count("linear_combination_command") == 0)
	{
		setError("Linear combination command not set.", -4);
	}
	else if (pMap.count("relevant_tuple_set") == 0)
	{
		setError("Relevant tuple set not set.", -4);
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	storageDirectory			= pMap["storage"].as<std::string>();
	outputFilename				= pMap["output_filepath"].as<std::string>();

	contingencyTableGenerator	= pMap["table_generator"].as<std::string>();
	contingencyTableStorage		= pMap["table_storage"].as<std::string>();
	filter						= pMap["filter"].as<std::string>();

	linearCombinationCommand	= pMap["linear_combination_command"].as<std::string>();

	relevantTupleSetFilepath	= pMap["relevant_tuple_set"].as<std::string>();
	tupleElementsFixedOrder		= pMap["tuple_elements_fixed_order"].as<bool>();
}


	}
}


