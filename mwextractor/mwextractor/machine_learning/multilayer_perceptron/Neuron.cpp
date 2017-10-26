
#include <cmath>
#include <iostream>

#include "../../utils/Debug.h"
#include "../../utils/Random.h"

#include "../../exception/Exception.h"

#include "Layer.h"
#include "Neuron.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


Neuron::Neuron(
	size_t pInputCount,
	size_t pIndex)
:
	mIndex(pIndex),
	mOutputValue(0.0),
	mGradient(0.0)
{
	mInputConnectionVector.reserve(pInputCount);
	for (size_t i = 0; i < pInputCount; ++i)
	{
		mInputConnectionVector.push_back({ utils::randNormalized(), 0.0 });
	}
}


Neuron::Neuron(
	ConnectionVector&&	pInputConnections,
	size_t 				pIndex,
	double				pGradient)
:
	mIndex(pIndex),
	mOutputValue(0.0),
	mGradient(pGradient),
	mInputConnectionVector(std::forward<ConnectionVector>(pInputConnections))
{

}


Neuron::Neuron(
	ConnectionVector const&	pInputConnections,
	size_t 					pIndex,
	double					pGradient)
:
	mIndex(pIndex),
	mOutputValue(0.0),
	mGradient(pGradient),
	mInputConnectionVector(pInputConnections)
{

}


void Neuron::setOutputValue(double pValue) const
{
	mOutputValue = pValue;
}


size_t Neuron::getIndex() const
{
	return mIndex;
}


double Neuron::getOutputValue() const
{
	return mOutputValue;
}


double Neuron::getGradient() const
{
	return mGradient;
}


auto Neuron::getConnection(size_t pIndex) const -> Connection const&
{
	XASSERT(
		pIndex < mInputConnectionVector.size(),
		"Neuron::getConnection(): Index out of bound.");

	return mInputConnectionVector[pIndex];
}


auto Neuron::getConnection(size_t pIndex) -> Connection&
{
	XASSERT(
		pIndex < mInputConnectionVector.size(),
		"Neuron::getConnection(): Index out of bound.");
	return mInputConnectionVector[pIndex];
}


auto Neuron::getConnectionVector() const -> ConnectionVector const&
{
	return mInputConnectionVector;
}


auto Neuron::getConnectionVector() -> ConnectionVector&
{
	return mInputConnectionVector;
}


void Neuron::feedForward(Layer const& pPreviousLayer) const
{
	double sum = 0.0;

	for (size_t i = 0; i < mInputConnectionVector.size(); ++i)
	{
		//std::cerr << "Neuron::feedForward(): connection = " << i << ", w = " << mInputConnectionVector[i].weight << ", dw = " << mInputConnectionVector[i].weightDelta << std::endl;
		sum += pPreviousLayer.getNeuron(i).getOutputValue() * 
			mInputConnectionVector[i].weight;
	}

	//std::cerr << "Neuron::feedForward(): sum = " << sum << std::endl;

	setOutputValue(activationFunction(sum));
}


double Neuron::activationFunction(double pValue) const
{
	/*
	 * Why 40?
	 * This activation function values are from 0 to 1 (included).
	 * For arguemnt equal 40 this function returns almost 1 -- 0 point
	 * 17 nines or sth and some other values later so more nines than double
	 * max precision.
	 * So there is no need to compute this and this simplification max error is
	 * equal to 10 x 10^(-17) (or sth?).
	 * The error is small but this check makes possible to compute this function value
	 * for almost every possible double value and not only values much less than 1000.
	 */
	if (pValue >= 40.0)
	{
		return 1.0;
	}
	if (pValue <= -40.0)
	{
		return -1.0;
	}

	return (2.0 / (exp(-pValue) + 1.0)) - 1.0;

	/*if (pValue >= 40.0)
	{
		return 1.0;
	}
	if (pValue <= -40.0)
	{
		return 0.0;
	}
	return 1.0 / (exp(-pValue) + 1.0);*/
}


double Neuron::activationFunctionDerivative(double pValue) const
{
	/*
	 * Same reasons as activation function.
	 */
	if (std::abs(pValue) >= 40.0)
	{
		return 0.0;
	}

	double expValue = exp(pValue);
	double element = expValue + 1.0;

	return (expValue * 2.0) / (element * element);

	/*if (std::abs(pValue) >= 40.0)
	{
		return 0.0;
	}

	double expValue = exp(pValue);
	double element = expValue + 1.0;

	return expValue / (element * element);*/
}


void Neuron::computeOutputGradient(double pTargetValue)
{
	double delta = pTargetValue - getOutputValue();
	mGradient = delta * activationFunctionDerivative(getOutputValue());
	//std::cerr << "Neuron::computeOutputGradient(): gradient = " << mGradient << std::endl;
}


void Neuron::computeHiddenGradient(Layer const& pNextLayer)
{
	double dow = pNextLayer.sumDerivatesOfWeights(getIndex());
	mGradient = dow * activationFunctionDerivative(getOutputValue());
	//std::cerr << "Neuron::computeHiddenGradient(): gradient = " << mGradient << std::endl;
}


void Neuron::updateInputWeights(
	Layer const& 	pPreviousLayer,
	double			pLearningRate,
	double			pMomentum)
{
	/* update with bias */
	for (size_t c = 0; c < mInputConnectionVector.size(); ++c)
	{
		double oldDeltaWeight = mInputConnectionVector[c].weightDelta;

		/* individual input magnified by the gradient and train rate	*/
		/* and add momentum - fraction of the previous delta weight 	*/
		double newDeltaWeight =
			pLearningRate *
			pPreviousLayer[c].getOutputValue() *
			getGradient() +
			/* momentum */
			pMomentum *
			oldDeltaWeight;

		mInputConnectionVector[c].weightDelta = newDeltaWeight;
		mInputConnectionVector[c].weight += newDeltaWeight;

		//std::cerr << mInputConnectionVector[c].weight << ' ' << mInputConnectionVector[c].weightDelta << std::endl;
	}
}


	}
}
