
#pragma once

#include "Config.h"


namespace program
{
	namespace metatool
	{


class MetaTool
{
private:
	//static constexpr std::string getPrompt(){ return std::string("==>>>"); }

public:
	void run(
		Config const& 	pConfig,
		int 			pArgc,
		char* 			pArgs[]);


private:
	Config mConfig;
};


	}
}
