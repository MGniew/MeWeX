
#include <fstream>
#include <cstddef>

#include "../../exception/Exception.h"

#include "Model.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


Model::Model(std::string const& pFilePath)
{
	loadFromFile(pFilePath);
}


void Model::writeToStream(std::ostream& pStream) const
{
	pStream << netData.layerDataVector.size() << ' ' << netData.learningRate << ' ' << netData.momentum << std::endl;
	for (size_t l = 0; l < netData.layerDataVector.size(); ++l)
	{
		NeuronDataVector const& neurons = netData.layerDataVector[l].neuronDataVector;
		pStream << neurons.size() << std::endl;
		for (size_t n = 0; n < neurons.size(); ++n)
		{
			pStream << neurons[n].connectionVector.size() << ' ' << neurons[n].gradient;
			for (size_t c = 0; c < neurons[n].connectionVector.size(); ++c)
			{
				pStream << ' ' << neurons[n].connectionVector[c].weight << ' ' << neurons[n].connectionVector[c].weightDelta;
			}
			pStream << std::endl;
		}
	}
}


void Model::writeToFile(std::string const& pFilePath) const
{
	std::fstream output(pFilePath, std::ios_base::out);
	EXCEPTION(output.is_open(), "Model::writeToFile(): cannot open output file '" << pFilePath << "'.");
	writeToStream(output);
	output.close();
}


void Model::loadFromStream(std::istream& pStream)
{
	size_t layerCount;

	pStream >> layerCount >> netData.learningRate >> netData.momentum;

	netData.layerDataVector.resize(layerCount);
	for (size_t l = 0; l < layerCount; ++l)
	{
		size_t neuronCount;
		pStream >> neuronCount;
		NeuronDataVector& neurons = netData.layerDataVector[l].neuronDataVector;
		neurons.resize(neuronCount);
		for (size_t n = 0; n < neuronCount; ++n)
		{
			size_t connectionCount;
			pStream >> connectionCount >> neurons[n].gradient;
			neurons[n].connectionVector.resize(connectionCount);
			for (size_t c = 0; c < connectionCount; ++c)
			{
				pStream >> neurons[n].connectionVector[c].weight >> neurons[n].connectionVector[c].weightDelta;
			}
		}
	}
}


void Model::loadFromFile(std::string const& pFilePath)
{
	std::fstream input(pFilePath, std::ios_base::in);
	EXCEPTION(input.is_open(), "Model::loadFromFile(): cannot open input file '" << pFilePath << "'.");
	loadFromStream(input);
	input.close();
}


	}
}
