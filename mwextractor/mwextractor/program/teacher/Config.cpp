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
	namespace teacher
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 					"Prints this message.")

		("input_storage,I", 		bpo::value<std::string>(), 								"Input storage.")
		("output_folder,O",			bpo::value<std::string>(), 								"Output folder for results.")

		("features_functions,f",	bpo::value<std::string>(), 								"Vector Association Measure")
		("features_preprocessor,p",	bpo::value<std::string>()->default_value(""),		 	"Score Function")
		("multilayer_perceptron,m",	bpo::value<std::vector<std::string>>()->multitoken(),	"Multilayer Perceptrons to teach.")

		("filter,F", 				bpo::value<std::string>()->default_value(""),			"Filter to determine which tuples should be used during teaching")

		("quality_function,q",		bpo::value<std::string>(), 								"Quality function to score MLP.")
		("relevant_set,r",			bpo::value<std::string>(), 								"Relevant set for quality function.")

		("thread_count,t",			bpo::value<size_t>()->default_value(1), 				"Max available worker threads");

	return options;
}


std::string Config::helpMessage() const
{
	return "Multilayer Perceptron trainer by Michal Wendelberger.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_storage") == 0)
	{
		setError("Input directory not set.", -1);
	}
	else if (pMap.count("output_folder") == 0)
	{
		setError("Output folder not set.", -2);
	}
	else if (pMap.count("multilayer_perceptron") == 0)
	{
		setError("Multilayer perceptron not set.", -3);
	}
	else if (pMap.count("features_functions") == 0)
	{
		setError("Features not set.", -4);
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputStorage			= pMap["input_storage"].as<std::string>();
	outputFolder			= pMap["output_folder"].as<std::string>();
	featuresFunctions		= pMap["features_functions"].as<std::string>();
	featuresPreprocessor	= pMap["features_preprocessor"].as<std::string>();
	filter					= pMap["filter"].as<std::string>();
	multilayerPerceptrons	= pMap["multilayer_perceptron"].as<std::vector<std::string>>();
	qualityFunction			= pMap["quality_function"].as<std::string>();
	relevantSet				= pMap["relevant_set"].as<std::string>();
	threadCount				= pMap["thread_count"].as<size_t>();
}


	}
}


