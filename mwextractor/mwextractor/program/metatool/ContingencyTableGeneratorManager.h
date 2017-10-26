
#pragma once

#include <memory>

#include "../../structure/io/ContingencyTableGeneratorIO.h"
#include "../../structure/storage/ContingencyTableGenerator.h"

#include "DataManager.h"


namespace program
{
	namespace metatool
	{


class ContingencyTableGeneratorManager :
	public DataManager<structure::io::ContingencyTableGeneratorIO::ContingencyTableGeneratorPtrS>
{
public:
	typedef structure::io::ContingencyTableGeneratorIO::ContingencyTableGeneratorPtrS ContingencyTableGeneratorPtrS;

public:
	ContingencyTableGeneratorManager(Id pModuleId, std::string&& 		pName);
	ContingencyTableGeneratorManager(Id pModuleId, std::string const& 	pName);


	virtual Id loadFromFile(std::string const& pPath) override;

	virtual void writeToFile(std::string const& pPath, Id pId) const override;

	virtual Id copy(Id pId) override;
};


	}
}
