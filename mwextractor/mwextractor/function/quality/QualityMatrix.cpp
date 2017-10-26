
#include "QualityMatrix.h"


namespace function
{
	namespace quality
	{


QualityMatrix::QualityMatrix(
	size_t 	pSize,
	size_t	pElementSize,
	double 	pValue)
:
	Array2D(pSize, pElementSize, pValue)
{

}


QualityMatrix::QualityMatrix(
	std::string pDescription,
	size_t 		pSize,
	size_t		pElementSize,
	double 		pValue)
:
	Array2D(pSize, pElementSize, pValue),
	mDescription(pDescription)
{

}


std::string const& QualityMatrix::getDescription() const
{
	return mDescription;
}


std::string& QualityMatrix::getDescription()
{
	return mDescription;
}


void QualityMatrix::setDescription(std::string const& pDescription)
{
	mDescription = pDescription;
}


void QualityMatrix::writeToStream(
	std::ostream& 	pStream,
	char 			pDelimeter) const
{
	pStream << mDescription << '\n' << getRowCount() << pDelimeter << getRowSize() << '\n';
	Array2D::writeToStream(pStream, pDelimeter);
}


	}
}
