#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Skrypt zbiera wyniki zapisane w kilku plikach wynikowych programu
# Miner i generuje z nich jeden plik.
# Każdy plik wejściowy musiał być utworzony za pomocą takiej samej
# funkcji oceny.

import sys


def open_files(p_file_with_input_files):
    file_handlers = {}  # index : file_handler
    for file_path in p_file_with_input_files:
        file_handlers[len(file_handlers)] = open(file_path.strip(), 'r')
    return file_handlers


def gather_metadata(p_files, p_round_count, p_fold_count):
    is_same_quality_function = set()
    association_names = {}
    fold_sizes = {}
    lengths = {}
    width = -1
    fold_sum = p_round_count * p_fold_count
    for index, file_handler in p_files.iteritems():
        parts = file_handler.readline().strip().split('\t')
        association_names[index] = parts[2]
        if fold_sum > 0:
            fold_sum -= 1
            fold_sizes[len(fold_sizes)] = (int(parts[0]), int(parts[1]))
        is_same_quality_function.add(file_handler.readline().strip())
        new_length, new_width = file_handler.readline().strip().split('\t')
        lengths[index] = int(new_length)
        assert width == -1 or width == int(new_width)
        width = int(new_width)
    assert len(is_same_quality_function) == 1
    return association_names, fold_sizes, lengths, width


def generate_csv_header(p_file_handlers, p_association_names, p_fold_sizes, p_lengths, p_width, p_round_count, p_fold_count):
    merge_count = p_round_count * p_fold_count
    widths = '%i\n' % p_width
    for i in range(0, len(p_file_handlers) / merge_count):
        widths += '%i\t' % p_lengths[i * merge_count]
    names = ''
    for i in range(0, len(p_file_handlers) / merge_count):
        names += '%s\t' % p_association_names[i * merge_count]
    fold_sizes = ''
    for index, values in p_fold_sizes.iteritems():
        fold_sizes += '%d\t%d\n' % values
    header = 'rounds: %i, folds: %i.\n%s%s\n%s' % (p_round_count, p_fold_count, fold_sizes, widths, names)
    for i in range(1, p_width):
        header += '\t%s' % names
    return header


def generate_csv(p_file_handlers, p_association_names, p_fold_sizes, p_lengths, p_width, p_output_file, p_round_count, p_fold_count):
    p_output_file.write("%s\n" % generate_csv_header(p_file_handlers, p_association_names, p_fold_sizes, p_lengths, p_width, p_round_count, p_fold_count))
    lines = {i: 0 for i in range(0, len(p_file_handlers))}
    max_lines = max(p_lengths.itervalues())
    merge_count = p_round_count * p_fold_count
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
            values = output_lines[p].split('\t')
            for m in range(0, len(p_file_handlers) / merge_count):
                sum = 0.0
                for x in range(0, merge_count):
                    try:
                        sum += float(values[x + m * merge_count])
                    except Exception as e:
                        pass
                        #print e
                p_output_file.write('%s\t' % str(sum / merge_count).replace('.', ','))
            p_output_file.write('\t')
        p_output_file.write('\n')


def main(p_output_file_path, p_file_with_input_files_path, p_round_count, p_fold_count):
    with open(p_file_with_input_files_path, 'r') as f:
        file_handlers = open_files(f)
    association_names, fold_sizes, lengths, width = gather_metadata(file_handlers, p_round_count, p_fold_count)
    with open(p_output_file_path, 'w') as f:
        generate_csv(file_handlers, association_names, fold_sizes, lengths, width, f, p_round_count, p_fold_count)


"""
This script take N files as input (made with the same quality function)
and convert them into single csv file
"""
if __name__ == '__main__':
    required_argument_count = 4
    if len(sys.argv) == (required_argument_count + 1):
        main(sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4]))
    else:
        print 'Error: required argument count: %i, passed: %i' % \
              (required_argument_count, (len(sys.argv) - 1))
