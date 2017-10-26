#pragma once

#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace Exception
		{


/**
* General exception class for Optimizer. Exception is described by a string message.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class Exception : public std::exception
{
public:
    /**
    * Creates empty exception with no message.
    */
    Exception(void) throw();

    /**
    * Creates an exception with the specified message.
    *
    * @param[in] rMsg The message.
    */
    Exception(const std::string& rMsg) throw();

    /**
    * A copy constructor.
    *
    * @param rException Reference to copied Exception.
    */
    Exception(const Exception& rException) throw();

    /**
    * An object destructor.
    */
    virtual ~Exception(void) throw();

    /**
    * An assignment operator.
    *
    * @param rException Reference to copied Exception.
    */
    Exception& operator=(const Exception& rException) throw();
    /**
    * Returns a describe of the exception.
    *
    * @return The describe of the exception.
    */
    virtual const char* what() const throw();

protected:
    /**
    * The string message describes Exception.
    */
    std::string mMsg;
}; // Exception


		}
	} // Exception
} // Optimizer
