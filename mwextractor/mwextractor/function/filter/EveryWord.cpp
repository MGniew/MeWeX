
#include "../../structure/io/StreamingFileReader.h"

#include "EveryWord.h"


namespace function
{
	namespace filter
	{


EveryWord::EveryWord(
	OperatorType 					pOperatorType,
	StringParameterVector const&	pWords)
:
	FeatureFilter(pOperatorType, pWords)
{

}


void EveryWord::construct()
{
	for (size_t i = 0; i < getParameters().size(); ++i)
	{
		auto vector = getMatrixTupleStorage()->findWordIdsAllPartOfSpeech(
			WordT(nullptr, getParameters()[i], 0.0, 0));
		mWordIdSet.insert(vector.begin(), vector.end());
	}

	if (!getParameterFile().empty())
	{
		structure::io::StreamingFileReader reader(getParameterFile());
		std::string line;
		while (reader.readline(line))
		{
			auto vector = getMatrixTupleStorage()->findWordIdsAllPartOfSpeech(
				WordT(nullptr, line, 0.0, 0));
			mWordIdSet.insert(vector.begin(), vector.end());
		}
	}
}


bool EveryWord::in(TupleId pTupleId) const
{
	bool isOk = true;
	TupleStorage::TupleT const& tuple = getMatrixTupleStorage()->findTuple(pTupleId);
	for (size_t i = 0; i < tuple.size() && isOk; ++i)
	{
		isOk = mWordIdSet.find(tuple[i]) != mWordIdSet.end();
	}

	return isOk;
}


std::string EveryWord::name() const
{
	return "every_word";
}


	}
}
