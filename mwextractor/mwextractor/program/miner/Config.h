
#pragma once

#include <vector>
#include <string>

#include <boost/program_options.hpp>

#include "../AbstractConfig.h"


namespace program
{
	namespace miner
	{


class Config : public AbstractConfig
{
public:
	std::string					inputStorageDirectory;
	std::string 				outputResultsDirectory;

	size_t						contingencyTableGeneratorPolicy;

	std::string					statisticDataFilter;
	std::string					extractionFilter;
	std::vector<std::string> 	associationFunctions;
	std::vector<std::string> 	vectorAssociationMeasures;
	std::vector<std::string> 	aggregationFunctions;
	std::string 				classifierFeatureGenerator;
	std::string					classifierFeatureProcessor;
	std::vector<std::string> 	classifiers;
	std::vector<std::string> 	qualityFunctions;

	std::string					relevantTupleSetFilepath;
	bool						tupleElementsFixedOrder;

	size_t						foldCount;
	size_t						repeatCount;
	size_t						kbestLengthForQualities;
	size_t						threadCount;

	bool						writeKBestFiles;
	size_t						writeKbestLength;

protected:
	virtual Options 	buildOptions() 							const override;
	virtual std::string helpMessage() 							const override;
	virtual void		validateParameters(VariableMap& pMap)	override;

private:
	void useParameters(VariableMap const& pMap) override;
};


	}
}
