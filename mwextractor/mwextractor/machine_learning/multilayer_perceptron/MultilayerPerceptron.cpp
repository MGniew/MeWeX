
#include <sstream>
#include <ctime>

#include "../../utils/Textual.h"
#include "../../utils/Debug.h"

#include "MultilayerPerceptron.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


MultilayerPerceptron::MultilayerPerceptron()
:
	mErorr(0.0),
	mLearningRate(0.0),
	mMomentum(0.0),
	mEpoch(1)
{

}


MultilayerPerceptron::MultilayerPerceptron(
	std::vector<size_t> const& 	pTopology,
	double						pLearningRate,
	double						pMomentum)
:
	mErorr(0.0),
	mLearningRate(pLearningRate),
	mMomentum(pMomentum),
	mEpoch(1)
{
	buildFromTopology(pTopology);
}


MultilayerPerceptron::MultilayerPerceptron(Model const& pModel)
:
	mErorr(0.0),
	mLearningRate(pModel.netData.learningRate),
	mMomentum(pModel.netData.momentum),
	mEpoch(1)
{
	buildFromModel(pModel);
}


MultilayerPerceptron::MultilayerPerceptron(
	LayerVector const& 	pLayerVector,
	double				pLearningRate,
	double				pMomentum)
:
	mLayerVector(pLayerVector),
	mErorr(0.0),
	mLearningRate(pLearningRate),
	mMomentum(pMomentum),
	mEpoch(1)
{

}


auto MultilayerPerceptron::clone() const -> ClassifierPtrS
{
	return ClassifierPtrS(new MultilayerPerceptron(*this));
}


auto MultilayerPerceptron::retrieveFunctionParameters() const -> StringParameterMap
{
	return
	{
		{"learning_rate", "0.15"},
		{"momentum", "0.5"},
		{"epoch", "10"},
		{"model", "none"}
	};
}


void MultilayerPerceptron::build(
	StringParameterMap const& pParameters,
	StringParameterMap const& pUnnamedParameters)
{
	std::string epoch_str = pParameters.find("epoch")->second;
	if (!epoch_str.empty())
	{
		mEpoch = std::stoi(epoch_str);
	}
	std::string modelFilePath = pParameters.find("model")->second;
	if (!modelFilePath.empty())
	{
		buildFromModel(Model(modelFilePath));
	}
	else
	{
		XASSERT(
			pParameters.find("learning_rate") != pParameters.end(),
			"MultilayerPerceptron::build(): Learning rate parameter not set.");
		XASSERT(
			pParameters.find("momentum") != pParameters.end(),
			"MultilayerPerceptron::build(): Momentum parameter not set.");

		std::vector<size_t> topology;
		for (size_t l = 0; l < pUnnamedParameters.size(); ++l)
		{
			topology.push_back(utils::toSizeT(pUnnamedParameters.find(std::to_string(l))->second));
		}

		buildFromTopology(
			topology,
			utils::toDouble(pParameters.find("learning_rate")->second),
			utils::toDouble(pParameters.find("momentum")->second));
	}
}


Layer const& MultilayerPerceptron::getInputLayer() const
{
	XASSERT(mLayerVector.size() > 0, "MultilayerPerceptron::getInputLayer(): Index out of bound.");
	return mLayerVector.front();
}


Layer& MultilayerPerceptron::getInputLayer()
{
	XASSERT(mLayerVector.size() > 0, "MultilayerPerceptron::getInputLayer(): Index out of bound.");
	return mLayerVector.front();
}


Layer const& MultilayerPerceptron::getLayer(size_t pIndex) const
{
	XASSERT(pIndex < mLayerVector.size(), "MultilayerPerceptron::getLayer(): Index out of bound.");
	return mLayerVector[pIndex];
}


Layer& MultilayerPerceptron::getLayer(size_t pIndex)
{
	XASSERT(pIndex < mLayerVector.size(), "MultilayerPerceptron::getLayer(): Index out of bound.");
	return mLayerVector[pIndex];
}


