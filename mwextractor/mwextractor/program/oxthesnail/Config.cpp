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
	namespace digger
	{


auto Config::buildOptions() const -> Options
{
	namespace bpo = boost::program_options;

	Options options("Parameters:");
	options.add_options()
		("help,h", 							"Prints this message.")

		("input_directory,s", 				bpo::value<std::string>(), "Full path to input storage directory.")
		("output_directory,o",				bpo::value<std::string>(), "Full path to output directory.")

		("association_function,f", 			bpo::value<std::vector<std::string>>()->multitoken(), "Association function to use.")
		("association_vector_function,v", 	bpo::value<std::vector<std::string>>()->multitoken(), "Association vector function to use.")
		("aggregation_function,a", 			bpo::value<std::vector<std::string>>()->multitoken(), "Aggregation function to use (one per association_vector_function required!).")
		("quality_function,q", 				bpo::value<std::vector<std::string>>()->multitoken(), "Quality function to use.")

		("relevant_wordnet_set,r", 			bpo::value<std::string>()->default_value(""), "Wordnet relevant words set used to count quality - must be set if quality function set is not empty.")
		("contingency_table,c",				bpo::value<std::string>()->default_value(""), "File with contingency table (exclusive with 'tuple index').")
		("tuple_index,i",					bpo::value<std::string>()->default_value(""), "File with tuple index (exclusive with 'contingency_table').")
		("filter,w",						bpo::value<std::string>()->default_value(""), "It will be used to determine for which tuple measures will be computed.")
		("tuple_elements_fixed_order,e",	bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.")

		("table_creation_policy,p",			bpo::value<std::string>()->default_value("s"), "Policy used to create tables from index, s - join same size relations, n - do not join relations.")
		("kbest_length,k", 					bpo::value<size_t>()->default_value(structure::storage::KBestTupleStructure::maxTopSize()), "KBest list length.")
		("thread_count,t",					bpo::value<size_t>()->default_value(utils::maxThreads()), "Thread count to use.")
		("speed_it_up,u",					bpo::value<bool>()->default_value(true), "If this parameter is true then computation may be faster however more memory may be used.")

		("tagset_name,x",					bpo::value<std::string>()->default_value(""), "Tagset name (req: reader_name, wccl_operators_file, corporas_file).")
		("reader_name,y",					bpo::value<std::string>()->default_value(""), "Corpus reader (req: tagset_name, wccl_operators_file, corporas_file).")
		("wccl_operators_file,z",			bpo::value<std::string>()->default_value(""), "Wccl operators which will be used to extract orths from corporas (req: tagset_name, reader_name, corporas_file).")
		("corporas_file,m",					bpo::value<std::string>()->default_value(""), "Corporas from which orths will be extracted (req: tagset_name, reader_name, wccl_operators_file).");

	return options;
}


std::string Config::helpMessage() const
{
	return "Digger by Michal Wendelberger.\n";
}


// TODO: Change error nr. -3
void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_directory") == 0)
	{
		setError("Input directory not set.", -1);
	}
	else if (pMap.count("association_function") == 0 && pMap.count("association_vector_function") == 0)
	{
		setError("Association function nor association vector function not set.", -2);
	}
	else if (pMap.count("association_vector_function") != pMap.count("aggregation_function"))
	{
		setError("Association vector function count is different than aggregation function count.", -3);
	}
	else if ( (pMap.count("quality_function") == 0) ^ pMap["relevant_wordnet_set"].as<std::string>().empty() )
	{
		setError("If any hen both 'quality_function' and 'relevant_wordnet_set' parameters must be set.", -4);
	}
	else if (pMap.count("output_directory") == 0)
	{
		setError("Output directory must be set.", -5);
	}
	else if (pMap.count("tuple_index") == 0 && pMap.count("contingency_table") == 0)
	{
		setError("Neither tuple index nor contingency table set", -6);
	}
	else if
		(!((
			!pMap["wccl_operators_file"].as<std::string>().empty() &&
			!pMap["corporas_file"].as<std::string>().empty() &&
			!pMap["tagset_name"].as<std::string>().empty() &&
			!pMap["reader_name"].as<std::string>().empty()
		) || (
			pMap["wccl_operators_file"].as<std::string>().empty() &&
			pMap["corporas_file"].as<std::string>().empty() &&
			pMap["tagset_name"].as<std::string>().empty() &&
			pMap["reader_name"].as<std::string>().empty()
		)))
	{
		setError("If any then all 'wccl_operators_file', 'corporas_file', 'reader_name', 'tagset_name' parameters must be set.", -7);
	}

	if (pMap["filter"].as<std::string>().empty())
	{
		std::cerr << "No filter set, will compute measures for every tuple." << std::endl;
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputDirectory				= pMap["input_directory"].as<std::string>();
	outputDirectory				= pMap["output_directory"].as<std::string>();

	associationFunctions		= pMap["association_function"].as<std::vector<std::string>>();
	associationVectorFunctions	= pMap.count("association_vector_function") > 0 ?
									pMap["association_vector_function"].as<std::vector<std::string>>() :
									std::vector<std::string>();
	aggregationFunctions		= pMap.count("aggregation_function") > 0 ?
									pMap["aggregation_function"].as<std::vector<std::string>>() :
									std::vector<std::string>();
	qualityFunctions			= pMap.count("quality_function") > 0 ?
									pMap["quality_function"].as<std::vector<std::string>>() :
									std::vector<std::string>();

	fileWithRelevantSet			= pMap["relevant_wordnet_set"].as<std::string>();
	fileWithContingencyTable	= pMap["contingency_table"].as<std::string>();
	fileWithTupleFrequencyIndex	= pMap["tuple_index"].as<std::string>();
	filter	 					= pMap["filter"].as<std::string>();
	tupleElementsFixedOrder		= pMap["tuple_elements_fixed_order"].as<bool>();

	indexTableCreationPolicy	= static_cast<size_t>(pMap["table_creation_policy"].as<std::string>()[0]);
	kbestLength					= pMap["kbest_length"].as<size_t>();
	threadCount					= pMap["thread_count"].as<size_t>();
	speedItUp					= pMap["speed_it_up"].as<bool>();

	fileWithWcclOperators		= pMap["wccl_operators_file"].as<std::string>();
	fileWithCorporas			= pMap["corporas_file"].as<std::string>();
	tagsetName					= pMap["tagset_name"].as<std::string>();
	readerName					= pMap["reader_name"].as<std::string>();
}


	}
}


