
#include "../../utils/Textual.h"
#include "../../utils/Time.h"

#include "OrthExtractor.h"


namespace structure
{
	namespace builder
	{


OrthExtractor::OrthForm::OrthForm(
	size_t 				pFrequency,
	std::string const& 	pForm)
:
	frequency(pFrequency),
	form(pForm)
{

}


bool OrthExtractor::OrthForm::operator==(OrthForm const& pOrthForm) const
{
	return form == pOrthForm.form;
}


bool OrthExtractor::OrthForm::operator!=(OrthForm const& pOrthForm) const
{
	return form != pOrthForm.form;
}


bool OrthExtractor::OrthForm::operator<(OrthForm const& pOrthForm) const
{
	return form < pOrthForm.form;
}


bool OrthExtractor::OrthForm::operator<=(OrthForm const& pOrthForm) const
{
	return form <= pOrthForm.form;
}


bool OrthExtractor::OrthForm::operator>(OrthForm const& pOrthForm) const
{
	return form > pOrthForm.form;
}


bool OrthExtractor::OrthForm::operator>=(OrthForm const& pOrthForm) const
{
	return form >= pOrthForm.form;
}


void OrthExtractor::extract(
	OrthFormMap&					pInputOutput,
	TupleStorageConstPtrS const&	pStorage,
	std::vector<std::string> const&	pCorporas,
	OperatorDataVector const&		pOperatorDataVector,
	Corpus2::Tagset const& 			pTagset,
	std::string const&				pReaderName) const
{
	// update relations list and variables names
	std::vector<TupleStorage::RelationId> 	relations(pOperatorDataVector.size());
	std::vector<std::string> 				wcclVariables;
	OrthForm								findOrthForm(1, "");

	for (size_t op = 0; op < pOperatorDataVector.size(); ++op)
	{
		relations[op] = pStorage->findRelationIdSilent(TupleStorage::RelationT(
			pOperatorDataVector[op].group, pOperatorDataVector[op].name, 0, 0.0, 0));
		while (wcclVariables.size() < pOperatorDataVector[op].size)
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

		Corpus2::TokenReader::TokenReaderPtr reader =
			Corpus2::TokenReader::create_path_reader(
				pReaderName,
				pTagset,
				pCorporas[c]);

		std::vector<TupleStorage::WordId> 	vecPosWord;
		std::vector<std::string> 			vecPosOrth;
		std::vector<std::string> 			vecPos;
		Corpus2::Sentence::Ptr 				sentence;
		while ((sentence = reader->get_next_sentence()) != nullptr)
		{
			size_t sentenceSize = sentence->size();
			if (vecPosWord.size() < sentenceSize)
			{
				vecPosWord.resize(sentenceSize);
				vecPosOrth.resize(sentenceSize);
				vecPos.resize(sentenceSize);
			}

			for (size_t t = 0; t < sentenceSize; ++t)
			{
				Corpus2::Token* token = sentence->at(t);
				Corpus2::Lexeme lexem = token->get_preferred_lexeme(pTagset);

				TupleStorage::PartOfSpeechT pos(pTagset.get_pos_name(lexem.tag().get_pos()), 0.0, 0);
				TupleStorage::PartOfSpeechId posId = pStorage->findPartOfSpeechIdSilent(pos);

				TupleStorage::WordT word = TupleStorage::WordT(posId, lexem.lemma_utf8(), 0.0, 0);
				vecPosWord[t] = pStorage->findWordIdSilent(word);
				vecPosOrth[t] = token->orth_utf8();
				vecPos[t] = pTagset.tag_to_string(lexem.tag());
			}

			for (size_t t = 0; t < sentenceSize; ++t)
			{
				Wccl::SentenceContext sc(sentence);
				sc.set_position(t);
				for (size_t op = 0; op < pOperatorDataVector.size(); ++op)
				{
					auto result = pOperatorDataVector[op].body->apply(sc);
					if (!result->get_value())
					{
						continue;
					}

					TupleStorage::TupleT tuple(pOperatorDataVector[op].size, relations[op], 0.0, 0);
					for (size_t pos = 0; pos < pOperatorDataVector[op].size; ++pos)
					{
						int tokenPos = sc.get_abs_position(pOperatorDataVector[op].body->get<Wccl::Position>(wcclVariables[pos]));
						tuple[pos] = vecPosWord[tokenPos];
					}

					auto tupleId = pStorage->findTupleIdSilent(tuple);
					if (tupleId == nullptr)
					{
						continue;
					}

					OrthFormMap::iterator iter = pInputOutput.find(tupleId);
					if (iter == pInputOutput.end())
					{
						continue;
					}

					std::set<int> indices;
					for (size_t pos = 0; pos < pOperatorDataVector[op].size; ++pos)
					{
						int tokenPos = sc.get_abs_position(pOperatorDataVector[op].body->get<Wccl::Position>(wcclVariables[pos]));
						indices.insert(tokenPos);
					}

					std::stringstream str;
					for (auto pos = indices.begin(); pos != indices.end(); ++pos)
					{
						str << vecPosOrth[*pos];
						if (*pos < *indices.rbegin())
						{
							str << ' ';
						}
					}

					std::stringstream posstr;
					for (auto pos = indices.begin(); pos != indices.end(); ++pos)
					{
						posstr << vecPos[*pos];
						if (*pos < *indices.rbegin())
						{
							posstr << ' ';
						}
					}

					findOrthForm.form = str.str();
					findOrthForm.tag = posstr.str();

					auto setIter = iter->second.find(findOrthForm);
					if (setIter != iter->second.end())
					{
						setIter->frequency += 1;
					}
					else
					{
						iter->second.emplace(findOrthForm);
					}
				}
			}								// for every operator

			vecPosWord.clear();
			vecPosOrth.clear();
			vecPos.clear();
		}									// for every sentence

		utils::Time corpusTimeEnd;
		std::cerr << "Corpus parsed in: " << (corpusTimeEnd - corpusTimeBegin) << 's' << std::endl;
	}										// for every corpora

	utils::Time wholeTimeEnd;
	std::cerr << "All corporas parsed in: " << (wholeTimeEnd - wholeTimeBegin) << 's' << std::endl;
}


	}
}
