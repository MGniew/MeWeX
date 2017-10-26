
#pragma once

#include <string>

#include "Neuron.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


/**
 * \brief Klasa reprezentuje model perceptronu wielowarstwowego.
 *
 * Zapisywane są informacje zarówno klasyfikujące jak i te
 * niezbędne do nauki sieci, a tym samym można się douczać po
 * utworzeniu jej z modelu.
 *
 * @see MultilayerPerceptron
 */
class Model
{
public:
	struct NeuronData
	{
		Neuron::ConnectionVector	connectionVector;
		double						gradient;
	};
	typedef std::vector<NeuronData> NeuronDataVector;

	struct LayerData
	{
		NeuronDataVector neuronDataVector;
	};
	typedef std::vector<LayerData> LayerDataVector;

	struct NetData
	{
		LayerDataVector layerDataVector;
		double			learningRate;
		double			momentum;
	};

public:
	Model(std::string const& pFilePath);

	Model()									= default;
	Model(Model&& pModel) 					= default;
	Model(Model const& pModel) 				= default;
	Model& operator=(Model&& pModel) 		= default;
	Model& operator=(Model const& pModel) 	= default;

	~Model() = default;

	void writeToStream(std::ostream& pStream) 		const;
	void writeToFile(std::string const& pFilePath)	const;

	void loadFromStream(std::istream& pStream);
	void loadFromFile(std::string const& pFilePath);

public:
	NetData netData;
};


	}
}
