#!/usr/bin/env python
# -*- coding: utf-8 -*-


__author__ = 'michalw'

import sys


def open_files(p_file_with_input_files):
    file_handlers = {}  # index : file_handler
    for file_path in p_file_with_input_files:
        file_handlers[len(file_handlers)] = open(file_path.strip(), 'r')
    return file_handlers


def gather_metadata(p_files):
    is_same_quality_function = set()
    association_names = {}
    lengths = {}
    width = -1
    for index, file_handler in p_files.iteritems():
        association_names[index] = file_handler.readline().strip()
        is_same_quality_function.add(file_handler.readline().strip())
        new_length, new_width = file_handler.readline().strip().split('\t')
        lengths[index] = int(new_length)
        assert width == -1 or width == int(new_width)
        width = int(new_width)
    assert len(is_same_quality_function) == 1
    return association_names, lengths, width


def generate_csv_header(p_file_handlers, p_association_names, p_lengths, p_width):
    widths = '%i\n' % p_width
    for i in range(0, len(p_file_handlers)):
        widths += '%i\t' % p_lengths[i]
    names = ''
    for i in range(0, len(p_file_handlers)):
        names += '%s\t' % p_association_names[i]
    header = '%s\n%s' % (widths, names)
    for i in range(1, p_width):
        header += '\t%s' % names
    return header


def generate_csv(p_file_handlers, p_association_names, p_lengths, p_width, p_output_file):
    p_output_file.write("%s\n" % generate_csv_header(p_file_handlers, p_association_names, p_lengths, p_width))
    lines = {i: 0 for i in range(0, len(p_file_handlers))}
    max_lines = max(p_lengths.itervalues())
    for l in range(0, max_lines):
        output_lines = {i: '' for i in range(0, p_width)}
        for f in range(0, len(p_file_handlers)):
            if p_lengths[f] <= lines[f]:
                for p in range(0, p_width):
                    output_lines[p] += '\t'
            else:
                lines[f] += 1
                parts = p_file_handlers[f].readline().strip().split('\t')
                for p in range(0, p_width):
                    output_lines[p] += '%s\t' % parts[p]
        for p in range(0, p_width):
            p_output_file.write('%s\t' % output_lines[p])
        p_output_file.write('\n')


def main(p_output_file_path, p_file_with_input_files_path):
    with open(p_file_with_input_files_path, 'r') as f:
        file_handlers = open_files(f)
    association_names, lengths, width = gather_metadata(file_handlers)
    with open(p_output_file_path, 'w') as f:
        generate_csv(file_handlers, association_names, lengths, width, f)


"""
This script take N files as input (made with the same quality function)
and convert them into single csv file
"""
if __name__ == '__main__':
    required_argument_count = 2
    if len(sys.argv) == (required_argument_count + 1):
        main(sys.argv[1], sys.argv[2])
    else:
        print 'Error: required argument count: %i, passed: %i' % \
              (required_argument_count, (len(sys.argv) - 1))
