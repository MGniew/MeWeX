
#pragma once

#include <string>


namespace structure
{
	namespace storage
	{


/**
 * \brief Klasa przechowująca informacje o korpusie.
 *
 * Klasa przechowuje nazwę korpusu, jego numer
 * sekwencyjny (identyfikator) oraz liczbę tokenów
 * w nim zawartych.
 */
class Corpora
{
public:
	Corpora(
		std::string pName,
		size_t		pSequenceNumber,
		size_t		pTokenCount = 0);

	Corpora(Corpora&& 					pCorpora)	= default;
	Corpora(Corpora const& 				pCorpora) 	= default;
	Corpora& operator=(Corpora&&	 	pCorpora) 	= default;
	Corpora& operator=(Corpora const& 	pCorpora) 	= default;

	~Corpora() = default;


	std::string			getNameCopy()		const;
	std::string const& 	getName() 			const;
	std::string&		getName();

	size_t				getSequenceNumber() const;

	size_t				getTokenCount()		const;


	void				setTokenCount(size_t pTokens)	const;
	void 				modifyTokenCount(size_t pDelta)	const;


	bool operator==(Corpora const& pCorpora) 	const;
	bool operator!=(Corpora const& pCorpora) 	const;
	bool operator>(Corpora const& pCorpora) 	const;
	bool operator<(Corpora const& pCorpora) 	const;
	bool operator>=(Corpora const& pCorpora) 	const;
	bool operator<=(Corpora const& pCorpora) 	const;


private:
	mutable size_t	mTokenCount;
	std::string 	mName;
	size_t			mSequenceNumber;
};


	}
}


namespace std
{


template <>
struct hash<structure::storage::Corpora>
{
	typedef structure::storage::Corpora __Corpora;

	size_t operator()(__Corpora const& pCorpora) const
	{
		return pCorpora.getTokenCount();
	}
};


}
