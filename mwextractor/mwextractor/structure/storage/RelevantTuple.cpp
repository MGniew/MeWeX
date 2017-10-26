
#include "../../exception/Exception.h"

#include "RelevantTuple.h"


namespace structure
{
	namespace storage
	{


RelevantTuple::RelevantTuple(size_t pElementCount)
:
	mElements(pElementCount)
{

}


RelevantTuple::RelevantTuple(std::vector<std::string>&& pElements)
:
	mElements(std::forward<std::vector<std::string>>(pElements))
{

}


RelevantTuple::RelevantTuple(std::vector<std::string> const& pElements)
:
	mElements(pElements)
{

}


RelevantTuple::RelevantTuple(
	MatrixTupleStorage const& 	pStorage,
	TupleT const&				pTuple)
:
	mElements(pTuple.size())
{
	for (size_t i = 0; i < pTuple.size(); ++i)
	{
		mElements[i] = pStorage.findWord(pTuple[i]).getContent();
	}
}


std::string const& RelevantTuple::operator[](size_t pIndex) const
{
	return mElements[pIndex];
}


std::string& RelevantTuple::operator[](size_t pIndex)
{
	return mElements[pIndex];
}


std::vector<std::string> const& RelevantTuple::getElements() const
{
	return mElements;
}


std::vector<std::string>& RelevantTuple::getElements()
{
	return mElements;
}


size_t RelevantTuple::size() const
{
	return mElements.size();
}


bool RelevantTuple::equalFlexible(RelevantTuple const& pRelevantTuple) const
{
	bool equal = (size() == pRelevantTuple.size());

	for (size_t i = 0; equal && (i < size()); ++i)
	{
		equal = isWordIn(pRelevantTuple[i]);
	}

	return equal;
}


bool RelevantTuple::equalFixed(RelevantTuple const& pRelevantTuple) const
{
	bool equal = (size() == pRelevantTuple.size());

	for (size_t i = 0; equal && (i < size()); ++i)
	{
		equal = ((*this)[i] == pRelevantTuple[i]);
	}

	return equal;
}


bool RelevantTuple::operator==(RelevantTuple const& pRelevantTuple) const
{
	return equalFlexible(pRelevantTuple);
}


bool RelevantTuple::operator!=(RelevantTuple const& pRelevantTuple) const
{
	return !((*this) == pRelevantTuple);
}


bool RelevantTuple::operator<(RelevantTuple const& pRelevantTuple) const
{
	EXCEPTION(false, "RelevantTuple::operator<(): called.");
	// TODO: it should be flexible, not fixed

	if (size() < pRelevantTuple.size())
	{
		return true;
	}
	else if (size() > pRelevantTuple.size())
	{
		return false;
	}

	for (size_t i = 0; i < size(); ++i)
	{
		if (mElements[i] < pRelevantTuple[i])
		{
			return true;
		}
		else if (mElements[i] > pRelevantTuple[i])
		{
			return false;
		}
	}

	return false;
}


bool RelevantTuple::operator>(RelevantTuple const& pRelevantTuple) const
{
	EXCEPTION(false, "RelevantTuple::operator>(): called.");
	// TODO: it should be flexible, not fixed

	if (size() > pRelevantTuple.size())
	{
		return true;
	}
	else if (size() < pRelevantTuple.size())
	{
		return false;
	}

	for (size_t i = 0; i < size(); ++i)
	{
		if (mElements[i] > pRelevantTuple[i])
		{
			return true;
		}
		else if (mElements[i] < pRelevantTuple[i])
		{
			return false;
		}
	}

	return false;
}


bool RelevantTuple::operator<=(RelevantTuple const& pRelevantTuple) const
{
	return !((*this) > pRelevantTuple);
}


bool RelevantTuple::operator>=(RelevantTuple const& pRelevantTuple) const
{
	return !((*this) < pRelevantTuple);
}


bool RelevantTuple::isWordIn(std::string const& pWord) const
{
	bool isIn = false;
	for (size_t i = 0; (!isIn) && (i < size()); ++i)
	{
		isIn = (mElements[i] == pWord);
	}
	return isIn;
}


std::ostream& operator<<(std::ostream& pStream, RelevantTuple const& pTuple)
{
	for (size_t i = 0; i < pTuple.size(); ++i)
	{
		pStream << "'" << pTuple[i] << "'";
		if (i < pTuple.size() - 1)
		{
			pStream << ' ';
		}
	}
	return pStream;
}


	}
}
