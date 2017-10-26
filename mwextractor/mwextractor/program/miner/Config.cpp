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

#include "../../structure/storage/KBestTupleList.h"

#include "Config.h"


namespace program
{
	namespace miner
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 							"Prints this message.")

		("input_storage_directory,I", 		bpo::value<std::string>(), "Full path to input storage directory.")
		("output_result_directory,O",		bpo::value<std::string>(), "Full path to output directory where results should be stored.")

		("table_creation_policy,P",			bpo::value<std::string>()->default_value("s"), "Policy used to create tables from index, s - join same size relations, n - do not join relations.")

		("statistic_data_filter,s",			bpo::value<std::string>()->default_value(""), "It will be used to determine on which statistic data will be computed (default = all).")
		("extraction_filter,x",				bpo::value<std::string>()->default_value(""), "It will be used to determine for which tuple measures will be computed (default = all).")
		("association_function,a", 			bpo::value<std::vector<std::string>>()->multitoken(), "Association function to use.")
		("vector_association_measure,v", 	bpo::value<std::vector<std::string>>()->multitoken(), "Vector association measure to use.")
		("aggregation_function,g", 			bpo::value<std::vector<std::string>>()->multitoken(), "Aggregation function to use (one per vector_association_measure required!).")
		("classifier_features,f", 			bpo::value<std::string>()->default_value(""), "Vector association measure used to generate features.")
		("features_processors,p", 			bpo::value<std::string>()->default_value(""), "Score function used to preprocess features before constructing classifier.")
		("classifier,c", 					bpo::value<std::vector<std::string>>()->multitoken(), "Classifier to use.")
		("quality_function,q", 				bpo::value<std::vector<std::string>>()->multitoken(), "Quality function to use.")

		("relevant_tuple_set,r", 			bpo::value<std::string>()->default_value(""), "Relevant tuple set used to count quality - must be set if quality function set is not empty.")
		("tuple_elements_fixed_order,e",	bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.")

		("repeat_count,R",					bpo::value<size_t>()->default_value(1), "Repeat count in cross validation.")
		("fold_count,F",					bpo::value<size_t>()->default_value(5), "Fold count used in cross validation.")
		("kbest_length_for_qualities,K", 	bpo::value<size_t>()->default_value(structure::storage::KBestTupleStructure::maxTopSize()), "KBest list length.")
		("thread_count,T",					bpo::value<size_t>()->default_value(utils::maxThreads() >> 1), "Thread count to use.")

		("write_kbest_files,w",				bpo::value<bool>()->default_value(false), "If kbest files should be stored.")
		("write_kbest_length,W",			bpo::value<size_t>()->default_value(structure::storage::KBestTupleStructure::maxTopSize()), "");

	return options;
}


std::string Config::helpMessage() const
{
	return "Miner by Michal Wendelberger.\n";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_storage_directory") == 0)
	{
		setError("Input storage directory not set.", -1);
	}
	else if (pMap.count("output_result_directory") == 0)
	{
		setError("Output result directory must be set.", -2);
	}
	else if (pMap.count("association_function") == 0 && pMap.count("vector_association_measure") == 0 && pMap.count("classifier") == 0)
	{
		setError("No association function, vector association measure nor classifier set.", -3);
	}
	else if (pMap.count("vector_association_measure") != pMap.count("aggregation_function"))
	{
		setError("Association vector function count is different than aggregation function count.", -4);
	}
	else if (pMap.count("classifier") == 0 ^ pMap["classifier_features"].as<std::string>().empty())
	{
		setError("If classifier or classifier features set then both must be set.", -5);
	}
	else if ((pMap.count("quality_function") == 0) || pMap["relevant_tuple_set"].as<std::string>().empty())
	{
		setError("Quality function and relevant tuple set must be set.", -6);
	}

	if (pMap["statistic_data_filter"].as<std::string>().empty())
	{
		std::cerr << "No statistic filter set, will collect data for every tuple." << std::endl;
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputStorageDirectory				= pMap["input_storage_directory"].as<std::string>();
	outputResultsDirectory				= pMap["output_result_directory"].as<std::string>();

	contingencyTableGeneratorPolicy		= static_cast<size_t>(pMap["table_creation_policy"].as<std::string>()[0]);

	statisticDataFilter					= pMap["statistic_data_filter"].as<std::string>();
	extractionFilter					= pMap["extraction_filter"].as<std::string>();
	associationFunctions				= pMap.count("association_function") > 0 ?
											pMap["association_function"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	vectorAssociationMeasures			= pMap.count("vector_association_measure") > 0 ?
											pMap["vector_association_measure"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	aggregationFunctions				= pMap.count("aggregation_function") > 0 ?
											pMap["aggregation_function"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	classifierFeatureGenerator			= pMap["classifier_features"].as<std::string>();
	classifierFeatureProcessor			= pMap["features_processors"].as<std::string>();
	classifiers							= pMap.count("classifier") > 0 ?
											pMap["classifier"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	qualityFunctions					= pMap.count("quality_function") > 0 ?
											pMap["quality_function"].as<std::vector<std::string>>() :
											std::vector<std::string>();

	relevantTupleSetFilepath			= pMap["relevant_tuple_set"].as<std::string>();
	tupleElementsFixedOrder				= pMap["tuple_elements_fixed_order"].as<bool>();

	repeatCount							= pMap["repeat_count"].as<size_t>();
	foldCount							= pMap["fold_count"].as<size_t>();
	kbestLengthForQualities				= pMap["kbest_length_for_qualities"].as<size_t>();
	threadCount							= pMap["thread_count"].as<size_t>();

	writeKBestFiles						= pMap["write_kbest_files"].as<bool>();
	writeKbestLength					= pMap["write_kbest_length"].as<size_t>();
}


	}
}


