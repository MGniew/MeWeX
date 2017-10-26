#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Skrypt konwertuje słownik Morfeusz SGJP 1
# do innego pliku, który może być użyty przykładowo jako 
# argument dla filtru lub jako zestaw krotek poprawnych
# dla funkcji oceny.

import codecs
import sys


def main(p_input_file_path, p_output_file_path):
    with codecs.open(p_input_file_path, 'r', 'iso8859_2') as f:
        with codecs.open(p_output_file_path, 'w', 'utf8') as output_file:
            done_words = set()
            for line in f:
                word = line.split(' ')[1]
                if word not in done_words:
                    done_words.add(word)
                    output_file.write('%s\n' % word)

"""
- - interp
A accusativus brev:pun
B bajt brev:npun
B biernik brev:pun
"""
if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
