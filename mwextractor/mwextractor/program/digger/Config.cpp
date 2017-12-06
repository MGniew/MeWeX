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

		("input_directory,I", 				bpo::value<std::string>(), "Full path to input storage directory.")
		("output_directory,O",				bpo::value<std::string>(), "Full path to output directory.")

		("association_function,a", 			bpo::value<std::vector<std::string>>()->multitoken(), "Association function to use.")
		("vector_association_measure,v", 	bpo::value<std::vector<std::string>>()->multitoken(), "Association vector function to use.")
		("aggregation_function,g", 			bpo::value<std::vector<std::string>>()->multitoken(), "Aggregation function to use (one per vector_association_measure required!).")
		("classifier,c",					bpo::value<std::vector<std::string>>()->multitoken(), "Teached classifier.")
		("features,f",						bpo::value<std::vector<std::string>>()->multitoken(), "Features for classifier.")
		("preprocessor,p",					bpo::value<std::vector<std::string>>()->multitoken(), "Features preprocessor.")

		("quality_function,q", 				bpo::value<std::vector<std::string>>()->multitoken(), "Quality function to use.")

		("relevant_tuple_set,r", 			bpo::value<std::string>()->default_value(""), "Wordnet relevant words set used to count quality - must be set if quality function set is not empty.")
		("contingency_table_storage,S",		bpo::value<std::string>()->default_value(""), "File with contingency table (exclusive with 'tuple index').")
		("contingency_table_generator,i",	bpo::value<std::string>()->default_value(""), "File with tuple index (exclusive with 'contingency_table_storage').")
		("valid_statistic_tuple_filter,s",	bpo::value<std::string>()->default_value(""), "Filter which will be used to determine which tuples can be used as statistic information for rankers based on tuple elements order (WOrder for ex.).")
		("extraction_filter,x",				bpo::value<std::string>()->default_value(""), "It will be used to determine for which tuple measures will be computed.")
		("tuple_elements_fixed_order,e",	bpo::value<bool>()->default_value(true), "If elements in relevant tuple should be considered as in fixed order.")

		("table_creation_policy,P",			bpo::value<std::string>()->default_value("s"), "Policy used to create tables from index, s - join same size relations, n - do not join relations.")
		("kbest_length,k", 					bpo::value<size_t>()->default_value(structure::storage::KBestTupleStructure::maxTopSize()), "KBest list length.")
		("thread_count,t",					bpo::value<size_t>()->default_value(utils::maxThreads()), "Thread count to use.")

		("tagset_name,T",					bpo::value<std::string>()->default_value(""), "Tagset name (req: reader_name, wccl_operators_file, corporas_file).")
		("reader_name,R",					bpo::value<std::string>()->default_value(""), "Corpus reader (req: tagset_name, wccl_operators_file, corporas_file).")
		("wccl_operators_file,W",			bpo::value<std::vector<std::string>>()->multitoken(), "Wccl operators which will be used to extract orths from corporas (req: tagset_name, reader_name, corporas_file).")
		("corporas_file,C",					bpo::value<std::string>()->default_value(""), "Corporas from which orths will be extracted (req: tagset_name, reader_name, wccl_operators_file).")

		("speed_it_up,u",					bpo::value<bool>()->default_value(true), "True if speed up computing, more memory required.");

	return options;
}


std::string Config::helpMessage() const
{
	return "Digger by Michal Wendelberger.\n";
}


