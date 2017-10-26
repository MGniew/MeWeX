
#pragma once

#include <cstddef>
#include <vector>


namespace machine_learning
{
	namespace multilayer_perceptron
	{


class Layer;


class Neuron
{
public:
	struct Connection
	{
		double weight;
		double weightDelta;
	};

	typedef std::vector<Connection> ConnectionVector;

public:
	Neuron(
		size_t pInputCount,
		size_t pIndex = static_cast<size_t>(-1));

	Neuron(
		ConnectionVector&&	pInputConnections,
		size_t 				pIndex = static_cast<size_t>(-1),
		double				pGradient = 0.0);

	Neuron(
		ConnectionVector const&	pInputConnections,
		size_t 					pIndex = static_cast<size_t>(-1),
		double					pGradient = 0.0);

	Neuron(Neuron&& 				pNeuron) 	= default;
	Neuron(Neuron const& 			pNeuron) 	= default;
	Neuron& operator=(Neuron&&	 	pNeuron) 	= default;
	Neuron& operator=(Neuron const& pNeuron) 	= default;

	~Neuron() = default;


	void setOutputValue(double pValue) const;

	size_t getIndex() const;

	double getOutputValue() const;

	double getGradient() const;

	Connection const& 	getConnection(size_t pIndex) const;
	Connection& 		getConnection(size_t pIndex);

	ConnectionVector const& getConnectionVector() const;
	ConnectionVector& 		getConnectionVector();


	void feedForward(Layer const& pPreviousLayer) const;

	void computeOutputGradient(double pTargetValue);
	void computeHiddenGradient(Layer const& pNextLayer);

	void updateInputWeights(
		Layer const& 	pPreviousLayer,
		double			pLearningRate,
		double			pMomentum);


private:
	double activationFunction(double pValue)			const;
	double activationFunctionDerivative(double pValue)	const;

private:
	size_t 				mIndex;
	mutable double 		mOutputValue;
	double 				mGradient;
	ConnectionVector	mInputConnectionVector;
};


	}
}
