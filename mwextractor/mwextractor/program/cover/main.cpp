

#include <iostream>

#include "Cover.h"


int main(int argc, char* argv[])
{
	using namespace program::cover;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Cover cover;
		try
		{
			cover.check(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

