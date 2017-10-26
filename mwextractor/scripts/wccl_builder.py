#!/usr/bin/env python
# -*- coding: utf-8 -*-


__author__ = 'michalw'

import sys


class WcclBuilder(object):

    @staticmethod
    def parse_line(p_parts_of_speech_string):
        parts = []
        comment = ''
        is_comment = False
        current = ''
        for p in ' '.join(p_parts_of_speech_string.split()).split():
            if p.startswith('//') or p.startswith('(') or is_comment:
                if p.startswith('('):
                    comment += '//'
                comment += '%s ' % p
                is_comment = True
                continue
            elif p.startswith('{') or len(current) > 0:
                current += p.strip()
                if not p.endswith('}'):
                    continue
            else:
                current = p
            parts.append(current)
            current = ''
        return (parts, comment)

    @staticmethod
    def generate_wccl_header(p_parts):
        header = ''
        for p in p_parts:
            if p.startswith('{'):
                end = p.find(',')
                if end == -1:
                    end = p.rfind('}')
                header_part = p[1].upper() + p[2:end]
            else:
                header_part = p[0].upper() + p[1:]
            header += header_part
        return '@b:\"%s_%i\"' % (header, len(p_parts))

    @staticmethod
    def body_builder(p_parts):
        content = ''
        idx = 0
        for p in p_parts:
            content += '\t\tinter(class[%i], %s),\n' % (idx, p)
            idx += 1
        for p in range(0, len(p_parts)):
            content += '\t\tsetvar($Pos%i, %i)%s' % (p + 1, p, ',\n' if p < len(p_parts) - 1 else '')
        body = '\tand(\n%s\n\t)' % content
        return '(\n%s\n)' % body

    @staticmethod
    def build_wccl(p_parts_of_speech):
        parts, comment = WcclBuilder.parse_line(p_parts_of_speech)
        header = WcclBuilder.generate_wccl_header(parts)
        body = WcclBuilder.body_builder(parts)
        return '%s\n%s%s' % (comment, header, body)


def main(p_file_with_operators, p_output_file):
    with open(p_output_file, 'w') as out:
        with open(p_file_with_operators, "r") as f:
            for line in [line.strip() for line in f if len(line.strip()) > 0]:
                out.write('%s%s' % (WcclBuilder.build_wccl(line), '\n\n'))


"""
This script convert part of speech combinations into simple wccl_operators

Example input file:
subst adj
adj subst adj
...

Output:
Single file with simple wccl operators

usage: script.py input_file output_file
"""
if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
