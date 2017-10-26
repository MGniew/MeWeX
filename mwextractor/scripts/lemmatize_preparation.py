#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Skrypt przygotowuje zestaw krotek do lematyzacji
# poprzez dostawienie dwóch znaków nowej linii pomiędzy wszystkie
# krotki.


import sys


def main(p_input_file_path, p_output_file_path):
    with open(p_input_file_path, 'r') as input_file:
        input_file.readline() # header
        with open(p_output_file_path, 'w') as output_file:
            for line in input_file:
                output_file.write('%s\n\n\n' % (line.split('\t')[-1].strip()))


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
