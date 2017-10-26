/*
 * AbstractConfig.h
 *
 *  Created on: 20-05-2014
 *      Author: michalw
 */

#pragma once

#include <vector>
#include <string>

#include <boost/program_options.hpp>


namespace program
{


class AbstractConfig
{
public:
	typedef boost::program_options::options_description Options;
	typedef boost::program_options::variables_map		VariableMap;

public:
	static const int CONFIG_OK			= 0;
	static const int HELP_MESSAGE 		= 1;
	static const int BIG_BAD_EXCEPTION 	= 1001;

public:
	AbstractConfig();
	AbstractConfig(AbstractConfig const& pConfig)				= default;
	AbstractConfig(AbstractConfig&& pConfig) 					= default;
	AbstractConfig& operator=(AbstractConfig const& pConfig) 	= default;
	AbstractConfig& operator=(AbstractConfig&& pConfig) 		= default;

	virtual ~AbstractConfig() = default;


	virtual int initFromCommandLine(
		int 	argc,
		char* 	argv[]);

	virtual void dump(std::ostream& pStream) const;


protected:
	void setError(std::string const& pError, int pErrorCode);

	// return Options
	virtual Options 	buildOptions() 							const = 0;

	// return help message without parameters
	virtual std::string helpMessage() 							const = 0;

	// check if all parameters are ok, if yes return CONFIG_OK, if not try to repair this or return non zero value
	virtual void		validateParameters(VariableMap& pMap) 	= 0;


private:
	virtual void useParameters(VariableMap const& pMap) = 0;

private:
	std::string mError;
	int			mErrorCode;
};


}
