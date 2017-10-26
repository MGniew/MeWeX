
#pragma once

#include <libcorpus2/tagsetmanager.h>
#include <libcorpus2/io/xcesreader.h>
#include <libwccl/ops/operator.h>
#include <libwccl/parser/Parser.h>

#include "../../utils/Textual.h"
#include "../../utils/Debug.h"


namespace structure
{
	namespace builder
	{


/**
 * \brief Klasa ładująca operatory WCCL z pliku.
 *
 * Zadaniem obiektu tej klasy jest ładowanie operatorów
 * zapisanych w jezyku WCCL.
 * Operatory te zostać mogą potem wykorzystane przykładowo
 * jako relacje.
 *
 * @see Relation
 */
template <typename WcclType>
class WcclOperatorLoader
{
public:
	typedef boost::shared_ptr<Wccl::Operator<WcclType>> WcclOperatorPtr;

	struct OperatorData
	{
		WcclOperatorPtr body;
		size_t			group;
		std::string		name;
		size_t			size;
	};

	typedef std::vector<OperatorData> WcclOperatorDataVector;


public:
	void loadOperators(
		Corpus2::Tagset const&	pTagset,
		std::string const& 		pOperatorFile,
		std::string const& 		pSearchDir,
		WcclOperatorDataVector&	pOutput);

	WcclOperatorDataVector loadOperators(
		Corpus2::Tagset const&	pTagset,
		std::string const& 		pOperatorFile,
		std::string const& 		pSearchDir);

	WcclOperatorDataVector loadOperators(
		Corpus2::Tagset const&			pTagset,
		std::vector<std::string> const& pOperatorFile,
		std::string const& 				pSearchDir);

	void parseOperatorName(
		std::string const& 	pOperatorName,
		OperatorData&		pOperatorData) 	const;
};


template <typename WcclType>
void WcclOperatorLoader<WcclType>::loadOperators(
	Corpus2::Tagset const&	pTagset,
	std::string const& 		pOperatorFilePath,
	std::string const& 		pSearchDir,
	WcclOperatorDataVector&	pOutput)
{
	std::ifstream file(pOperatorFilePath.c_str());
	EXCEPTION(file.is_open(), "Error occured while trying to open operators file '" << pOperatorFilePath << "'.");
	file.close();

	Wccl::Parser parser(pTagset);
	auto operatorsFile 		= parser.parseWcclFileFromPath(pOperatorFilePath, pSearchDir);
	auto& sectionsVector	= operatorsFile->sections<WcclType>();

	pOutput.reserve(pOutput.size() + sectionsVector.size());

	for (size_t i = 0; i < sectionsVector.size(); ++i)
	{
		for (size_t p = 0; p < sectionsVector[i]->size(); ++p)
		{
			pOutput.push_back(OperatorData());
			pOutput.back().body = sectionsVector[i]->get_ptr(p);
			parseOperatorName(sectionsVector[i]->name(), pOutput.back());
		}
	}
}


template <typename WcclType>
auto WcclOperatorLoader<WcclType>::loadOperators(
	Corpus2::Tagset const&	pTagset,
	std::string const& 		pOperatorFile,
	std::string const& 		pSearchDir) -> WcclOperatorDataVector
{
	WcclOperatorDataVector operators;
	loadOperators(pTagset, pOperatorFile, pSearchDir, operators);
	return operators;
}


template <typename WcclType>
auto WcclOperatorLoader<WcclType>::loadOperators(
	Corpus2::Tagset const&			pTagset,
	std::vector<std::string> const& pOperatorFile,
	std::string const& 				pSearchDir) -> WcclOperatorDataVector
{
	WcclOperatorDataVector vector;

	for (size_t f = 0; f < pOperatorFile.size(); ++f)
	{
		loadOperators(pTagset, pOperatorFile[f], pSearchDir, vector);
	}

	return vector;
}


template <typename WcclType>
void WcclOperatorLoader<WcclType>::parseOperatorName(
	std::string const& 		pOperatorName,
	OperatorData&			pOperatorData) const
{
	size_t first = pOperatorName.find_first_of('_');
	size_t last = pOperatorName.find_last_of('_');

	EXCEPTION(first != std::string::npos && first != last, "Operator name doesn't contains metadata (groupIdx_relationName_relationSize)'" << pOperatorName << "'.");

	pOperatorData.group = utils::toSizeT(pOperatorName.substr(0, first));
	pOperatorData.name = pOperatorName.substr(first + 1, last - first - 1);
	pOperatorData.size = utils::toSizeT(pOperatorName.substr(last + 1));
}


	}
}
