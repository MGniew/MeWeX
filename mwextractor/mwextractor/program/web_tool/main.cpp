

#include <iostream>

#include "../../exception/Exception.h"

#include "WebTool.h"


int main(int argc, char* argv[])
{
	using namespace program::web_tool;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		WebTool webTool;
		try
		{
			webTool.start(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
			// There seem to be error codes in messages, but no way to get at them.
			// Just return generic error status.
			return 1;
		}

		return 0;
	}

	// Config was not OK
	return 2;
}
