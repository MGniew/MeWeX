#!/usr/bin/env python
# -*- coding: utf-8 -*-


# Format wejścia
"""
w_specific_exponential_correlation(e=1.25)
29788656
0.001814007558027857    AllSubstSubst   2       subst:wzgląd    subst:ludność   33754 względem ludności 21 względem ludność     3 względzie ludności    3 względy ludności      1 względów ludności     1 względu ludności      1 względem ludnością
0.001499475928643016    GndSubstAdj     2       subst:sojusz    adj:demokratyczny       22331 Sojuszu Demokratycznej    35 Sojuszowi Demokratycznej     2 sojuszu Demokratycznej        1 sojuszu demokratycznej        1 Sojusz demokratyczna  1 SOJUSZU DEMOKRATYCZNEJ
"""

# wyjście
"""
'punktacja' 'relacja' 'szyk (ułożenie lematów względem ocenionwego szyku)' 'AB' 'BA' 'orth_1' 'orth_2' ...
"""

import argparse


class Orth(object):
    def __init__(self, p_line):
        self.frequency = 0
        self.word_array = []
        if not p_line == '':
            self.build(p_line)

    def build(self, p_line):
        parts = p_line.split(' ')
        self.frequency = int(parts[0])
        self.word_array = parts[1:]

    def check_linkage(self, p_word_array):
        """
        check self.word_array linkage with p_word_array and returns index array
        returns [orth_idx_1, orth_idx_2] -> this_array[input_array_idx] = orth_idx
        """
        assert len(p_word_array) == len(self.word_array)
        word_count = len(p_word_array)
        result = []
        for i in range(0, word_count):
            result.append(-1)
        # for each word from input array
        for input_idx in range(0, word_count):
            # find best fitted word from inner array
            current_best_score = 1337
            for inner_idx in range(0, word_count):
                score = self.score_linkage(p_word_array[input_idx], self.word_array[inner_idx])
                if score < current_best_score:
                    result[input_idx] = inner_idx
                    current_best_score = score
        """
        for i in range(0, len(result)):
            print p_word_array[i], ' to ', self.word_array[result[i]],
        print ''
        """
        return result

    def score_linkage(self, p_word_1, p_word_2):
        return self.levenshtein(p_word_1.lower(), p_word_2.lower())

    def levenshtein(self, p_word_1, p_word_2):
        if len(p_word_1) < len(p_word_2):
            return self.levenshtein(p_word_2, p_word_1)

        # len(s1) >= len(s2)
        if len(p_word_2) == 0:
            return len(p_word_1)

        previous_row = range(len(p_word_2) + 1)
        for i, c1 in enumerate(p_word_1):
            current_row = [i + 1]
            for j, c2 in enumerate(p_word_2):
                insertions = previous_row[j + 1] + 1    # j+1 instead of j since previous_row and current_row are one character longer
                deletions = current_row[j] + 1          # than s2
                substitutions = previous_row[j] + (c1 != c2)
                current_row.append(min(insertions, deletions, substitutions))
            previous_row = current_row

        return previous_row[-1]

    def __str__(self):
        result = '%d' % self.frequency
        for word in self.word_array:
            result += ' %s' % word
        return result

    def __repr__(self):
        return str(self)


