
#pragma once

#include <vector>

#include "Neuron.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


/**
 * \brief Klasa reprezentuje warstwę sieci.
 */
class Layer
{
public:
	typedef std::vector<Neuron> NeuronVector;

public:
	Layer(
		size_t pSize,
		size_t pNextLayerSize);

	Layer(NeuronVector&& pNeuronVector);
	Layer(NeuronVector const& pNeuronVector);

	Layer(Layer&& 					pLayer) = default;
	Layer(Layer const& 				pLayer) = default;
	Layer& operator=(Layer&&	 	pLayer) = default;
	Layer& operator=(Layer const& 	pLayer) = default;

	~Layer() = default;

	Neuron const& 	getNeuron(size_t pIndex) const;
	Neuron& 		getNeuron(size_t pIndex);

	Neuron const& 	operator[](size_t pIndex) const;
	Neuron& 		operator[](size_t pIndex);

	size_t size()			const;
	size_t sizeUnbiased()	const;

	void setNeuronsOutputs(std::vector<double> const& pOutputValueVector) const;

	void feedForward(Layer const& pPreviousLayer) const;

	double computeError(std::vector<double> const& pTargetValues) 	const;
	double sumDerivatesOfWeights(size_t pNeuronIndex)				const;

	void computeOutputGradients(std::vector<double> const& pTargetValues);
	void computeHiddenGradients(Layer const& pNextLayer);

	void updateNeuronsInputWeights(
		Layer const& 	pPreviousLayer,
		double			pLearningRate,
		double			pMomentum);

private:
	NeuronVector mNeuronVector;
};


	}
}
