
#pragma once

#include <vector>
#include <set>
#include <map>
#include <memory>

#include "WcclOperatorLoader.h"
#include "../../structure/storage/MatrixTupleStorage.h"


namespace structure
{
	namespace builder
	{


/**
 * \brief Parser korpusów -- ekstraktor form napotkanych.
 *
 * Zadaniem obiektu tej klasy jest ekstrakcja form napotkanych
 * z zadanego zestawu korpusów.
 *
 * @see CorporaParser
 */
class OrthExtractor
{
public:
	typedef	structure::storage::MatrixTupleStorage				TupleStorage;
	typedef std::shared_ptr<TupleStorage const>					TupleStorageConstPtrS;
	typedef TupleStorage::TupleId								TupleId;
	typedef std::vector<TupleId>								TupleIdVector;

	typedef WcclOperatorLoader<Wccl::Bool>::OperatorData		OperatorData;
	typedef std::vector<OperatorData>							OperatorDataVector;

	struct OrthForm
	{
		OrthForm(
			size_t pFrequency = 0,
			std::string const& pForm = "");

		mutable size_t 	frequency;
		std::string 	form;

		bool operator==(OrthForm const& pOrthForm)	const;
		bool operator!=(OrthForm const& pOrthForm)	const;
		bool operator<(OrthForm const& pOrthForm)	const;
		bool operator<=(OrthForm const& pOrthForm)	const;
		bool operator>(OrthForm const& pOrthForm)	const;
		bool operator>=(OrthForm const& pOrthForm)	const;
	};

	typedef std::set<OrthForm> 				OrthFormSet;
	typedef std::map<TupleId, OrthFormSet> 	OrthFormMap;

public:
	void extract(
		OrthFormMap&					pInputOutput,
		TupleStorageConstPtrS const&	pStorage,
		std::vector<std::string> const&	pCorporas,
		OperatorDataVector const&		pOperatorDataVector,
		Corpus2::Tagset const& 			pTagset,
		std::string const&				pReaderName) const;
};


	}
}