class Line(object):
    _big_polish_letters = set('AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ'.decode('utf8'))

    def __init__(self, p_line=''):
        self.frequency = 0
        self.score = ''
        self.relation_name = ''
        self.relation_size = 0
        self.pos_array = []
        self.lemma_array = []
        self.orth_array = []
        self.linkage = []
        self.L1L2_frequency = 0
        self.L2L1_frequency = 0
        self.proper_name_value = 0.0   # [0:1]
        if not p_line == '':
            self.build(p_line)

    def build(self, p_line):
        parts = p_line.split('\t')
        self.score = parts[0]
        self.relation_name = parts[1]
        self.relation_size = int(parts[2])
        self.pos_array = [pos_lemma.split(':')[0] for pos_lemma in parts[3:3 + self.relation_size]]
        self.lemma_array = [pos_lemma.split(':')[1] for pos_lemma in parts[3:3 + self.relation_size]]
        self.orth_array = [Orth(orth_line) for orth_line in parts[3 + self.relation_size:]]
        self.frequency = sum(orth.frequency for orth in self.orth_array)

    def initialize(self):
        self.link()
        self.sum_order_frequencies()
        self.compute_proper_name_value()

    def link(self):
        """
        links orth with base using list
        this_array[orth_idx]=array[base_idx]=orth_idx
        """
        self.linkage = [orth.check_linkage(self.lemma_array) for orth in self.orth_array]

    def sum_order_frequencies(self):
        """
        return frequencies of lemma
        """
        self.L1L2_frequency = 0
        self.L2L1_frequency = 0
        for idx, link in enumerate(self.linkage):
            freq = self.orth_array[idx].frequency
            if link[0] == 0:
                self.L1L2_frequency += freq
            else:
                self.L2L1_frequency += freq

    def compute_proper_name_value(self):
        self.proper_name_value = self.compute_proper_name_value_for_array(self.orth_array)

    @staticmethod
    def compute_proper_name_value_for_array(p_orth_array):
        second_lemma_first_letter_is_upper = 0
        frequency = 0
        for orth in p_orth_array:
            second_lemma_first_letter = orth.word_array[1][0]
            if second_lemma_first_letter in Line._big_polish_letters:
                second_lemma_first_letter_is_upper += orth.frequency
            frequency += orth.frequency
        return float(second_lemma_first_letter_is_upper) / float(frequency)

    def pos_lemma_set(self):
        return set(['%s:%s' % (self.pos_array[i], self.lemma_array[i]) for i in range(0, self.relation_size)])

    def tuple_string(self):
        """
        returns tuple
        """
        result = ''
        for i in range(0, self.relation_size):
            result += '%s:%s' % (self.pos_array[i], self.lemma_array[i])
            if i + 1 < self.relation_size:
                result += ' '
        return result

    def tuple_string_with_order(self):
        """
        works in general only if L1L2 > L2L1, else only for 2-elements
        """
        if self.L1L2_frequency >= self.L2L1_frequency:
            return self.tuple_string()
        return '%s:%s %s:%s' % (self.pos_array[1], self.lemma_array[1], self.pos_array[0], self.lemma_array[0])

    def get_ab_frequency(self):
        return max(self.L1L2_frequency, self.L2L1_frequency)

    def get_ba_frequency(self):
        return min(self.L1L2_frequency, self.L2L1_frequency)

    def as_line(self):
        """
        returns string in input format
        """
        result = '%s\t%s\t%d' % (self.score, self.relation_name, self.relation_size)
        for i in range(0, self.relation_size):
            result += '\t%s:%s' % (self.pos_array[i], self.lemma_array[i])
        for orth in self.orth_array:
            result += '\t%s' % str(orth)
        return result

    def __str__(self):
        return self.as_line()


def write_line(p_processed_line, p_output_file):
    p_output_file.write('%s\t%s\t%s\t%d\t%d\t%d' % (
        p_processed_line.score,
        '%s_%d' % (p_processed_line.relation_name, p_processed_line.relation_size),
        p_processed_line.tuple_string_with_order(),
        p_processed_line.frequency,
        p_processed_line.get_ab_frequency(),
        p_processed_line.get_ba_frequency()
    ))
    for orth in p_processed_line.orth_array:
        p_output_file.write('\t%s' % str(orth))
    p_output_file.write('\n')


def per_relation(p_input_file, p_threshold, p_output_file, p_output_file_proper, p_output_file_problematic):
    p_output_file.write(p_input_file.readline())
    p_output_file.write(p_input_file.readline())
    p_output_file.write('punktacja\trelacja\tszyk, lematy\tczęstość\tAB\tBA\tformy napotkane...\n')
    for line in p_input_file:
        try:
            the_line = Line(line.strip())
            the_line.initialize()
            if the_line.proper_name_value < p_threshold:
                write_line(the_line, p_output_file)
            else:
                p_output_file_proper.write('%s\n' % str(the_line))
        except Exception as e:
            p_output_file_problematic.write('%s\n' % str(line))


def parse_lines(p_input_file, p_output_file_problematic):
    mapped_lines = {}
    p_input_file.readline()  # header
    p_input_file.readline()
    for line in p_input_file:
        try:
            parsed_line = Line(line.strip())
            key = frozenset(parsed_line.pos_lemma_set())
            if key not in mapped_lines:
                mapped_lines[key] = []
            mapped_lines[key].append(parsed_line)
        except Exception as e:
            p_output_file_problematic.write('%s\n' % str(line))
    return mapped_lines


