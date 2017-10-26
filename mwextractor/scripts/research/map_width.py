#!/usr/bin/env python
# -*- coding: utf-8 -*-

__author__ = 'Xardanves'


"""
rounds: 3, folds: 5.
13383	13383
13410	13410
13395	13395
13370	13370
13223	13223
13490	13490
13397	13397
13254	13254
13385	13385
13255	13255
13339	13339
13331	13331
13384	13384
13304	13304
13423	13423
1
30000	30000	30000
frequency()	expected_frequency()	inversed_expected_frequency()
0	0	0
"""

import sys


class ProcessedFile:
    def __init__(self, p_name, p_functions_name, p_func_count, p_map_from, p_map_to):
        self.m_name = p_name if p_name.find('/') == -1 else p_name[p_name.rfind('/') + 1:]
        self.m_functions_name = ''
        for index, name in enumerate(p_functions_name.strip().split('\t')):
            self.m_functions_name += '&\t%d\t' % index
        self.m_functions_name += '\t\\\\'
        self.m_maps = {i: 0.0 for i in range(0, p_func_count)}
        self.m_map_from = p_map_from
        self.m_map_to = p_map_to

    def to_string(self, p_index, p_from_percent, p_to_percent):
        ret_value = '%d' % p_index
        for index in range(0, len(self.m_maps)):
            ret_value += ('\t&\t%f' % (self.m_maps[index] / float(self.m_map_to - self.m_map_from + 1))).replace('.', ',')
        return '%s\t\\\\' % ret_value


def parse_header(p_header):
    rounds, folds = p_header.strip().split(', ')
    rounds = int(rounds.split(' ')[1])
    folds = int(folds.split(' ')[1][0:-1])
    return rounds, folds 


def process_file(p_input_list_file, p_from_percent, p_to_percent):
    with open(p_input_list_file, 'r') as input_file:
        rounds, folds = parse_header(input_file.readline())  # header
        length = min([int(input_file.readline().split('\t')[1]) for i in range(0, rounds * folds)])
        input_file.readline()  # width
        line = input_file.readline()
        func_count = len(line.strip().split('\t'))
        #output_file.write(line)  # lengths
        output = ProcessedFile(
            p_input_list_file,
            input_file.readline(),
            func_count,
            int(float(length) * p_from_percent),
            int(float(length) * p_to_percent - 1))
        for i in range(0, output.m_map_from):
            input_file.readline()
        for i in range(output.m_map_from, output.m_map_to):
            parts = input_file.readline().strip().split('\t')
            for index, value in enumerate(parts):
                value = float(value.replace(',', '.'))
                output.m_maps[index] += value
    return output


def main(p_output_file, p_input_list_file_list, p_from_percent, p_to_percent):
    with open(p_input_list_file_list, 'r') as file_list:
        parsed_files = [process_file(the_file.strip(), p_from_percent, p_to_percent) for the_file in file_list]
    with open(p_output_file, 'w') as output_file:
        output_file.write('%d -- %d\t%s\n' % (p_from_percent * 100.0, p_to_percent * 100.0, parsed_files[0].m_functions_name))
        for index, parsed_file in enumerate(parsed_files):
            output_file.write('%s\n' % parsed_file.to_string(index, p_from_percent, p_to_percent))


"""
output_file.csv
input_merged_list.csv
from [0:1]
to [from:1]
"""
if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2], float(sys.argv[3]), float(sys.argv[4]))
