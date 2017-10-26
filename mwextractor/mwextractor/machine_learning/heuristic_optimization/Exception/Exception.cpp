#include "Exception.h"

using std::string;


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace Exception
		{


Exception::Exception(void) throw()
{
    this->mMsg = "";
}

Exception::Exception(const std::string& rMsg) throw()
{
    this->mMsg = rMsg;
}

Exception::Exception(const Exception& rException) throw()
{
    this->mMsg = rException.mMsg;
}

Exception& Exception::operator=(const Exception& rException) throw()
{
    this->mMsg = rException.mMsg;
    return *this;
}

Exception::~Exception(void) throw()
{
}

const char* Exception::what() const throw()
{
    string s = "Exception: Message=\"";
    s += this->mMsg;
    s += "\"";
    return s.c_str();
}


		}
	}
}
