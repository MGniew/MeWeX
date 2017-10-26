/*
 * RawFrequencyStorage.h
 *
 *  Created on: 08-07-2014
 *      Author: michalw
 */

#pragma once

#include <cstddef>
#include <vector>
#include <map>


namespace structure
{
	namespace storage
	{


/**
 * \brief Skład częstości.
 *
 * Skład częstości przechowuje informacje o częstościach poszczególnych
 * elementów jak i sumę tych częstości.
 *
 * @see CompressedFrequencyStorage
 */
class RawFrequencyStorage {
public:
	typedef std::vector<size_t> FrequencyVector;

	typedef std::vector<size_t> 				LocalFrequencies;
	typedef LocalFrequencies::iterator			ValueIterator;
	typedef LocalFrequencies::const_iterator	ValueIteratorConst;

public:
	RawFrequencyStorage(
		double pGlobalFrequency = 0,
		size_t pSourceCount		= 0);

	RawFrequencyStorage(
		double	 		pGlobalFrequency,
		FrequencyVector	pSourceFrequencies);

	RawFrequencyStorage(RawFrequencyStorage&& 					pStorage)	= default;
	RawFrequencyStorage(RawFrequencyStorage const& 				pStorage)	= default;
	RawFrequencyStorage& operator=(RawFrequencyStorage&&		pStorage)	= default;
	RawFrequencyStorage& operator=(RawFrequencyStorage const& 	pStorage)	= default;

	~RawFrequencyStorage() = default;


	void addNewLocalFrequency(size_t pSource, size_t pFrequency);
	void addFrequencies(RawFrequencyStorage const& pStorage);
	void subtractFrequencies(RawFrequencyStorage const& pStorage);


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
