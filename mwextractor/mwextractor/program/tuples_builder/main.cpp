/*
 * main.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */


#include "TuplesBuilder.h"


int main(int argc, char* argv[])
{
	using namespace program::tuples_builder;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		TuplesBuilder builder;
		try
		{
			builder.start(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}
