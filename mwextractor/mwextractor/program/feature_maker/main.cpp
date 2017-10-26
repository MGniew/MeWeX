

#include <iostream>

#include "FeatureMaker.h"


int main(int argc, char* argv[])
{
	using namespace program::feature_maker;

	Config config;
	int res = config.initFromCommandLine(argc, argv);

	if (res == program::AbstractConfig::CONFIG_OK)
	{
		FeatureMaker featureMaker;
		try
		{
			featureMaker.make(config);
		}
		catch (exception::Exception const& e)
		{
			std::cerr << e.getMessage() << std::endl;
		}
	}

	return 0;
}

