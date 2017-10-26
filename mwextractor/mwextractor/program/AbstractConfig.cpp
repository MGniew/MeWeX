
#include <iostream>

#include "AbstractConfig.h"


namespace program
{


AbstractConfig::AbstractConfig()
:
	mError(""),
	mErrorCode(CONFIG_OK)
{

}


int AbstractConfig::initFromCommandLine(int pArgc, char* pArgv[])
{
	Options options = buildOptions();

	try {
		VariableMap variableMap;
		boost::program_options::store(parse_command_line(
			pArgc, pArgv, options), variableMap);

		notify(variableMap);

		if (variableMap.count("help") > 0)
		{
			std::cerr << helpMessage() << '\n' << options << '\n';
			return HELP_MESSAGE;
		}

		validateParameters(variableMap);

		if (mErrorCode != CONFIG_OK)
		{
			std::cerr << "Error occured (code = " << mErrorCode << "):\n" << mError << '\n';
			return mErrorCode;
		}

		useParameters(variableMap);
	}
	catch (std::exception const& e)
	{
		std::cerr << "Big bad exception occured:" << '\n' << e.what() << std::endl;
		return BIG_BAD_EXCEPTION;
	}

	return CONFIG_OK;
}


void AbstractConfig::dump(std::ostream& pStream) const
{
	pStream << "Not implemented for this config." << std::endl;
}


void AbstractConfig::setError(
	std::string const& 	pError,
	int 				pErrorCode)
{
	mError 		= pError;
	mErrorCode 	= pErrorCode;
}


}