Layer const& MultilayerPerceptron::getOutputLayer() const
{
	XASSERT(mLayerVector.size() > 0, "MultilayerPerceptron::getOutputLayer(): Index out of bound.");
	return mLayerVector.back();
}


Layer& MultilayerPerceptron::getOutputLayer()
{
	XASSERT(mLayerVector.size() > 0, "MultilayerPerceptron::getOutputLayer(): Index out of bound.");
	return mLayerVector.back();
}


size_t MultilayerPerceptron::getLayerCount() const
{
	return mLayerVector.size();
}


size_t MultilayerPerceptron::getNeuronCount() const
{
	size_t c = 0;

	for (size_t i = 0; i < mLayerVector.size(); ++i)
	{
		c += mLayerVector[i].size();
	}

	return c;
}


std::string	MultilayerPerceptron::name() const
{
	return "multilayer_perceptron";
}


std::string	MultilayerPerceptron::reprezentation() const
{
	std::stringstream str;
	utils::setStreamMaxDoublePrecision(str);
	str << name() << "(learning_rate=" << mLearningRate << ",momentum=" << mMomentum << ",epoch=" << mEpoch;
	for (size_t i = 0; i < getLayerCount(); ++i)
	{
		str << ',' << getLayer(i).sizeUnbiased();
	}
	str << ')';
	return str.str();
}


std::string	MultilayerPerceptron::usage() const
{
	std::stringstream str;
	str << name() << "(learning_rate=<double_value>,momentum=<double_value>,<[int_value]input_layer_size>,<[int_value]first_hidden_layer_size>[,<[int_value]next_hidden_layer_size>][, ...],<[int_value]output_layer_size>)";
	return str.str();
}


void MultilayerPerceptron::feedForward(std::vector<double> const& pInputValues) const
{
	EXCEPTION(
		pInputValues.size() == getInputLayer().sizeUnbiased(),
		"MultilayerPerceptron::feedForward(): Feature count (" << pInputValues.size() <<
			") is different than input count (" << getOutputLayer().sizeUnbiased() << ").");

	/* latch input values */
	getInputLayer().setNeuronsOutputs(pInputValues);

	/* propagate to other layers */
	for (size_t i = 1; i < getLayerCount(); ++i)
	{
		getLayer(i).feedForward(getLayer(i - 1));
	}
}


void MultilayerPerceptron::backPropagation(std::vector<double> const& pTargetValues)
{
	/* compute error - MSE */
	mErorr = computeNetError(pTargetValues);

	getOutputLayer().computeOutputGradients(pTargetValues);

	/* without input layer, that is why > 0 not >= 0 */
	for (size_t i = getLayerCount() - 2; i > 0; --i)
	{
		getLayer(i).computeHiddenGradients(getLayer(i + 1));
	}

	/* update weights backward - from output layer to input layer 	*/
	/* without input layer, that is why > 0 not >= 0 				*/
	for (size_t i = getLayerCount() - 1; i > 0; --i)
	{
		getLayer(i).updateNeuronsInputWeights(
			getLayer(i - 1),
			mLearningRate,
			mMomentum);
	}
}


void MultilayerPerceptron::getResults(std::vector<double>& pResultValues) const
{
	pResultValues.resize(getOutputLayer().sizeUnbiased());

	for (size_t n = 0; n < pResultValues.size(); ++n)
	{
		pResultValues[n] = getOutputLayer().getNeuron(n).getOutputValue();
	}
}


double MultilayerPerceptron::computeNetError(std::vector<double> const& pTargetValues) const
{
	return getOutputLayer().computeError(pTargetValues);
}


