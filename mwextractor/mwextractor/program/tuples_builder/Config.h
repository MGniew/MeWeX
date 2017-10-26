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

#include <libwccl/wcclfile.h>

#include "../AbstractConfig.h"


namespace program
{
	namespace tuples_builder
	{


class Config : public AbstractConfig
{
public:
	typedef boost::shared_ptr<Wccl::Operator<Wccl::Bool>> WcclBoolOperatorPtr;

public:
	void dump(std::ostream& pStream) const override;

public:
	std::vector<std::string> 	corporas;
	std::string					corpusReaderName;
	std::string					tagsetName;
	std::string					outputDirectory;
	std::vector<std::string>	operatorsFiles;

protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
