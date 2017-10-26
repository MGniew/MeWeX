
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>

#include "../../utils/File.h"
#include "../../utils/Textual.h"

#include "../../structure/io/DecodedTupleStorageIO.h"

#include "../../function/FunctionFactory.h"
#include "../../function/filter/Filtrator.h"

#include "Reductor.h"


namespace program
{
	namespace reductor
	{


void Reductor::reduce(Config const& pConfig)
{
	mConfig = pConfig;

	srand(time(0));
	reduce();

	std::cerr << "Done." << std::endl;
}


void Reductor::reduce()
{
	mTupleStorage = structure::io::DecodedTupleStorageIO().read(mConfig.inputDirectory);

	if (!mConfig.filter.empty())
	{
		typedef std::shared_ptr<function::filter::Filter>	__FilterPtrS;
		typedef function::filter::Filtrator					__Filtrator;

		std::cerr << "Building filter: " << mConfig.filter << std::endl;
		__FilterPtrS filter = function::FunctionFactory().createFilterFunction("not(" + mConfig.filter + ')');
		filter->initialize(mTupleStorage);

		std::cerr << "Filtering using: " << filter->reprezentation() << std::endl;
		TupleIdVector ids = __Filtrator()(*mTupleStorage, filter);

		for (size_t i = 0; i < ids.size(); ++i)
		{
			mTupleStorage->removeTuple(ids[i]);
		}
	}

	if (!mConfig.fileWithRelevantTupleSet.empty())
	{
		std::cerr << "Subsampling..." << std::endl;
		{
			TupleIdSet set;
			for (auto iter = mTupleStorage->beginTuples(); iter != mTupleStorage->endTuples(); ++iter)
			{
				set.insert(mTupleStorage->findTupleId(iter));
			}

			std::cerr << "Loading relevant set..." << std::endl;
			mPositiveNegative = RelevantLoader().loadPairFromFile(
				mConfig.fileWithRelevantTupleSet,
				*mTupleStorage,
				mConfig.tupleElementFixedOrder ?
					RelevantLoader::ElementOrder::FIXED :
					RelevantLoader::ElementOrder::FLEXIBLE,
				set);
		}

		{
			size_t targetNegativeCount = static_cast<size_t>(std::ceil(static_cast<double>(
				mPositiveNegative.positive->size()) / mConfig.positiveToNegativeRatio)) -
					mPositiveNegative.positive->size();
			size_t negativeToRemove = mPositiveNegative.negative->size() - targetNegativeCount;

			TupleIdVector negative(mPositiveNegative.negative->begin(), mPositiveNegative.negative->end());
			std::random_shuffle(negative.begin(), negative.end());

			for (size_t i = 0; i < negativeToRemove; ++i)
			{
				mTupleStorage->removeTuple(negative[i]);
			}
		}
	}

	std::cerr << "Writing storage..." << std::endl;
	structure::io::DecodedTupleStorageIO().write(mConfig.outputDirectory, *mTupleStorage);
}


	}
}
