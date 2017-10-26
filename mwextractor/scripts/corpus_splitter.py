#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Skrypt dzieli zadany korpus w formacie iob-chan 
# na zestaw podobnych rozmiarowo korpusów.

import sys

"""
Nie	nie	qub
mów	mówić	impt:sg:sec:imperf
:	:	interp
Jak	jak	adv:pos
to	to	subst:sg:nom:n
jest	być	fin:sg:ter:imperf
,	,	interp
że	że	comp
dni	dzień	subst:pl:nom:m3
dawne	dawny	adj:pl:nom:m3:pos
były	być	praet:pl:m3:imperf
lepsze	dobry	adj:pl:nom:m3:com
niż	niż	prep:nom
te	ten	adj:pl:nom:m3:pos
co	co	comp
są	być	fin:pl:ter:imperf
teraz	teraz	adv
?	?	interp

Bo	bo	comp
nie	nie	qub
z	z	prep:gen:nwok
mądrości	mądrość	subst:sg:gen:f
zapytujesz	zapytywać	fin:sg:sec:imperf
o	o	prep:acc
to	to	subst:sg:acc:n
.	.	interp

Eklezjasta	eklezjasta	subst:sg:nom:m1
7	7	ign
"""


def load_corpus_metadata(p_input_corpora_filepath):
    sentence_count = 0
    token_count = 0
    with open(p_input_corpora_filepath, 'r') as input_file:
        for line in input_file:
            line = line.strip()
            if len(line) == 0:
                sentence_count += 1
            else:
                token_count += 1
    return sentence_count, token_count


def split_corporas(p_output_directory_filepath, p_input_corpora_filepath, p_token_count, p_part_percentage_list):
    with open(p_input_corpora_filepath, 'r') as input_file:
        for i in range(0, len(p_part_percentage_list)):
            with open('%s/%d.iob-chan' % (p_output_directory_filepath, i), 'w') as output_file:
                token_count_goal = p_part_percentage_list[i] * float(p_token_count)
                current_corupus_size = 0
                to_break = False
                for line in input_file:
                    if current_corupus_size >= token_count_goal:
                        to_break = True
                    if to_break and len(line) == 1 and (i + 1) < len(p_part_percentage_list):
                        break
                    if len(line) > 1:
                        current_corupus_size += 1
                    output_file.write(line)


def prepare_parts_list(p_part_percentage_list):
    parts = []
    for value in p_part_percentage_list:
        parts.append(int(value))
    the_sum = sum(parts)
    assert the_sum <= 100 and the_sum >= 0
    if the_sum < 100:
        parts.append(100 - the_sum)
    return [(float(v) / 100.0) for v in parts]


def main(p_output_directory_filepath, p_input_corpora_filepath, p_part_percentage_list):
    print 'Reading metadata...'
    sentence_count, token_count = load_corpus_metadata(p_input_corpora_filepath)
    print 'Preparing parts...'
    part_percentage_list = prepare_parts_list(p_part_percentage_list)
    print 'Parts: %s' % str(part_percentage_list)
    print 'Sentence count: %d, token count: %d.' % (sentence_count, token_count)
    split_corporas(p_output_directory_filepath, p_input_corpora_filepath, token_count, part_percentage_list)
    print 'Split done.'


if __name__ == '__main__':
    if len(sys.argv) >= 5:
        main(sys.argv[1], sys.argv[2], sys.argv[3:])
    else:
        print 'usage: ./script.py output_directory input_iob_chan_corpus part_size_1 part_size_2 ...'
