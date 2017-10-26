
#include "../../utils/Parallel.h"
#include "../../utils/Textual.h"
#include "../../utils/Time.h"

#include "CorporaParser.h"


namespace structure
{
	namespace builder
	{


auto CorporaParser::parse(
	std::vector<std::string> const&	pCorporas,
	WcclOperatorDataVector const& 	pOperators,
	Corpus2::Tagset const& 			pTagset,
	std::string const&				pReaderName) -> TupleStoragePtrS
{
	TupleStoragePtrS storage(new TupleStorage());

	// update relations list and variables names
	std::vector<TupleStorage::RelationId> 	relations(pOperators.size());
	std::vector<std::string> 				wcclVariables;

	for (size_t op = 0; op < pOperators.size(); ++op)
	{
		relations[op] = storage->addRelationGetId(TupleStorage::RelationT(
			pOperators[op].group,
			pOperators[op].name,
			pOperators[op].size,
			0.0,
			pCorporas.size()));

		while (wcclVariables.size() < pOperators[op].size)
		{
			std::stringstream s;
			s << "Pos" << (wcclVariables.size() + 1);
			wcclVariables.push_back(s.str());
		}
	}

	utils::Time wholeTimeBegin;

	// parse corporas
	for (size_t c = 0; c < pCorporas.size(); ++c)
	{
		std::cerr << "corpus nr: " << c << ", name: " << pCorporas[c] << std::endl;
		utils::Time corpusTimeBegin;

		size_t 					tokens 		= 0;
		TupleStorage::CorporaId corporaId 	= storage->addCorporaGetId(TupleStorage::CorporaT(pCorporas[c], c));

		Corpus2::TokenReader::TokenReaderPtr reader =
			Corpus2::TokenReader::create_path_reader(
				pReaderName,
				pTagset,
				pCorporas[c]);

		std::vector<TupleStorage::WordId> 	vecPosWord;
		Corpus2::Sentence::Ptr 				sentence;
		while ((sentence = reader->get_next_sentence()) != nullptr)
		{
			size_t sentenceSize = sentence->size();
			if (vecPosWord.size() < sentenceSize)
			{
				vecPosWord.resize(sentenceSize);
			}

			for (size_t t = 0; t < sentenceSize; ++t)
			{
				Corpus2::Token* token = sentence->at(t);
				Corpus2::Lexeme lexem = token->get_preferred_lexeme(pTagset);

				TupleStorage::PartOfSpeechT pos(pTagset.get_pos_name(lexem.tag().get_pos()), 1.0, pCorporas.size());
				pos.getMetadata().setLocalFrequency(c, 1);
				TupleStorage::PartOfSpeechId posId = storage->addPartOfSpeechGetId(pos);

				TupleStorage::WordT word = TupleStorage::WordT(posId, lexem.lemma_utf8(), 1.0, pCorporas.size());
				word.getMetadata().setLocalFrequency(c, 1);
				vecPosWord[t] = storage->addWordGetId(word);

				++tokens;
			}

			// parallel is slower...
			for (size_t t = 0; t < sentenceSize; ++t)
			{
				Wccl::SentenceContext sc(sentence);
				sc.set_position(t);
				for (size_t op = 0; op < pOperators.size(); ++op)
				{

					// It generates less tuples...
					//if (op + pOperators[op].size > sentenceSize)
					//{
					//	continue;
					//}

					auto result = pOperators[op].body->apply(sc);
					if (!result->get_value())
					{
						continue;
					}

					TupleStorage::TupleT tuple(pOperators[op].size, relations[op], 1.0, pCorporas.size());
					tuple.getMetadata().setLocalFrequency(c, 1);
					for (size_t pos = 0; pos < pOperators[op].size; ++pos)
					{
						int tokenPos = sc.get_abs_position(pOperators[op].body->get<Wccl::Position>(wcclVariables[pos]));
						tuple[pos] = vecPosWord[tokenPos];
					}
					storage->addTuple(tuple);
				}
			}

			vecPosWord.clear();
		}									// for every sentence

		storage->findCorpora(corporaId).setTokenCount(tokens);

		utils::Time corpusTimeEnd;
		std::cerr << "Corpus parsed in: " << (corpusTimeEnd - corpusTimeBegin) << 's' << std::endl;
	}										// for every corpus

	utils::Time wholeTimeEnd;
	std::cerr << "All corporas parsed in: " << (wholeTimeEnd - wholeTimeBegin) << 's' << std::endl;

	return storage;
}


	}
}
