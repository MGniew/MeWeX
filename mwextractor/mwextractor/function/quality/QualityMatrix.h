
#pragma once

#include "../../structure/container/Array2D.h"


namespace function
{
	namespace quality
	{


class QualityMatrix : public structure::container::Array2D<double>
{
public:
	QualityMatrix(
		size_t 	pSize 			= 0,
		size_t	pElementSize	= 1,
		double 	pValue 			= 0);

	QualityMatrix(
		std::string pDescription,
		size_t 		pSize 			= 0,
		size_t		pElementSize	= 1,
		double 		pValue 			= 0);

	QualityMatrix(QualityMatrix&& 					pVector) = default;
	QualityMatrix(QualityMatrix const& 				pVector) = default;
	QualityMatrix& operator=(QualityMatrix&& 		pVector) = default;
	QualityMatrix& operator=(QualityMatrix const& 	pVector) = default;

	virtual ~QualityMatrix() = default;


	std::string const&		getDescription() const;
	std::string&			getDescription();

	void 					setDescription(std::string const& pDescription);

	virtual void			writeToStream(
								std::ostream& 	pStream,
								char 			pDelimeter = '\t') const override;

private:
	std::string mDescription;
};


	}
}
