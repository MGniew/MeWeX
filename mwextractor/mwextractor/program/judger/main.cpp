/*
 * main.cpp
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#include <iostream>

#include "../../exception/Exception.h"

#include "Judger.h"


int main(int argc, char* argv[])
{
	using namespace program::judger;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Judger judger;
		try
		{
			judger.judge(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}
