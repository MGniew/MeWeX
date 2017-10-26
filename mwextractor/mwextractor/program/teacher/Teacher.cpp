
#include <iostream>
#include <fstream>
#include <sstream>

#include "../../utils/Textual.h"

#include "../../structure/io/DecodedTupleStorageIO.h"

#include "../../structure/storage/TupleFeatureGenerator.h"
#include "../../structure/builder/ContingencyTableGeneratorBuilder.h"
#include "../../structure/builder/TupleFeatureStorageBuilder.h"
#include "../../structure/io/RelevantTupleSetLoader.h"
#include "../../structure/io/KBestTupleListIO.h"

#include "../../function/filter/Filtrator.h"
#include "../../function/association/Extractor.h"
#include "../../function/FunctionFactory.h"

#include "Teacher.h"


namespace program
{
	namespace teacher
	{


void Teacher::teach(Config const& pConfig)
{
	mConfig = pConfig;

	auto rankerData = loadData();
	teach(rankerData);

	std::cerr << "Done" << std::endl;
}


auto Teacher::loadData() const -> RankerDataPtrS
{
	using namespace function;
	using namespace association;
	using namespace structure::io;
	using namespace structure::builder;
	using namespace structure::storage;

	srand(static_cast<unsigned int>(time(0)));

	std::shared_ptr<RankerData> rankerData(new RankerData());

	auto featureVam = FunctionFactory().createVectorAssociationMeasure(mConfig.featuresFunctions);

	auto mtxstr = DecodedTupleStorageIO().read(mConfig.inputStorage);
	auto allTuples = mtxstr->retrieveTupleIdVector();
	rankerData->setMatrixTupleStorage(mtxstr);

	auto relevant = RelevantTupleSetLoader().loadFromFile(
		mConfig.relevantSet,
		*rankerData->getMatrixTupleStorage(),
		RelevantTupleSetLoader::ElementOrder::FIXED);
	rankerData->setRelevantTupleIdSet(relevant);

	auto tabsrc = ContingencyTableGeneratorBuilder().build(mtxstr, allTuples);
	rankerData->setContingencyTableSource(tabsrc);

	featureVam->initialize(rankerData);
	auto ftrsrc = TupleFeatureStorageBuilder().build(
		TupleFeatureGenerator(featureVam), mtxstr, allTuples, mConfig.threadCount);
	rankerData->setTupleFeatureSource(ftrsrc);

	if (!mConfig.featuresPreprocessor.empty())
	{
		auto preproc = FunctionFactory().createScoreFunction(mConfig.featuresPreprocessor);
		preproc->buildForFeatures(*ftrsrc);
		preproc->scoreFeatures(*ftrsrc);

		std::fstream file(mConfig.outputFolder + "/preprocessor.txt", std::ios_base::out);
		EXCEPTION(file.is_open(), "Teacher::writePreprocessor(): Cannot open a file " << mConfig.outputFolder << "/preprocessor.txt" << ".");

		file << preproc->reprezentation();
		file.close();
	}

	return rankerData;
}


void Teacher::teach(RankerDataPtrS const& pRankerData) const
{
	using namespace function;
	using namespace function::association;
	using namespace structure::io;


	MultilayerPerceptronPtrSVector perceptrons(mConfig.multilayerPerceptrons.size());

	structure::storage::MatrixTupleStorage::TupleIdVector tuples;
	if (!mConfig.filter.empty())
	{
		auto filter = FunctionFactory().createFilterFunction(mConfig.filter);
		filter->initialize(pRankerData->getMatrixTupleStorage());
		tuples = function::filter::Filtrator()(*pRankerData->getMatrixTupleStorage(), filter);
	}
	else
	{
		tuples = pRankerData->getMatrixTupleStorage()->retrieveTupleIdVector();
	}

	utils::parallelFor(0, perceptrons.size(), [&](size_t pThreadId, size_t pJob){
		perceptrons[pJob] = std::static_pointer_cast<MultilayerPerceptron>(
			FunctionFactory().createClassifier(mConfig.multilayerPerceptrons[pJob]));
		perceptrons[pJob]->initialize(pRankerData);
		perceptrons[pJob]->construct(tuples);
	}, mConfig.threadCount);

	auto qfun = FunctionFactory().createQualityFunction(mConfig.qualityFunction);

	for (size_t i = 0; i < perceptrons.size(); ++i)
	{
		auto result = Extractor().extract(perceptrons[i], tuples, -1, mConfig.threadCount);
		auto quality = (*qfun)(result, *pRankerData->getRelevantTupleIdSet(), *pRankerData->getMatrixTupleStorage());

		std::stringstream qdesc;
		qdesc << perceptrons[i]->reprezentation() << '\n' + qfun->reprezentation();
		quality.setDescription(qdesc.str());

		std::stringstream qstr;
		qstr << mConfig.outputFolder << "/quality." << i << ".csv";

		std::string qualityFileResult = qstr.str();
		std::fstream output(
			qualityFileResult,
			std::ios_base::out);
		EXCEPTION(output.is_open(), "Miner::processKBest(): Cannot open output file '" << qualityFileResult << "'.");
		utils::setStreamMaxDoublePrecision(output);
		quality.writeToStream(output);
		output.close();

		std::stringstream mstr;
		mstr << mConfig.outputFolder << "/model." << i << ".csv";
		perceptrons[i]->retrieveModel().writeToFile(mstr.str());

		KBestTupleListIO().write(result, *pRankerData->getMatrixTupleStorage(), mstr.str() + 'd');
	}
}


	}
}
