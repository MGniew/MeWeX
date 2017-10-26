

#include <iostream>

#include "Teacher.h"


/**
 * Zadaniem programu jest nauczenie sieci neuronowej na podstawie pewnego zbioru danych.
 */
int main(int argc, char* argv[])
{
	using namespace program::teacher;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		Teacher teacher;
		try
		{
			teacher.teach(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

