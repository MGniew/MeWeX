/*
 * main.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */


#include "Normalizer.h"


int main(int argc, char* argv[])
{
	using namespace program::normalizer;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Normalizer normalizer;
		try
		{
			normalizer.normalizeInPlace(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}
