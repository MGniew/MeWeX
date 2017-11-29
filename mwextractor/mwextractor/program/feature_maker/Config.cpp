/*
 * Config.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include <iostream>

#include "../../utils/Debug.h"
#include "../../utils/Textual.h"
#include "../../utils/Parallel.h"

#include "../../function/association/Extractor.h"

#include "Config.h"


namespace program
{
	namespace feature_maker
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 							"Prints this message.")

		("input_directory,I", 				bpo::value<std::string>(), "Full path to input directory.")
		("output_file,O",					bpo::value<std::string>(), "Full path to output file.")

		("feature_generator,f", 			bpo::value<std::string>(), "Vector Association Measure which will be used to create features.")
		("score_function,p", 				bpo::value<std::string>()->default_value(""), "Score function for features.")

		("relevant_tuple_set,r", 			bpo::value<std::string>(), "Relevant tuple set used to count quality - must be set if quality function set is not empty.")
		("contingency_table,c",				bpo::value<std::string>()->default_value(""), "File with contingency table (exclusive with 'tuple index').")
		("tuple_index,i",					bpo::value<std::string>()->default_value(""), "File with tuple index (exclusive with 'contingency_table').")
		("extraction_filter,x",				bpo::value<std::string>()->default_value(""), "Filter tuples - measures will be computed only for these tuples which meets filter requirements.")
		("valid_statistic_tuple_filter,s",	bpo::value<std::string>()->default_value(""), "Filter which will be used to determine which tuples can be used as statistic information for rankers based on tuple elements order (WOrder for ex.).")
		("tuple_elements_fixed_order,e",	bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.")

		("table_creation_policy,P",			bpo::value<std::string>()->default_value("s"), "Policy used to create tables from index, s - join same size relations, n - do not join relations.")
		("thread_count,T",					bpo::value<size_t>()->default_value(utils::maxThreads()), "Thread count to use.");

	return options;
}


std::string Config::helpMessage() const
{
	return "Feature maker by Michal Wendelberger.\n";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_directory") == 0)
	{
		setError("Input directory not set.", -1);
	}
	else if (pMap.count("feature_generator") == 0)
	{
		setError("Feature generator not set.", -2);
	}
	else if (pMap.count("output_file") == 0)
	{
		setError("Output file must be set.", -5);
	}
	else if (pMap.count("relevant_tuple_set") == 0)
	{
		setError("Relevant set must be set.", -6);
	}
	else if (pMap.count("tuple_index") == 0 && pMap.count("contingency_table") == 0)
	{
		setError("Neither tuple index nor contingency table set", -7);
	}
	if (pMap["extraction_filter"].as<std::string>().empty())
	{
		std::cerr << "No filter set, will compute measures for every relation." << std::endl;
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputDirectory					= pMap["input_directory"].as<std::string>();
	outputFile						= pMap["output_file"].as<std::string>();

	featureGenerator				= pMap["feature_generator"].as<std::string>();
	scoreFunction					= pMap["score_function"].as<std::string>();

	fileWithRelevantSet				= pMap["relevant_tuple_set"].as<std::string>();
	fileWithContingencyTable		= pMap["contingency_table"].as<std::string>();
	fileWithTupleFrequencyIndex		= pMap["tuple_index"].as<std::string>();
	extractionFilter				= pMap["extraction_filter"].as<std::string>();
	validStatisticTupleFilter		= pMap["valid_statistic_tuple_filter"].as<std::string>();
	tupleElementsFixedOrder			= pMap["tuple_elements_fixed_order"].as<bool>();

	indexTableCreationPolicy		= static_cast<size_t>(pMap["table_creation_policy"].as<std::string>()[0]);
	threadCount						= pMap["thread_count"].as<size_t>();
}


	}
}


