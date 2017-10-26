/*
 * Config.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include <vector>
#include <string>

#include <boost/program_options.hpp>

#include "../AbstractConfig.h"


namespace program
{
	namespace metatool
	{


class Config : public AbstractConfig
{
public:

protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