void Config::validateParameters(VariableMap& pMap)
{
	if (pMap.count("input_directory") == 0)
	{
		setError("Input directory not set.", -1);
	}
	else if (pMap.count("association_function") == 0 && pMap.count("vector_association_measure") == 0 && pMap.count("classifier") == 0)
	{
		setError("Association function, association vector function nor classifier set.", -2);
	}
	else if (pMap.count("vector_association_measure") != pMap.count("aggregation_function"))
	{
		setError("Association vector function count is different than aggregation function count.", -3);
	}
	else if (!(pMap.count("classifier") == pMap.count("features")) && (pMap.count("features") == pMap.count("preprocessor")))
	{
		setError("Classifier, features and preprocessor count must be equal.", -3);
	}
	else if ( (pMap.count("quality_function") == 0) ^ pMap["relevant_tuple_set"].as<std::string>().empty() )
	{
		setError("If any hen both 'quality_function' and 'relevant_tuple_set' parameters must be set.", -4);
	}
	else if (pMap.count("output_directory") == 0)
	{
		setError("Output directory must be set.", -5);
	}
	else if (pMap.count("contingency_table_generator") == 0 && pMap.count("contingency_table_storage") == 0)
	{
		setError("Neither tuple index nor contingency table set", -6);
	}
	else if
		(!((
			!pMap.count("wccl_operators_file") == 0 &&
			!pMap["corporas_file"].as<std::string>().empty() &&
			!pMap["tagset_name"].as<std::string>().empty() &&
			!pMap["reader_name"].as<std::string>().empty()
		) || (
			pMap.count("wccl_operators_file") == 0 &&
			pMap["corporas_file"].as<std::string>().empty() &&
			pMap["tagset_name"].as<std::string>().empty() &&
			pMap["reader_name"].as<std::string>().empty()
		)))
	{
		setError("If any then all 'wccl_operators_file', 'corporas_file', 'reader_name', 'tagset_name' parameters must be set.", -7);
	}

	if (pMap["extraction_filter"].as<std::string>().empty())
	{
		std::cerr << "No filter set, will compute measures for every tuple." << std::endl;
	}
}


void Config::useParameters(boost::program_options::variables_map const& pMap)
{
	inputDirectory						= pMap["input_directory"].as<std::string>();
	outputDirectory						= pMap["output_directory"].as<std::string>();

	associationFunctions				= pMap.count("association_function") > 0 ?
											pMap["association_function"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	vectorAssociationMeasures			= pMap.count("vector_association_measure") > 0 ?
											pMap["vector_association_measure"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	aggregationFunctions				= pMap.count("aggregation_function") > 0 ?
											pMap["aggregation_function"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	classifiers							= pMap.count("classifier") > 0 ?
											pMap["classifier"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	features							= pMap.count("features") > 0 ?
											pMap["features"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	preprocessors						= pMap.count("preprocessor") > 0 ?
											pMap["preprocessor"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	qualityFunctions					= pMap.count("quality_function") > 0 ?
											pMap["quality_function"].as<std::vector<std::string>>() :
											std::vector<std::string>();

	relevantSetFilepath					= pMap["relevant_tuple_set"].as<std::string>();
	contingencyTableStorageFilepath		= pMap["contingency_table_storage"].as<std::string>();
	contingencyTableGeneratorFilepath	= pMap["contingency_table_generator"].as<std::string>();
	validStatisticTupleFilter			= pMap["valid_statistic_tuple_filter"].as<std::string>();
	extractionFilter					= pMap["extraction_filter"].as<std::string>();
	tupleElementsFixedOrder				= pMap["tuple_elements_fixed_order"].as<bool>();

	indexTableCreationPolicy			= static_cast<size_t>(pMap["table_creation_policy"].as<std::string>()[0]);
	kbestLength							= pMap["kbest_length"].as<size_t>();
	threadCount							= pMap["thread_count"].as<size_t>();

	fileWithWcclOperators				= pMap.count("wccl_operators_file") > 0 ?
											pMap["wccl_operators_file"].as<std::vector<std::string>>() :
											std::vector<std::string>();
	fileWithCorporas					= pMap["corporas_file"].as<std::string>();
	tagsetName							= pMap["tagset_name"].as<std::string>();
	readerName							= pMap["reader_name"].as<std::string>();

	speedItUp							= pMap["speed_it_up"].as<bool>();
}


	}
}