def merge_mapped_lines(p_mapped_lines):
    merged_lines = []   # line
    for key, the_list in p_mapped_lines.iteritems():
        ab_sg = 0
        ba_sg = 0
        a_b_sg = 0
        b_a_sg = 0
        ab_pl = 0
        ba_pl = 0
        a_b_pl = 0
        b_a_pl = 0
        score = None
        tuple_string = None
        orth_array = []  # orth
        for parsed_line in the_list:
            if score is None:
                score = float(parsed_line.score)
		lemma_arr = (parsed_line.lemma_array[0], parsed_line.lemma_array[1]) if parsed_line.pos_array[0] == 'subst' else (parsed_line.lemma_array[1], parsed_line.lemma_array[0])
                tuple_string = 'subst:%s adj:%s' % lemma_arr
            with_hole = 'Hole' in parsed_line.relation_name
            subst_adj_order = parsed_line.relation_name.find('Subst') < parsed_line.relation_name.find('Adj')
            singular = parsed_line.relation_name.endswith('Sg')
            if singular:
                if not with_hole and subst_adj_order:
                    ab_sg += parsed_line.frequency
                elif not with_hole and not subst_adj_order:
                    ba_sg += parsed_line.frequency
                elif with_hole and subst_adj_order:
                    a_b_sg += parsed_line.frequency
                elif with_hole and not subst_adj_order:
                    b_a_sg += parsed_line.frequency
            else:
                if not with_hole and subst_adj_order:
                    ab_pl += parsed_line.frequency
                elif not with_hole and not subst_adj_order:
                    ba_pl += parsed_line.frequency
                elif with_hole and subst_adj_order:
                    a_b_pl += parsed_line.frequency
                elif with_hole and not subst_adj_order:
                    b_a_pl += parsed_line.frequency
            for orth in parsed_line.orth_array:
                orth_array.append(orth)
        freq_sum = sum([ab_sg, ba_sg, a_b_sg, b_a_sg, ab_pl, ba_pl, a_b_pl, b_a_pl])
	div = float(freq_sum) / 100.0
        new_line = (score,
                    '%s\t%d\t%d (%f%%)\t%d (%f%%)\t%d (%f%%)\t%d (%f%%)\t%d (%f%%)\t%d (%f%%)\t%d (%f%%)\t%d (%f%%)' % (tuple_string, freq_sum, ab_sg, float(ab_sg)/div, ba_sg, float(ba_sg)/div, a_b_sg, float(a_b_sg)/div, b_a_sg, float(b_a_sg)/div, ab_pl, float(ab_pl)/div, ba_pl, float(ba_pl)/div, a_b_pl, float(a_b_pl)/div, b_a_pl, float(b_a_pl)/div),
                    sorted(orth_array, key=lambda orth: orth.frequency, reverse=True))
        merged_lines.append(new_line)
    return sorted(merged_lines, key=lambda line: line[0], reverse=True)


def merge_relations(p_input_file, p_threshold, p_output_file, p_output_file_proper, p_output_file_problematic):
    merged_lines = merge_mapped_lines(parse_lines(p_input_file, p_output_file_problematic))
    p_output_file.write('punktacja\tkrotka\tsuma wystapien\tab sg\tba sg\ta_b sg\tb_a sg\tab pl\tba pl\ta_b pl\tb_a pl\tformy napotkane...\n')
    for score, line, orth_array in merged_lines:
        orth_string = ''
        for orth in orth_array:
            orth_string += '\t%s' % str(orth)
        if Line.compute_proper_name_value_for_array(orth_array) >= p_threshold:
            p_output_file_proper.write('%f\t%s\t%s\n' % (score, line, orth_string))
        else:
            p_output_file.write('%f\t%s\t%s\n' % (score, line, orth_string))


def main(p_argv):
    threshold = p_argv.cap_thres
    with open(p_argv.list, 'r') as input_file:
        with open(p_argv.output, 'w') as output_file:
            with open('%s.proper_names' % p_argv.output, 'w') as output_file_proper_names:
                with open('%s.problematic' % p_argv.output, 'w') as output_file_problematic:
                    #per_relation(input_file, threshold, output_file, output_file_proper_names, output_file_problematic)
                    merge_relations(input_file, threshold, output_file, output_file_proper_names, output_file_problematic)


def print_error(p_exception, p_line):
    print 'Error: \'%s\', line: \'%s\'' % (p_exception.message, p_line)


if __name__ == '__main__':
    argp = argparse.ArgumentParser()
    argp.add_argument('list')
    argp.add_argument('output')
    argp.add_argument('-c', '--capital-letters-threshold',
        type=float, default=0.8, dest='cap_thres')

    main(argp.parse_args())
