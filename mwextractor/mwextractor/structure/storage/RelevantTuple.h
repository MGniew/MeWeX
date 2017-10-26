
#pragma once

#include <vector>

#include "MatrixTupleStorage.h"


namespace structure
{
	namespace storage
	{


/**
 * \brief Klasa pomocnicza w procesie oceny kolokacji.
 *
 * Obiekty klasy reprezentują krotki (zestawy słów).
 * Krotki mogą być ze sobą porównywane na dwa sposoby.
 * Klasa miała na celu obudowanie funkcjonalności związanej
 * z porównywaniem ze sobą różnych krotek na dwa sposoby --
 * przy założeniu szyku ustalonego i dowolnego.
 */
class RelevantTuple
{
public:
	typedef MatrixTupleStorage::TupleT TupleT;

public:
	RelevantTuple(size_t pElementCount);

	RelevantTuple(std::vector<std::string>&& 		pElements);
	RelevantTuple(std::vector<std::string> const& 	pElements);

	RelevantTuple(
		MatrixTupleStorage const& 	pStorage,
		TupleT const&				pTuple);

	RelevantTuple() 												= default;
	RelevantTuple(RelevantTuple&& 					pRelevantTuple) = default;
	RelevantTuple(RelevantTuple const& 				pRelevantTuple) = default;
	RelevantTuple& operator=(RelevantTuple&&		pRelevantTuple) = default;
	RelevantTuple& operator=(RelevantTuple const& 	pRelevantTuple) = default;

	virtual ~RelevantTuple() = default;


	std::string const& 	operator[](size_t pIndex) const;
	std::string& 		operator[](size_t pIndex);

	std::vector<std::string> const& getElements() const;
	std::vector<std::string>& 		getElements();

	size_t size() const;

	bool equalFlexible(RelevantTuple const& pRelevantTuple)	const;
	bool equalFixed(RelevantTuple const& pRelevantTuple)	const;

	bool operator==(RelevantTuple const& pRelevantTuple) 	const;
	bool operator!=(RelevantTuple const& pRelevantTuple) 	const;
	bool operator<(RelevantTuple const& pRelevantTuple) 	const;
	bool operator>(RelevantTuple const& pRelevantTuple) 	const;
	bool operator<=(RelevantTuple const& pRelevantTuple) 	const;
	bool operator>=(RelevantTuple const& pRelevantTuple) 	const;

private:
	bool isWordIn(std::string const& pWord) const;

private:
	/* Element count is low so that's why vector is used instead of map or set */
	std::vector<std::string> mElements;
};


std::ostream& operator<<(std::ostream& pStream, RelevantTuple const& pTuple);


	}
}


namespace std
{


template <>
struct hash<structure::storage::RelevantTuple>
{
	typedef structure::storage::RelevantTuple __RelevantTuple;

	size_t operator()(__RelevantTuple const& pRelevantTuple) const
	{
		size_t 				hashValue = 0;
		hash<std::string>	hasher;

		for (size_t i = 0; i < pRelevantTuple.size(); ++i)
		{
			hashValue += hasher(pRelevantTuple[i]);
		}

		return hashValue;
	}
};


}
