
#pragma once

/**
 * \file mwextractor/exception/Exception.h
 *
 * \brief Opakowanie funkcjonalności związanej z wyjątkami.
 */


#include <string>
#include <sstream>


#define EXCEPTION(test, messageStream) 				\
{													\
	if (!(test))									\
	{												\
		std::stringstream __str;					\
		__str << messageStream;						\
		throw exception::Exception(__str.str());	\
	}												\
}


namespace exception
{


class Exception
{
public:
	Exception(std::string&& pMessage);
	Exception(std::string const& pMessage);

	Exception(Exception&& 					pException) = default;
	Exception(Exception const& 				pException) = default;
	Exception& operator=(Exception&& 		pException) = default;
	Exception& operator=(Exception const& 	pException) = default;

	virtual ~Exception() = default;


	std::string const& getMessage() const;

	void setMessage(std::string&& 		pMessage);
	void setMessage(std::string const& 	pMessage);


private:
	std::string mMessage;
};


std::ostream& operator<<(
	std::ostream& 		pStream,
	Exception const& 	pException);


}
