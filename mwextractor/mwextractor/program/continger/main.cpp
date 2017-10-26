

#include <iostream>

#include "../../exception/Exception.h"

#include "Continger.h"


int main(int argc, char* argv[])
{
	using namespace program::continger;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Continger continger;
		try
		{
			continger.create(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

