#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Skrypt ma za zadanie ekstrachować wyniki programu
# optimizer autorstwa Łukasza Kłyka (folder mwextractor/optimizer/).


import sys


def parse_individual(p_line):
    end = p_line.rfind(']')
    start = p_line.rfind('=', 0, end)
    return float(p_line[start + 1:end])


def parse_population_number(p_line):
    return int(p_line[0:p_line.rfind(':')])


def parse_population_size(p_line):
    return int(p_line[p_line.find('e=') + 2:p_line.find(',')])


def parse(p_input_files, p_output_file):
    for f in p_input_files:
        p_output_file.write('%s\t\t\t\t\t\t' % f.name)
    p_output_file.write('\n')
    for f in p_input_files:
        p_output_file.write('population nr\tbest_global\tbest\taverage\tworst\t\t')
    p_output_file.write('\n')
    for f in p_input_files:
        f.readline()
        f.readline()
        f.readline()
        f.readline()
        f.readline()
    done = False
    while not done:
        for f in p_input_files:
            line = f.readline()
            if line.startswith('-'):
                done = True
                break
            # header
            population_nr = parse_population_number(line)
            best_global = parse_individual(f.readline())
            population_size = parse_population_size(f.readline())
            best = parse_individual(f.readline())
            worst = parse_individual(f.readline())
            # individuals
            f.readline()  # read 'Individuals='
            individuals = [parse_individual(f.readline()) for i in range(0, population_size)]
            # write result
            avg = sum(individuals) / population_size
            p_output_file.write('%i\t%f\t%f\t%f\t%f\t\t' % (population_nr, best_global, best, avg, worst))
            f.readline()  # read ']'
        p_output_file.write('\n')


def main(p_file_path_with_input_file_paths, p_output_file_path):
    with open(p_file_path_with_input_file_paths) as f:
        files = [open(path.strip(), 'r') for path in f]
    with open(p_output_file_path, 'w') as output_file:
        parse(files, output_file)
    for f in files:
        f.close()


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
