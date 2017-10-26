
#include <iostream>

#include "../../exception/Exception.h"

#include "MetaTool.h"


int main(int argc, char* argv[])
{
	using namespace program::metatool;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		MetaTool metaTool;
		try
		{
			metaTool.run(config, argc, argv);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

