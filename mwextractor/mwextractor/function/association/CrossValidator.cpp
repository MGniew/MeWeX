
#include "CrossValidator.h" 


namespace function
{
	namespace association
	{


CrossValidator::CrossValidator(
	FunctionSet const&		pFunctionSet,
	ParameterSet const&		pParameterSet,
	DataSet const&			pDataSet)
:
	mFunctionSet(pFunctionSet),
	mParameterSet(pParameterSet),
	mDataSet(pDataSet)
{
	initialize();
}


void CrossValidator::prepareRound()
{
	mFolds = FoldsBuilder().build(
		mDataSet.tupleStorage->retrieveTupleIdVector(),
		mParameterSet.foldCount,
		mParameterSet.foldCreationPolicy);

	mCurrentFold = 0;
}


auto CrossValidator::performForNextFold() -> ResultPtrS
{
	typedef function::filter::Filtrator __Filtrator;

	if (mCurrentFold >= mParameterSet.foldCount)
	{
		return nullptr;
	}

	/* allocate space for result */
	ResultPtrS result(new Result());
	result->foldResultForFunctions.resize(
		mFunctionSet.vectorAssociationMeasureVector.size() +
		mFunctionSet.associationFunctionVector.size() +
		mFunctionSet.classifierVector.size());

	/* perform cross validation */
	DEBUG_MESSAGE("Fold " << (mCurrentFold + 1));

	/********** Filtering **********/
	DEBUG_MESSAGE("Filtering and gathering statistics.");

	Fold trainFold;
	{
		Fold trainFoldFull = FoldsBuilder().mergeFolds(mFolds, mCurrentFold);
		if (mFunctionSet.statisticFilter != nullptr)
		{
			/* should be moved */
			trainFold = __Filtrator()(trainFoldFull, mFunctionSet.statisticFilter);
		}
		else
		{
			trainFold.swap(trainFoldFull);
		}
	}

	Fold testFold;
	{
		Fold& testFoldFull = mFolds[mCurrentFold];

		if (mFunctionSet.extractionFilter != nullptr)
		{
			testFold = __Filtrator()(testFoldFull, mFunctionSet.extractionFilter);
		}
		else
		{
			/* copy */
			testFold = testFoldFull;
		}

		result->foldRelevantTupleIdSetExtraction = mDataSet.relevantTupleIdSet->subset(testFold);

		if (testFoldFull.size() != testFold.size())
		{
			result->foldRelevantTupleIdSetExtraction->setSourceSize(
				mDataSet.relevantTupleIdSet->subset(testFoldFull)->sourceSize());
		}
	}

	DEBUG_MESSAGE("Filtering done, got statistics.");
	/********** !Filtering **********/

	/* build contingency table generator */
	{
		DEBUG_MESSAGE("Collecting contingency data...");

		ContingencyTableGeneratorPtrS generator = ContingencyTableGeneratorBuilder().
			build(mDataSet.tupleStorage, trainFold);
		generator->setTableCreationPolicy(mParameterSet.tableCreationPolicy);
		mRankerData->setContingencyTableSource(generator);

		DEBUG_MESSAGE("Contingency data collected.");
	}

	size_t functionIndex = 0;

	/* vector association measure */
	for (size_t v = 0; v < mFunctionSet.vectorAssociationMeasureVector.size(); ++v)
	{
		DEBUG_MESSAGE("Computing for " << mFunctionSet.vectorAssociationMeasureVector[v]->reprezentation());

		KBestTupleListVector vectorAssociationMeasureResult = extract(
			mFunctionSet.vectorAssociationMeasureVector[v],
			testFold,
			mParameterSet.rankSize,
			mParameterSet.threadCount);
		result->foldResultForFunctions[functionIndex] = (*mFunctionSet.vectorMeasureAggregatorVector[v])(
			vectorAssociationMeasureResult, mParameterSet.threadCount);
		++functionIndex;
	}

	/* association function */
	{
		DEBUG_MESSAGE("Computing for packed function: " << mPackedFunctions->reprezentation());

		KBestTupleListVector vectorAssociationMeasureResult = extract(
			mPackedFunctions,
			testFold,
			mParameterSet.rankSize,
			mParameterSet.threadCount);

		for (size_t a = 0; a < vectorAssociationMeasureResult.size(); ++a)
		{
			result->foldResultForFunctions[functionIndex] = std::forward<KBestTupleList>(vectorAssociationMeasureResult[a]);
			++functionIndex;
		}
	}

	/* train data for classifiers */
	if (!mFunctionSet.classifierVector.empty())
	{
		XASSERT(mFeatureGenerator.get() != nullptr, "CrossValidator::perform(): Feature generator not set.");

		/* compute features */
		{
			DEBUG_MESSAGE("Computing features using: " << mFeatureGenerator->getVectorAssociationMeasure()->reprezentation());
			TupleFeatureStoragePtrS trainFeatureStorage = TupleFeatureStorageBuilder().
				build(*mFeatureGenerator, mDataSet.tupleStorage, trainFold, mParameterSet.threadCount);

			if (mFunctionSet.featureProcessor != nullptr)
			{
				DEBUG_MESSAGE("Processing train features...");
				mFunctionSet.featureProcessor->buildForFeatures(*trainFeatureStorage);
				mFunctionSet.featureProcessor->scoreFeatures(*trainFeatureStorage);
			}

			mRankerData->setTupleFeatureSource(trainFeatureStorage);
		}

		/* construct classifiers */
		ClassifierPtrSVector classifiers;
		{
			for (size_t i = 0; i < mFunctionSet.classifierVector.size(); ++i)
			{
				classifiers.push_back(mFunctionSet.classifierVector[i]->clone());
			}

			utils::parallelFor(0, classifiers.size(), [&](
				size_t pThreadId,
				size_t pClassifierNumber)
			{
				DEBUG_MESSAGE("Constructing " << mFunctionSet.classifierVector[pClassifierNumber]->reprezentation());
				classifiers[pClassifierNumber]->construct(trainFold);
			}, mParameterSet.threadCount);
		}

		/* test data for classifiers */
		{
			DEBUG_MESSAGE("Building test features...");
			TupleFeatureStoragePtrS testFeatureStorage = TupleFeatureStorageBuilder().
				build(*mFeatureGenerator, mDataSet.tupleStorage, testFold, mParameterSet.threadCount);

			if (mFunctionSet.featureProcessor != nullptr)
			{
				DEBUG_MESSAGE("Processing test features...");
				mFunctionSet.featureProcessor->scoreFeatures(*testFeatureStorage);
			}

			mRankerData->setTupleFeatureSource(testFeatureStorage);
		}

		/* classifiers computation */;
		DEBUG_MESSAGE("Extracting using classifiers...");
		VectorAssociationMeasurePtrS packedClassifiers(new VectorAssociationMeasure(
			AssociationMeasurePtrSVector(classifiers.begin(), classifiers.end())));
		packedClassifiers->initialize(mRankerData);
		KBestTupleListVector classifiersResult = extract(
			packedClassifiers,
			testFold,
			mParameterSet.rankSize,
			mParameterSet.threadCount);
		for (size_t a = 0; a < classifiersResult.size(); ++a)
		{
			result->foldResultForFunctions[functionIndex] = std::forward<KBestTupleList>(classifiersResult[a]);
			++functionIndex;
		}
	}

	++mCurrentFold;

	DEBUG_MESSAGE(mParameterSet.foldCount << "-fold cross validation finished.");

	return result;
}


void CrossValidator::initialize()
{
	/* set data */
	mRankerData.reset(new RankerData(mDataSet.tupleStorage));
	mRankerData->setRelevantTupleIdSet(mDataSet.relevantTupleIdSet);

	/* pack functions */
	mPackedFunctions = VectorAssociationMeasurePtrS(new VectorAssociationMeasure(
		AssociationMeasurePtrSVector(
			mFunctionSet.associationFunctionVector.begin(),
			mFunctionSet.associationFunctionVector.end())));
	mPackedFunctions->initialize(mRankerData);

	for (size_t a = 0; a < mFunctionSet.vectorAssociationMeasureVector.size(); ++a)
	{
		mFunctionSet.vectorAssociationMeasureVector[a]->initialize(mRankerData);
	}
	for (size_t c = 0; c < mFunctionSet.classifierVector.size(); ++c)
	{
		mFunctionSet.classifierVector[c]->initialize(mRankerData);
	}

	/* construct filters */
	if (mFunctionSet.statisticFilter != nullptr)
	{
		mFunctionSet.statisticFilter->initialize(mDataSet.tupleStorage);
		mRankerData->setStatisticTupleFilter(mFunctionSet.statisticFilter);
	}

	if (mFunctionSet.extractionFilter != nullptr)
	{
		mFunctionSet.extractionFilter->initialize(mDataSet.tupleStorage);
	}

	/* create feature generator */
	TupleFeatureGeneratorPtrS featureGenerator;
	if (mFunctionSet.featureGenerator != nullptr)
	{
		mFunctionSet.featureGenerator->initialize(mRankerData);
		mFeatureGenerator.reset(new TupleFeatureGenerator(mFunctionSet.featureGenerator));
	}
}


	}
}
