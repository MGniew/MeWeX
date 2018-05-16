#!/usr/bin/python3
import os
import re
import io


import mewexlib as mwl
import WrapLem
from nlp_ws import NLPWorker, NLPService


class MewexWorker(NLPWorker):
    def init(self):
        self._lemmatizer = WrapLem.CascadeLemmatizer.assembleLemmatizer()

    def process(self, input_path, task_options, output_path):
        args = _parse_mewex_options(task_options.get('mewex_options') or {})
        args['input_files'] = (
            [os.path.join(input_path, f) for f in os.listdir(input_path)]
            if os.path.isdir(input_path)
            else (input_path,)
        )
        if not os.path.exists(output_path):
            os.makedirs(output_path)
        args['output_file'] = output_path+"/mewex.csv"

        mwl.call_mewex(**args)
        self.lemmatize(output_path+"/mewex.csv",output_path+"/mewexlemmatized.csv")
        self.cut_lines(output_path+"/mewexlemmatized.csv",output_path+"/mewexshort.csv",1000)

    def cut_lines(self,inf,outf,lines):
        f = open(inf, "r")
        copy = open(outf, "w")
        n = 0
        for line in f:
            copy.write(line)
            n = n + 1
            if n > lines:
                break
        f.close()
        copy.close()

    def lemmatize(self, inf, outf):
        input_file = io.open(inf, "r", encoding="utf-8")
        output_file = open(outf, "w")
        next(input_file); next(input_file) # First two rows are header rows, so just skip them
        output_file.write("Rank\tQuantity\tRealtion\tBase form\tLemmatized form\tAll forms\n")
        orthreg = re.compile(r'[0-9]+:([^(]+)\(([^)]+)\).*')
        basereg = re.compile(r'[^:]+:([^ ]+)')
        for line in input_file:
            splited = line.strip().split('\t')
            orthtuple = orthreg.findall(splited[4])
            baselist = basereg.findall(splited[3])
            base = u' '.join(baselist)
            orth = orthtuple[0][0].strip()
            tag = orthtuple[0][1]
            result = self._lemmatizer.lemmatizeS(orth, base, tag, False)
            splited.insert(4,result)
            output_file.write('\t'.join(splited) + '\n')
        input_file.close()
        output_file.close()


_OPT_DISPATCH = dict(
    ranker_func=lambda val: mwl.RankerFunction[val],
    dispersion_func=lambda val: mwl.DispersionFunction[val],
    wccl_rels=lambda val: frozenset(mwl.WCCLRelation[el] for el in val),
)


def _parse_mewex_options(opts):
    args = {}

    while opts:
        key, val = opts.popitem()

        if key in _OPT_DISPATCH:
            val = _OPT_DISPATCH[key](val)

        args[key] = val

    return args


if __name__ == '__main__':
    NLPService.main(MewexWorker, pause_at_exit=True)
