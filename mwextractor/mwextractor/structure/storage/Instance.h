
#pragma once

#include <cstddef>	/* size_t */
#include <vector>
#include <string>
#include <ostream>


namespace structure
{
	namespace storage
	{


typedef std::vector<double> FeatureVector;


/**
 * \brief Klasa instancji przykładów dla maszynowego uczenia.
 *
 * Obiekty klasy przechowują informacje o konkretnych instancjach
 * przykładów przeznaczonych do uczenia maszynowego.
 * Zawarte w niej informacje to cechy -- liczby rzeczywiste oraz
 * klasa instnacji.
 *
 * @see Classifier
 */
class Instance
{
public:
	Instance(
		size_t pFeatureCount,
		size_t pClass);

	Instance(
		FeatureVector 	pFeatureVector,
		size_t 			pClass);


	Instance();
	Instance(Instance&& 				pInstance) = default;
	Instance(Instance const& 			pInstance) = default;
	Instance& operator=(Instance&& 		pInstance) = default;
	Instance& operator=(Instance const& pInstance) = default;

	~Instance() = default;


	FeatureVector const& 	getFeatureVector() const;
	FeatureVector& 			getFeatureVector();

	int						getClass() const;

private:
	FeatureVector	mFeatureVector;
	int				mClass;
};


std::ostream& operator<<(std::ostream& pStream, Instance const& pInstance);


	}
}
