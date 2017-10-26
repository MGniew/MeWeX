#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import corpus2


def capital_letters_ratio(p_word):
    length = 0
    capital = 0
    for char in p_word:
        is_dot = char == '.'
        if char.isalpha() or is_dot:
            length += 1
            if char.isupper() or is_dot:
                capital += 1
    return float(capital) / float(length) if length > 0 else 0.0


def get_next_sentence(p_reader):
    while True:
        sentence = p_reader.get_next_sentence()
        if not sentence:
            break
        yield sentence


def add_to_map(p_map, p_word):
    if p_word not in p_map:
        p_map[p_word] = 1
    else:
        p_map[p_word] += 1


def search_file(p_input_iob_corpus_file_path, p_append_map=None):
    tagset = corpus2.get_named_tagset('nkjp')
    reader = corpus2.TokenReader.create_path_reader('iob-chan', tagset, p_input_iob_corpus_file_path)

    result = {} if p_append_map is None else p_append_map
    for sentence in get_next_sentence(reader):
        lemmas = {index: token.get_preferred_lexeme(tagset).lemma_utf8()
                  for index, token in enumerate(sentence.tokens())}
        orths = {index: token.orth_utf8()
                 for index, token in enumerate(sentence.tokens())}

        for index, lemma in lemmas.iteritems():
            orth = orths[index]
            capital_ratio = capital_letters_ratio(lemma)
            if (capital_ratio >= 0.6) and (len(orth) >= 2):
                add_to_map(result, orth)
            if (lemma == '.') and (index > 0) and (index < len(lemmas) - 1):
                if len(lemmas[index - 1]) >= 2:
                    add_to_map(result, '%s.' % orths[index - 1])

    return result


def main(p_input_iob_corpus_file_path, p_output_file_path):
    result = search_file(p_input_iob_corpus_file_path)
    with open(p_output_file_path, 'w') as output_file:
        sorted_list = sorted([(score, word) for word, score in result.iteritems()], reverse=1)
        for score, word in sorted_list:
            output_file.write('%s\t%d\n' % (word, score))


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])