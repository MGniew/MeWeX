
#include <cmath>

#include "../../utils/Debug.h"

#include "Layer.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


Layer::Layer(
	size_t pSize,
	size_t pPreviousLayerSize)
{
	/* increase because of bias neuron */
	++pSize;
	++pPreviousLayerSize;

	mNeuronVector.reserve(pSize);

	/* add neurons */
	for (size_t i = 0; i < pSize; ++i)
	{
		mNeuronVector.push_back(Neuron(pPreviousLayerSize, i));
	}

	/* set bias neuron to 1.0 */
	mNeuronVector.back().setOutputValue(1.0);
}


Layer::Layer(NeuronVector&& pNeuronVector)
:
	mNeuronVector(std::forward<NeuronVector>(pNeuronVector))
{
	/* set bias neuron to 1.0 */
	mNeuronVector.back().setOutputValue(1.0);
}


Layer::Layer(NeuronVector const& pNeuronVector)
:
	mNeuronVector(pNeuronVector)
{

}


Neuron const& Layer::getNeuron(size_t pIndex) const
{
	XASSERT(pIndex < mNeuronVector.size(), "Layer::getNeuron(): Index out of bound.");
	return mNeuronVector[pIndex];
}


Neuron& Layer::getNeuron(size_t pIndex)
{
	XASSERT(pIndex < mNeuronVector.size(), "Layer::getNeuron(): Index out of bound.");
	return mNeuronVector[pIndex];
}


Neuron const& Layer::operator[](size_t pIndex) const
{
	return getNeuron(pIndex);
}


Neuron& Layer::operator[](size_t pIndex)
{
	return getNeuron(pIndex);
}


size_t Layer::size() const
{
	return mNeuronVector.size();
}


size_t Layer::sizeUnbiased() const
{
	return size() - 1;
}


void Layer::setNeuronsOutputs(std::vector<double> const& pOutputValueVector) const
{
	/* -1 because of bias */
	XASSERT(
		pOutputValueVector.size() == sizeUnbiased(),
		"Layer::setNeuronsOutputs(): Size: " << sizeUnbiased() << ", vec size: " << pOutputValueVector.size());

	for (size_t n = 0; n < pOutputValueVector.size(); ++n)
	{
		getNeuron(n).setOutputValue(pOutputValueVector[n]);
	}
}


void Layer::feedForward(Layer const& pPreviousLayer) const
{
	for (size_t n = 0; n < sizeUnbiased(); ++n)
	{
		getNeuron(n).feedForward(pPreviousLayer);
	}
}


double Layer::computeError(std::vector<double> const& pTargetValues) const
{
	XASSERT(
		pTargetValues.size() == sizeUnbiased(),
		"Layer::computeError(): Size: " << sizeUnbiased() << ", vec size: " << pTargetValues.size());

	double error = 0.0;
	for (size_t n = 0; n < sizeUnbiased(); ++n)
	{
		double delta = pTargetValues[n] - getNeuron(n).getOutputValue();
		error += delta * delta;
	}

	return sqrt(error / static_cast<double>(sizeUnbiased()));
}


double Layer::sumDerivatesOfWeights(size_t pNeuronIndex) const
{
	double sum = 0.0;

	for (size_t n = 0; n < sizeUnbiased(); ++n)
	{
		sum += getNeuron(n).getConnection(pNeuronIndex).weight * getNeuron(n).getGradient();
	}

	return sum;
}


void Layer::computeOutputGradients(std::vector<double> const& pTargetValues)
{
	XASSERT(
		pTargetValues.size() == sizeUnbiased(),
		"Layer::computeOutputGradients(): Size: " << sizeUnbiased() << ", vec size: " << pTargetValues.size());

	for (size_t n = 0; n < sizeUnbiased(); ++n)
	{
		getNeuron(n).computeOutputGradient(pTargetValues[n]);
	}
}


void Layer::computeHiddenGradients(Layer const& pNextLayer)
{
	for (size_t n = 0; n < size(); ++n)
	{
		getNeuron(n).computeHiddenGradient(pNextLayer);
	}
}


void Layer::updateNeuronsInputWeights(
	Layer const& 	pPreviousLayer,
	double			pLearningRate,
	double			pMomentum)
{
	/* TODO what with bias? */
	for (size_t n = 0; n < sizeUnbiased(); ++n)
	{
		getNeuron(n).updateInputWeights(
			pPreviousLayer,
			pLearningRate,
			pMomentum);
	}
}


	}
}
