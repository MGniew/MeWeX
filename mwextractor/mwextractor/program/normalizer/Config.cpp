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
	namespace normalizer
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 							"Prints this message")

		("input_directory,I",	 			bpo::value<std::string>(), "Input directory")
		("output_directory,O",	 			bpo::value<std::string>(), "Output directory")

		("contingency_table_storage,s",	 	bpo::value<std::string>()->default_value(""), "Contingency table or tuple frequency index must be set if tuples are going to be normalized.")
		("contingency_table_generator,g",	bpo::value<std::string>()->default_value(""), "Contingency table or tuple frequency index must be set if tuples are going to be normalized.")

		("dispersion_function,d",			bpo::value<std::string>(), "Dispersion function")
		("inverse_dispersion,i", 			bpo::value<bool>()->default_value(false), "True if dispersion function results should be inversed");

	return options;
}


std::string Config::helpMessage() const
{
	return 	"Normalizer by Michal Wendelberger.\n"
			"Normalize global frequency using local frequencies distribution and dispersion function.\n.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_directory") == 0)
	{
		setError("Input directory not set.", -1);
	}
	else if (pMap.count("dispersion_function") == 0)
	{
		setError("Distribution function not set.", -2);
	}
	else if (pMap.count("output_directory") == 0)
	{
		setError("Output directory must be set", -3);
	}
	/*else if (
		pMap["contingency_table_generator"].as<std::string>().empty() &&
		pMap["contingency_table_storage"].as<std::string>().empty())
	{
		setError("Contingency table source not set.", -4);
	}*/
}



void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputDirectory				= pMap["input_directory"].as<std::string>();
	outputDirectory				= pMap["output_directory"].as<std::string>();
	dispersionFunction			= pMap["dispersion_function"].as<std::string>();
	inverseDispersion			= pMap["inverse_dispersion"].as<bool>();

	contingencyTableStorage		= pMap["contingency_table_storage"].as<std::string>();
	contingencyTableGenerator	= pMap["contingency_table_generator"].as<std::string>();
}


	}
}


