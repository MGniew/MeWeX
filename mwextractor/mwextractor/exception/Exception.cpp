
#include "Exception.h"


namespace exception
{


Exception::Exception(std::string&& pMessage)
:
	mMessage(std::forward<std::string>(pMessage))
{

}


Exception::Exception(std::string const& pMessage)
:
	mMessage(pMessage)
{

}


std::string const& Exception::getMessage() const
{
	return mMessage;
}


void Exception::setMessage(std::string&& pMessage)
{
	mMessage = std::forward<std::string>(pMessage);
}


void Exception::setMessage(std::string const& pMessage)
{
	mMessage = pMessage;
}


std::ostream& operator<<(
	std::ostream& 		pStream,
	Exception const& 	pException)
{
	return pStream << pException.getMessage() << std::endl;
}


}
