
#include <fstream>

#include "../../utils/Textual.h"
#include "../../utils/Debug.h"

#include "../../function/FunctionFactory.h"

#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/StreamingFileReader.h"
#include "../../structure/io/DecodedTupleStorageIO.h"
#include "../../structure/io/KBestTupleListIO.h"
#include "../../structure/io/RelevantTupleSetLoader.h"

#include "../../function/filter/Filtrator.h"

#include "Judger.h"


namespace program
{
	namespace judger
	{


void Judger::judge(Config const& pConfig) const
{
	typedef	structure::storage::MatrixTupleStorage	TupleStorage;
	typedef std::shared_ptr<TupleStorage>			TupleStoragePtrS;

	typedef structure::io::RelevantTupleSetLoader	RelevantLoader;
	typedef RelevantLoader::RelevantTupleIdSetPtrS	RelevantTupleIdSetPtrS;

	typedef structure::io::KBestTupleListIO 		__KIO;

	std::vector<function::FunctionFactory::QualityFunctionPtrS> functions;
	{
		std::cerr << "building functions..." << std::endl;
		function::FunctionFactory ff;
		functions.reserve(pConfig.qualityFunctions.size());
		for (size_t i = 0; i < pConfig.qualityFunctions.size(); ++i)
		{
			functions.push_back(ff.createQualityFunction(
				pConfig.qualityFunctions[i]));
		}
	}

	std::cerr << "loading storage: " << pConfig.storageDirectory << "..." << std::endl;
	TupleStoragePtrS storage = structure::io::DecodedTupleStorageIO().
		read(pConfig.storageDirectory);

	std::vector<__KIO::KBestTupleList> kbests;
	kbests.reserve(pConfig.kbestToScoreVector.size());
	for (size_t i = 0; i < pConfig.kbestToScoreVector.size(); ++i)
	{
		std::cerr << "kbest list loading: " << pConfig.kbestToScoreVector[i] << "..." << std::endl;
		kbests.push_back(__KIO().read(*storage, pConfig.kbestToScoreVector[i], pConfig.kbestToScoreMaxLength));
	}

	RelevantTupleIdSetPtrS relevant;
	{
		RelevantLoader::ElementOrder elementOrder =
			pConfig.tupleElementsFixedOrder ?
				RelevantLoader::ElementOrder::FIXED :
				RelevantLoader::ElementOrder::FLEXIBLE;

		if (!pConfig.filter.empty())
		{
			typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
			typedef function::filter::Filtrator					__Filtrator;

			std::cerr << "Building filter: " << pConfig.filter << std::endl;
			__FilterPtrS filter = function::FunctionFactory().createFilterFunction(pConfig.filter);
			filter->initialize(storage);

			std::cerr << "Filtering using: " << filter->reprezentation() << std::endl;
			TupleStorage::TupleIdVector tids = __Filtrator()(*storage, filter);

			std::cerr << "Loading relevant set using tuple id set..." << std::endl;
			relevant = RelevantLoader().loadFromFile(
				pConfig.relevantSet,
				*storage,
				elementOrder,
				TupleStorage::TupleIdSet(tids.begin(), tids.end()));
		}
		else
		{
			std::cerr << "Loading relevant set..." << std::endl;
			relevant = RelevantLoader().loadFromFile(
				pConfig.relevantSet,
				*storage,
				elementOrder);
		}
	}

	for (size_t k = 0; k < kbests.size(); ++k)
	{
		for (size_t i = 0; i < pConfig.qualityFunctions.size(); ++i)
		{
			std::cerr << "Checking result quality using: " << functions[i]->reprezentation() << std::endl;
			function::quality::QualityMatrix qualityResult = (*functions[i])(kbests[k], *relevant, *storage);
			qualityResult.setDescription(
				kbests[k].getDescription() + '\n' +
				functions[i]->reprezentation());

			std::string qualityOutputFile = pConfig.outputDirectory + "/quality." +
				std::to_string(k) + '.' +
				std::to_string(i) + ".quality.csv";
			std::fstream output(
				qualityOutputFile,
				std::ios_base::out);
			EXCEPTION(output.is_open(), "Judger::judge(): Cannot open output file '" << qualityOutputFile << "'.");
			utils::setStreamMaxDoublePrecision(output);
			qualityResult.writeToStream(output);
			output.close();
		}
	}
}


	}
}
