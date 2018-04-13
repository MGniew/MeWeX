
#pragma once

#include "../Classifier.h"

#include "Model.h"
#include "Layer.h"


namespace machine_learning
{
	namespace multilayer_perceptron
	{


/**
 * \brief Perceptron wielowarstwowy.
 *
 * Klasa jest implementacją perceptronu wielowarstwowego.
 * Liczba warstw i neuronów w nich jest dowolna.
 * Każda z warstw jest w pełni połączona z sąsiednimi.
 * Dodane są także neurony typu bias.
 *
 * @see Classifier
 */
class MultilayerPerceptron : public Classifier
{
public:
	typedef std::vector<Layer> LayerVector;

public:
	MultilayerPerceptron();

	/**
	 * \brief Tworzy nienauczoną sieć o zadanej topologii.
	 *
	 * Topologia to liczby neuronów we wszystkich warstwach.
	 */
	MultilayerPerceptron(
		std::vector<size_t> const& 	pTopology,
		double						pLearningRate = 0.15,
		double						pMomentum = 0.5);

	/**
	 * \brief Sieć jest odtwarzana z modelu.
	 */
	MultilayerPerceptron(Model const& pModel);

	/**
	 * \brief Budowa na podstawie konkretnych warstw.
	 */
	MultilayerPerceptron(
		LayerVector const& 	pLayerVector,
		double				pLearningRate = 0.15,
		double				pMomentum = 0.5);

	MultilayerPerceptron(MultilayerPerceptron&& 				pMultilayerPerceptron) = default;
	MultilayerPerceptron(MultilayerPerceptron const& 			pMultilayerPerceptron) = default;
	MultilayerPerceptron& operator=(MultilayerPerceptron&&	 	pMultilayerPerceptron) = default;
	MultilayerPerceptron& operator=(MultilayerPerceptron const& pMultilayerPerceptron) = default;

	virtual ~MultilayerPerceptron() = default;

	virtual ClassifierPtrS clone() const override;

	virtual StringParameterMap retrieveFunctionParameters() const override;

	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters) override;


	Layer const& 		getInputLayer() 		const;
	Layer& 				getInputLayer();

	Layer const& 		getLayer(size_t pIndex) const;
	Layer& 				getLayer(size_t pIndex);

	Layer const& 		getOutputLayer() 		const;
	Layer& 				getOutputLayer();

	size_t 				getLayerCount() 		const;
	size_t 				getNeuronCount() 		const;

	virtual std::string	name() 					const override;

	/**
	 * \brief Funkcja zwraca reprezentacje Perceptrona Wielowarstwowego.
	 *
	 * Funckja zwraca reprezentację Perceptrona Wielowarstwowego, ale
	 * bez informacji o wagach, gradientach błędów i zmianach wag, a
	 * co za tym idzie odtworzyć z niej można jedynie samą strukturę
	 * klasyfikatora niewyuczonego. W celu otrzymania modelu tej sieci,
	 * z której następnie można odtworzyć nauczony i mogący kontynuować
	 * naukę klasyfikator należy użyć funkcji "retrieveModel".
	 *
	 * \see retrieveModel
	 */
	virtual std::string	reprezentation() 	const override;

	virtual std::string	usage() 			const override;


	/**
	 * \brief Klasyfikacja za pomocą sieci.
	 *
	 * Arugmentem wejściowym jest zestaw cech do klasyfikacji.
	 * Stany neuronów są aktualizowane przy przejściu, a wynik
	 * zapisany wewnątrz sieci na neuronach wyjściowych.
	 * Odpowiedź sieć można uzyskać za pomocą funkcji getResults.
	 *
	 * @param pInputValues wektor cech
	 *
	 * @see getResults
	 */
	void feedForward(std::vector<double> const& pInputValues) const;

	/**
	 * \brief Funkcja przelicza jeden przebieg uczenia sieci.
	 *
	 * Przed użyciem tej funkcji należy wywołać feedForward.
	 * Innymi słowy załadować dane, a następnie wykonać jeden
	 * przebieg uczenia.
	 *
	 * @param pTargetValues wektor poprawny dla instancji z poprzedniego przebiegu feedForward
	 *
	 * @see feedForward
	 */
	void backPropagation(std::vector<double> const& pTargetValues);

	/**
	 * \brief Ekstrakcja wyniku z ostatniego wywołania feedForward.
	 *
	 * @see feedForward
	 */
	void getResults(std::vector<double>& pResultValues) const;

	double computeNetError(std::vector<double> const& pTargetValues) const;

	/**
	 * \brief Funkcja buduje model aktualnego stanu sieci.
	 *
	 * Zapisywane są także wartości gradientów błędu, a tym
	 * samym sieć może być douczana.
	 */
	Model retrieveModel() const;


	virtual void construct(TupleIdVector const& pTrainData) override;

	virtual double rankInstance(Instance const& pInstance) 	const override;
	virtual double rank(TupleId pTupleId)					const override;
	virtual double rankTuple(TupleT const& pTupleT) 		const override;

	virtual int classify(Instance const& pInstance) 		const override;
	virtual int classify(TupleId pTupleId)					const override;
	virtual int classify(TupleT const& pTupleT)				const override;


private:
	void buildFromTopology(std::vector<size_t> const& pTopology);
	void buildFromTopology(
		std::vector<size_t> const& 	pTopology,
		double 						pLearningRate,
		double						pMomentum);

	void buildFromModel(Model const& pModel);


private:
	LayerVector mLayerVector;
	double		mErorr;
	double 		mLearningRate;
	double 		mMomentum;
	int 		mEpoch;
};


	}
}
