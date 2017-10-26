/*
 * CompressedFrequencyStorage.h
 *
 *  Created on: 08-07-2014
 *      Author: michalw
 */

#pragma once

#include <cstddef>
#include <vector>
#include <map>

#include "../container/CompressedVector.h"


namespace structure
{
	namespace storage
	{

/**
 * \brief Skompresowana wersja składu częstości.
 *
 * Ta wersja od RawFrequencyStorage różni się tym, że oszczędza
 * miejsce w pamięci w przypadku dużej liczby zer.
 *
 * @see RawFrequencyStorage
 */
class CompressedFrequencyStorage {
public:
	typedef std::vector<size_t> FrequencyVector;

	typedef container::CompressedVector<size_t>				LocalFrequencies;
	typedef typename LocalFrequencies::ValueIterator		ValueIterator;
	typedef typename LocalFrequencies::ValueIteratorConst	ValueIteratorConst;

public:
	CompressedFrequencyStorage(
		double pGlobalFrequency = 0,
		size_t pSourceCount		= 0);

	CompressedFrequencyStorage(
		double	 		pGlobalFrequency,
		FrequencyVector	pSourceFrequencies);

	CompressedFrequencyStorage(CompressedFrequencyStorage&& 				pStorage)	= default;
	CompressedFrequencyStorage(CompressedFrequencyStorage const& 			pStorage)	= default;
	CompressedFrequencyStorage& operator=(CompressedFrequencyStorage&&		pStorage)	= default;
	CompressedFrequencyStorage& operator=(CompressedFrequencyStorage const& pStorage)	= default;

	~CompressedFrequencyStorage() = default;


	void addNewLocalFrequency(size_t pSource, size_t pFrequency);
	void addFrequencies(CompressedFrequencyStorage const& pStorage);
	void subtractFrequencies(CompressedFrequencyStorage const& pStorage);


	double getGlobalFrequency() 				const;
	size_t getSourceCount()						const;
	size_t getLocalFrequency(size_t pSource)	const;

	void setGlobalFrequency(double pFrequency);
	void setLocalFrequency(size_t pSource, size_t pFrequency);

	void modifyGlobalFrequency(double pDelta);
	void modifyLocalFrequency(size_t pSource, size_t pDelta);
	void modifyFrequency(size_t pSource, size_t pDelta);

	double 	sumLocalFrequencies() 		const;
	void 	computeGlobalFrequency();

	size_t countNonZeroSources() const;

	std::ostream&	writeFrequenciesReprezentation(std::ostream& pStream) 	const;
	std::string 	createFrequenciesReprezentation() 						const;


	ValueIteratorConst	begin() const;
	ValueIterator		begin();
	ValueIteratorConst	end() 	const;
	ValueIterator		end();


private:
	double				mGlobalFrequency;
	LocalFrequencies	mLocalFrequencies;
};

	}
}
