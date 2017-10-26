
#pragma once

#include <memory>

#include "WcclOperatorLoader.h"
#include "../../structure/storage/MatrixTupleStorage.h"


namespace structure
{
	namespace builder
	{


/**
 * \brief Parser korpusu.
 *
 * Zadaniem obiektu tej klasy jest budowa składu krotek
 * poprzez parsowanie korpusów tekstowych z wykorzystaniem
 * zadanego zestawu relacji.
 *
 * @see WcclOperatorLoader
 * @see MatrixTupleStorage
 */
class CorporaParser
{
public:
	typedef	structure::storage::MatrixTupleStorage					TupleStorage;
	typedef std::shared_ptr<TupleStorage>							TupleStoragePtrS;
	typedef WcclOperatorLoader<Wccl::Bool>::WcclOperatorDataVector	WcclOperatorDataVector;

public:
	TupleStoragePtrS parse(
		std::vector<std::string> const&	pCorporas,
		WcclOperatorDataVector const& 	pOperators,
		Corpus2::Tagset const& 			pTagset,
		std::string const&				pReaderName);
};


	}
}
