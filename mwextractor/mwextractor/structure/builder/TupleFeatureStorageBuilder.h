
#pragma once

#include <memory>

#include "../storage/TupleFeatureStorage.h"
#include "../storage/TupleFeatureGenerator.h"


namespace structure
{
	namespace builder
	{


/**
 * \brief Obiekt klasy buduje skład instnacji dla klasyfikatorów.
 *
 * Zadaniem tej klasy jest budowa składu instancji dla
 * klasyfikatorów na podstawie zadanego generatora cech,
 * składu krotek i zestawu identyfikatorów krotek, dla
 * których mają zostać wygenerowane cechy.
 *
 * @see TupleFeatureGenerator
 * @see MatrixTupleStorage
 * @see TupleFeatureStorage
 */
class TupleFeatureStorageBuilder
{
public:
	typedef std::shared_ptr<storage::MatrixTupleStorage>	MatrixTupleStoragePtrS;
	typedef storage::MatrixTupleStorage::TupleIdVector		TupleIdVector;
	typedef storage::TupleFeatureGenerator 					TupleFeatureGenerator;
	typedef storage::TupleFeatureStorage					TupleFeatureStorage;
	typedef std::shared_ptr<TupleFeatureStorage>			TupleFeatureStoragePtrS;

public:
	TupleFeatureStoragePtrS build(
		TupleFeatureGenerator const&	pTupleFeatureGenerator,
		MatrixTupleStoragePtrS const&	pTupleStorage,
		TupleIdVector const&			pInterestedTupleIdVector,
		size_t							pThreadCount) const;
};


	}
}
