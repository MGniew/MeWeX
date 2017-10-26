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
	namespace web_tool
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 																						"Prints this message.")

		("corpus_filepath_list,I",			bpo::value<std::string>(), 									"File with corporas filepaths.")
		("tagset_name,T", 					bpo::value<std::string>()->default_value("nkjp"), 			"Tagset name.")
		("reader_name,R", 					bpo::value<std::string>()->default_value("iob-chan"), 		"Reader name.")
		("wccl_relations_file,W",			bpo::value<std::vector<std::string>>()->multitoken(),		"WCCL relations filepath.")
		("kbest_filepath,K",				bpo::value<std::string>(), 									"Output kbest filepath.")

		("statistic_filter,s",				bpo::value<std::string>()->default_value(""),				"Statistic data filter.")
		("extraction_filter,e",				bpo::value<std::string>()->default_value(""),				"Extraction filter.")

		("dispersion_function,d",			bpo::value<std::string>()->default_value(""),				"Dispersion function.")
		("ranker,r",						bpo::value<std::string>()->default_value("wsec(e=1.1)"),	"Ranker function.")
		("aggregator,a",					bpo::value<std::string>()->default_value(""),				"Use only if Vector Association Measure will be used.")
		("features,f",						bpo::value<std::string>()->default_value(""),				"Use only if classifier will be used.")
		("features_preprocessor,p",			bpo::value<std::string>()->default_value(""),				"Feature preprocessor, score function.")

		("kbest_length,k",					bpo::value<size_t>()->default_value(100),					"Max rank length.")

		("extract_orths,o",					bpo::value<bool>()->default_value(true),					"Set true if orths should be extracted.");
	return options;
}


std::string Config::helpMessage() const
{
	return 	"Web tool by Michal Wendelberger.\n"
			"Implemented for 'wielowyr'.\n.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("corpus_filepath_list") == 0)
	{
		setError("File with corpora list not set.", -1);
	}
	else if (pMap.count("wccl_relations_file") == 0)
	{
		setError("File with WCCL relations not set.", -2);
	}
	else if (pMap.count("kbest_filepath") == 0)
	{
		setError("Result kbest filepath not set.", -3);
	}
	else if (pMap.count("ranker") == 0)
	{
		setError("Ranker must be set.", -4);
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	corpusFilepathList			= pMap["corpus_filepath_list"].as<std::string>();
	tagsetName					= pMap["tagset_name"].as<std::string>();
	readerName					= pMap["reader_name"].as<std::string>();
	wcclRelationsFile			= pMap["wccl_relations_file"].as<std::vector<std::string>>();
	kbestFilepath				= pMap["kbest_filepath"].as<std::string>();

	statisticDataFilter			= pMap["statistic_filter"].as<std::string>();
	extractionDataFilter		= pMap["extraction_filter"].as<std::string>();
	dispersionFunction			= pMap["dispersion_function"].as<std::string>();

	ranker						= pMap["ranker"].as<std::string>();
	aggregator					= pMap["aggregator"].as<std::string>();
	features					= pMap["features"].as<std::string>();
	featuresPreprocessor		= pMap["features_preprocessor"].as<std::string>();

	rankLength					= pMap["kbest_length"].as<size_t>();

	extractOrths				= pMap["extract_orths"].as<bool>();
}


	}
}


