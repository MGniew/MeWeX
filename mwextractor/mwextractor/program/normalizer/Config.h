/*
 * Config.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include <string>

#include <boost/program_options.hpp>

#include "../AbstractConfig.h"


namespace program
{
	namespace normalizer
	{


class Config : public AbstractConfig
{
public:
	std::string inputDirectory;
	std::string outputDirectory;

	std::string dispersionFunction;
	bool		inverseDispersion;

	std::string contingencyTableStorage;
	std::string contingencyTableGenerator;


protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