auto MultilayerPerceptron::retrieveModel() const -> Model
{
	Model model;
	model.netData.learningRate 	= mLearningRate;
	model.netData.momentum		= mMomentum;

	Model::LayerDataVector& layers = model.netData.layerDataVector;

	layers.reserve(getLayerCount());
	for (size_t l = 0; l < getLayerCount(); ++l)
	{
		Model::LayerData layerData;
		layerData.neuronDataVector.resize(getLayer(l).size());
		layers.push_back(std::forward<Model::LayerData>(layerData));
		Model::NeuronDataVector& neurons = layers.back().neuronDataVector;

		for (size_t n = 0; n < getLayer(l).size(); ++n)
		{
			Neuron const& neuron = getLayer(l).getNeuron(n);

			neurons[n].gradient = neuron.getGradient();
			neurons[n].connectionVector = neuron.getConnectionVector();
		}
	}

	return model;
}


void MultilayerPerceptron::construct(TupleIdVector const& pTrainData)
{
	std::vector<double> target(1);
	for (size_t epoch = 0; epoch < mEpoch; epoch++)
	{
		clock_t begin = clock();
		for (size_t i = 0; i < pTrainData.size(); ++i)
		{
			Instance instance = getRankerData()->constructInstance(pTrainData[i]);
			target[0] = static_cast<double>(instance.getClass());

			feedForward(instance.getFeatureVector());
			backPropagation(target);
		}
		clock_t end = clock();
		printf("Epoch %i evaluated in %f s\n", epoch, double(end - begin) / CLOCKS_PER_SEC);
	}
}


double MultilayerPerceptron::rankInstance(Instance const& pInstance) const
{
	feedForward(pInstance.getFeatureVector());
	std::vector<double> result(getOutputLayer().sizeUnbiased());
	getResults(result);
	return result[0];
}


double MultilayerPerceptron::rank(TupleId pTupleId) const
{
	return rankInstance(getRankerData()->constructInstance(pTupleId));
}


double MultilayerPerceptron::rankTuple(TupleT const& pTupleT) const
{
	return rankInstance(getRankerData()->constructInstance(pTupleT));
}


int MultilayerPerceptron::classify(Instance const& pInstance) const
{
	EXCEPTION(false, "Classify function is quite primitive.");
	double rank = rankInstance(pInstance);
	return rank > 0.0 ? 1 : 0;
}


int MultilayerPerceptron::classify(TupleId pTupleId) const
{
	return classify(getRankerData()->constructInstance(pTupleId));
}


int MultilayerPerceptron::classify(TupleT const& pTupleT) const
{
	return classify(getRankerData()->constructInstance(pTupleT));
}


void MultilayerPerceptron::buildFromTopology(std::vector<size_t> const& pTopology)
{
	EXCEPTION(pTopology.size() >= 3, "MultilayerPerceptron::buildFromTopology(): Topology is too small, at least 3 layers are required.");

	/* build net */
	mLayerVector.reserve(pTopology.size());

	/* input layer with no input weights */
	mLayerVector.push_back(Layer(pTopology[0], 0));

	/* hiddens and output layers */
	for (size_t i = 1; i < pTopology.size(); ++i)
	{
		mLayerVector.push_back(Layer(pTopology[i], pTopology[i - 1]));
	}
}


void MultilayerPerceptron::buildFromTopology(
	std::vector<size_t> const& 	pTopology,
	double 						pLearningRate,
	double						pMomentum)
{
	mLearningRate = pLearningRate;
	mMomentum = pMomentum;
	buildFromTopology(pTopology);
}


void MultilayerPerceptron::buildFromModel(Model const& pModel)
{
	typedef Layer::NeuronVector __NeuronVector;

	mLearningRate 	= pModel.netData.learningRate;
	mMomentum		= pModel.netData.momentum;

	Model::LayerDataVector const& layers = pModel.netData.layerDataVector;
	mLayerVector.reserve(layers.size());

	for (size_t l = 0; l < layers.size(); ++l)
	{
		__NeuronVector neurons;
		neurons.reserve(layers[l].neuronDataVector.size());
		for (size_t n = 0; n < layers[l].neuronDataVector.size(); ++n)
		{
			neurons.push_back(Neuron(
				layers[l].neuronDataVector[n].connectionVector,
				n,
				layers[l].neuronDataVector[n].gradient));
		}

		mLayerVector.push_back(Layer(std::forward<__NeuronVector>(neurons)));
	}
}


	}
}
