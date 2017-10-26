

#include <iostream>

#include "../../exception/Exception.h"

#include "Indexer.h"


int main(int argc, char* argv[])
{
	using namespace program::indexer;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Indexer indexer;
		try
		{
			indexer.create(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

