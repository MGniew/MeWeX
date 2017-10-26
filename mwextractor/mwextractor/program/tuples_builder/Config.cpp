/*
 * Config.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */


#include <fstream>

#include "../../utils/Debug.h"
#include "../../utils/File.h"

#include "Config.h"


namespace program
{
	namespace tuples_builder
	{


void Config::dump(std::ostream& pStream) const
{
	pStream
		<< "Tagset:                " << tagsetName << '\n'
		<< "Reader:                " << corpusReaderName << '\n'
		<< "Output dir:            " << outputDirectory << '\n'
		<< "Corporas:";

	for (size_t i = 0; i < corporas.size(); ++i)
	{
		pStream << "\n\t" << (i + 1) << ". " << corporas[i];
	}

	pStream << std::endl;
}


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 					"Print this message")
		("corpora_list_file,c", 	bpo::value<std::string>(), "File with paths to corporas")
		("wccl_operators_file,w", 	bpo::value<std::vector<std::string>>()->multitoken(), "File with wccl operators")
		("tagset,t", 				bpo::value<std::string>(), "Tagset for corpus and wccl parser")
		("corpus_reader,r", 		bpo::value<std::string>(), "Corpus reader")
		("output_directory,o", 		bpo::value<std::string>(), "Full path to output directory");
	return options;
}


std::string Config::helpMessage() const
{
	return 	"Tuples builder by Michal Wendelberger.\n"
			"Build tuples using wccl bool operators.";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("tagset") == 0)
	{
		setError("Tagset not set.\n", -1);
	}
	else if (pMap.count("corpus_reader") == 0)
	{
		setError("Reader not set.\n", -2);
	}
	else if (pMap.count("corpora_list_file") == 0)
	{
		setError("File with paths to corporas must be set.\n", -3);
	}
	else if (pMap.count("wccl_operators_file") == 0)
	{
		setError("At least one file with wccl operators must be set.\n", -4);
	}
	else if (pMap.count("output_directory") == 0)
	{
		setError("Output directory not set.\n", -5);
	}
}



void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	tagsetName 				= pMap["tagset"].as<std::string>();
	corpusReaderName 		= pMap["corpus_reader"].as<std::string>();
	outputDirectory			= pMap["output_directory"].as<std::string>();
	operatorsFiles			= pMap["wccl_operators_file"].as<std::vector<std::string>>();

	utils::loadLinesFromFile(
		pMap["corpora_list_file"].as<std::string>(),
		corporas);
}


	}
}


