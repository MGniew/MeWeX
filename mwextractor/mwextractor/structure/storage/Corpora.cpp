
#include "Corpora.h"


namespace structure
{
	namespace storage
	{


Corpora::Corpora(
	std::string pName,
	size_t		pSequenceNumber,
	size_t 		pTokenCount)
:
	mTokenCount(pTokenCount),
	mName(pName),
	mSequenceNumber(pSequenceNumber)
{

}


std::string	Corpora::getNameCopy() const
{
	return mName;
}


std::string const& Corpora::getName() const
{
	return mName;
}


std::string& Corpora::getName()
{
	return mName;
}


size_t Corpora::getSequenceNumber() const
{
	return mSequenceNumber;
}


size_t Corpora::getTokenCount()	const
{
	return mTokenCount;
}


void Corpora::setTokenCount(size_t pTokens) const
{
	mTokenCount = pTokens;
}


void Corpora::modifyTokenCount(size_t pDelta) const
{
	mTokenCount += pDelta;
}


bool Corpora::operator==(Corpora const& pCorpora) const
{
	return (mTokenCount == pCorpora.mTokenCount) && (mName == pCorpora.mName);
}


bool Corpora::operator!=(Corpora const& pCorpora) const
{
	return !((*this) == pCorpora);
}


bool Corpora::operator>(Corpora const& pCorpora) const
{
	return (mTokenCount > pCorpora.mTokenCount);
}


bool Corpora::operator<(Corpora const& pCorpora) const
{
	return (mTokenCount < pCorpora.mTokenCount);
}


bool Corpora::operator>=(Corpora const& pCorpora) const
{
	return !((*this) < pCorpora);
}


bool Corpora::operator<=(Corpora const& pCorpora) const
{
	return !((*this) > pCorpora);
}


	}
}
