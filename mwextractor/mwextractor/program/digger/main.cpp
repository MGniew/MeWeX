

#include <iostream>

#include "../../exception/Exception.h"

#include "Digger.h"


int main(int argc, char* argv[])
{
	using namespace program::digger;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Digger digger;
		try
		{
			digger.dig(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

