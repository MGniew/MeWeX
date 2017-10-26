

#include <iostream>

#include "Miner.h"


int main(int argc, char* argv[])
{
	using namespace program::miner;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Miner miner;
		try
		{
			miner.build(config);
			miner.mine();
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

