#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Skrypt laczy listy k-najlepszych krotek z odpowiadajacymi im 
# formami napotkanymi.

import sys


def parse_orths_list(p_orths_list_file_path):
    orth_dict = {}
    current_element_list = None
    with open(p_orths_list_file_path, 'r') as orths_file:
        for line in orths_file:
            if not line.startswith('\t'):
                current_element_list = []
                orth_dict[line.strip()] = current_element_list
            else:
                line = line.strip()
                split = line.find(' ')
                frequency = int(line[0:split])
                tuple = line[split + 1:]
                current_element_list.append((frequency, tuple))
    return orth_dict


def process(p_output_file_path, p_kbest_list_file_path, p_orth_dict):
    with open(p_kbest_list_file_path, 'r') as kbest_file:
        with open(p_output_file_path, 'w') as output_file:
            output_file.write(kbest_file.readline())
            output_file.write(kbest_file.readline())
            for line in kbest_file:
                line = line.strip()
                output_file.write(line)
                orths = p_orth_dict[line[line.find('\t') + 1:]]
                for orth in sorted(orths, reverse=True):
                    output_file.write('\t%i %s' % orth)
                output_file.write('\n')


def main(p_output_file_path, p_kbest_list_file_path, p_orths_list_file_path):
    orth_dict = parse_orths_list(p_orths_list_file_path)
    process(p_output_file_path, p_kbest_list_file_path, orth_dict)


"""
This script merge kbest list with orths

usage: script.py output_file input_file_with_kbest_list input_file_with_orth_list
"""
if __name__ == '__main__':
    required_argument_count = 3
    if len(sys.argv) == (required_argument_count + 1):
        main(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        print 'Error: required argument count: %i, passed: %i' % \
              (required_argument_count, (len(sys.argv) - 1))
        print "usage: script.py output_file input_file_with_kbest_list input_file_with_orth_list"
