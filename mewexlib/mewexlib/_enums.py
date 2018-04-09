# coding: utf8
from __future__ import absolute_import, division


import collections as coll
import enum
import os

import pkg_resources as pkgr


__all__ = (
    'RankerFunction',
    'DispersionFunction',
    'WCCLRelation',
    'ALL_WCCL_RELATIONS',
    'DEFAULT_WCCL_RELATIONS'
)


_MLP_MODEL_LOC = 'mewexlib', os.path.join('data', 'mlp_model.txt')
_RELATIONS_DIR = os.path.join('data', 'relations')

_FuncArgs = coll.namedtuple('_FuncArgs', ('main', 'other'))


def _fa(main, other=()):
    return _FuncArgs(main, other)


def _make_tuple(opt, func_en):
    return (opt, func_en.value.main) + func_en.value.other


class RankerFunction(enum.Enum):

    def to_args_tuple(self):
        return _make_tuple('-r', self)

    frequency = _fa('frequency()')

    pointwise_mutual_information = _fa('sc()')

    w_specific_correlation = _fa('wsc()')

    mutual_dependency = _fa('smd()')

    frequency_biased_mutual_dependency = _fa('sfbmd()')

    specific_exponential_correlation = _fa('sec(e=4.1)')

    w_specific_exponential_correlation = _fa('wsec(e=1.1)')

    mutual_expectation = _fa('me()')

    loglikelihood = _fa('g2()')

    pearsons_chi2 = _fa('px2()')

    w_pearsons_chi2 = _fa('wx2()')

    tscore = _fa('tscore()')

    zscore = _fa('zscore()')

    jaccard = _fa('jaccard()')

    dice = _fa('dice()')

    odds_ratio = _fa('or()')

    unigram_subtuples = _fa('us()')

    sorgenfrei = _fa('sorgenfrei()')

    consonni_t1 = _fa('ct1()')

    consonni_t2 = _fa('ct2()')

    expected_frequency = _fa('ef()')

    inversed_expected_frequency = _fa('ief()')

    w_order = _fa('wo()')

    w_term_frequency_order = _fa('wtfo()')

    vector_association_measure = _fa(
        'vam(tscore(),wtfo(),ct1(),jaccard(),cval(),dice(),us(),wsc(),wsec(e=3.8),me(),g2())',
        (
            '-a',
            'ms(0.206,0.076,0.139,0.209,0.002,0.021,0.104,0.127,0.007,0.027,0.037)',
        ),
    )

    multilayer_perceptron = _fa(
        'mlp(model={})'.format(pkgr.resource_filename(*_MLP_MODEL_LOC)),
        (
            '-f',
            'vam(wsc(),sfbmd(),me(),tscore(),g2(),jaccard(),sorgenfrei(),'
            'us(),sec(e=3.8),wsec(e=1.15),wo(),wtfo(),ct1(),ct2())',
            '-p',
            'normalization(-0.000113472,0.0172224,-63.3211,-6,1.76302e-14,'
            '0.00116278,-4857.71,387.906,-1.38093e-08,1.94893e+06,'
            '4.42166e-07,0.333333,1.33549e-28,0.25,-48.7993,13.3291,-83.7851,'
            '-15.3503,-0.000335203,0.0133202,1,6.83304e+33,1,1.65093e+38,'
            '-0.0497013,-3.98724e-08,0.170691,0.938039)',
        ),
    )


class DispersionFunction(enum.Enum):

    def to_args_tuple(self):
        return _make_tuple('-d', self)

    tf_idf = _fa('tfidf()')

    standard_deviation = _fa('sd()')

    variance_coefficient = _fa('vc()')

    juilland_d = _fa('jd()')

    distributional_consistency = _fa('dc()')

    lynes_d3 = _fa('ld3()')


class WCCLRelation(enum.Enum):

    def to_relation_filename(self):
        return pkgr.resource_filename(
            'mewexlib',
            os.path.join(_RELATIONS_DIR, self.value),
        )

    def to_args_tuple(self):
        return '-W', self.to_relation_filename()

    # RZECZOWNIK i PRZYMIOTNIK (uzgodnienie)
    agr_noun_adj = '2_2_agr_subst_adj.ccl'

    # BURKINOSTKA i RZECZOWNIK
    all_burk_noun = '2_4_all_burk_subst.ccl'

    # GERUNDIUM i KUBLIK
    all_ger_qub = '2_5_all_ger_qub.ccl'

    # IMIESŁÓW PRZYMIOTNIKOWY i PRZYSŁÓWEK
    all_adv_part = '2_3_all_adv_part.ccl'

    # COŚ i PRZYMIOTNIK w gen.
    sth_adjgen = '2_14_cos_adj_gen.ccl'

    # RZECZOWNIK i PRZYMIOTNIK f
    gndnoun_adj = '2_16_gnd_subst_adj.ccl'

    # RZECZOWNIK i RZECZOWNIK
    all_noun_noun = '2_13_all_subst_subst.ccl'

    # RZECZOWNIK i SIEBIE
    all_noun_self = '2_12_all_subst_siebie.ccl'

    # ZAIMEK 3. OS. w gen. i RZECZOWNIK
    ppron3gen_noun = '2_17_ppron_3_gen_subst.ccl'

    # LICZEBNIK i RZECZOWNIK
    all_num_noun = '2_6_all_num_subst.ccl'

    # DWA WYRAZY
    window = '2_19_window.ccl'

    # CZASOWNIK i RZECZOWNIK
    verb_noun = '2_20_verb_subst.ccl'

    # WYRAŻENIE PRZYIMKOWE
    bi_adv = '2_21_biadv.ccl'

    # PRZYMIOTNIK i RZECZOWNIK i PRZYMIOTNIK
    adj_noun_adj = '3_1100_adj_subst_adj.ccl'

    # CZASOWNIK i PRZYIMEK i RZECZOWNIK
    verb_prep_noun = '3_1101_verb_prep_subst.ccl'

    # PRZYMIOTNIK i RZECZOWNIK i RZECZOWNIK
    adj_noun_noun = '3_1102_adj_subst_subst.ccl'

    # RZECZOWNIK i PRZYIMEK i RZECZOWNIK
    noun_prep_noun = '3_1005_subst_prep_subst.ccl'

    # RZECZOWNIK i PRZYMIOTNIK (uzgodnienie + nieciągłość)
    agr_noun_adj_1h = '2_2_agr_subst_adj_1h.ccl'

    # BURKINOSTKA i RZECZOWNIK (nieciągłość)
    all_burk_noun_1h = '2_4_all_burk_subst_1h.ccl'

    # GERUNDIUM i KUBLIK (nieciągłość)
    all_ger_qub_1h = '2_5_all_ger_qub_1h.ccl'

    # IMIESŁÓW PRZYMIOTNIKOWY i PRZYSŁÓWEK (nieciągłość)
    all_adv_part_1h = '2_3_all_adv_part_1h.ccl'

    # COŚ i PRZYMIOTNIK w gen. (nieciągłość)
    sth_adjgen_1h = '2_14_cos_adj_gen_1h.ccl'

    # RZECZOWNIK i PRZYMIOTNIK f (nieciągłość)
    gndnoun_adj_1h = '2_16_gnd_subst_adj_1h.ccl'

    # RZECZOWNIK i RZECZOWNIK (nieciągłość)
    all_noun_noun_1h = '2_13_all_subst_subst_1h.ccl'

    # RZECZOWNIK i SIEBIE (nieciągłość)
    all_noun_self_1h = '2_12_all_subst_siebie_1h.ccl'

    # ZAIMEK 3. OS. w gen. i RZECZOWNIK (nieciągłość)
    ppron3gen_noun_1h = '2_17_ppron_3_gen_subst_1h.ccl'

    # LICZEBNIK i RZECZOWNIK (nieciągłość)
    all_num_noun_1h = '2_6_all_num_subst_1h.ccl'

    # DWA WYRAZY (nieciągłość)
    window_1h = '2_19_window_1h.ccl'

    # CZASOWNIK i RZECZOWNIK (nieciągłość)
    verb_noun_1h = '2_20_verb_subst_1h.ccl'

    # PRZYMIOTNIK i RZECZOWNIK i PRZYMIOTNIK (nieciągłość)
    adj_noun_adj_1h = '3_1100_adj_subst_adj_1h.ccl'

    # CZASOWNIK i PRZYIMEK i RZECZOWNIK (nieciągłość)
    verb_prep_noun_1h = '3_1101_verb_prep_subst_1h.ccl'

    # PRZYMIOTNIK i RZECZOWNIK i RZECZOWNIK (nieciągłość)
    adj_noun_noun_1h = '3_1102_adj_subst_subst_1h.ccl'

    # RZECZOWNIK i PRZYIMEK i RZECZOWNIK (nieciągłość)
    noun_prep_noun_1h = '3_1005_subst_prep_subst_1h.ccl'


DEFAULT_WCCL_RELATIONS = (
    WCCLRelation.agr_noun_adj,
    WCCLRelation.all_burk_noun,
    WCCLRelation.all_ger_qub,
    WCCLRelation.sth_adjgen,
    WCCLRelation.gndnoun_adj,
    WCCLRelation.all_noun_noun,
    WCCLRelation.all_noun_self,
    WCCLRelation.ppron3gen_noun,
    WCCLRelation.verb_noun,
    WCCLRelation.adj_noun_adj,
    WCCLRelation.verb_prep_noun,
    WCCLRelation.adj_noun_noun,
    WCCLRelation.noun_prep_noun
)

ALL_WCCL_RELATIONS = (
    WCCLRelation.agr_noun_adj,
    WCCLRelation.all_burk_noun,
    WCCLRelation.all_ger_qub,
    WCCLRelation.all_adv_part,
    WCCLRelation.sth_adjgen,
    WCCLRelation.gndnoun_adj,
    WCCLRelation.all_noun_noun,
    WCCLRelation.all_noun_self,
    WCCLRelation.ppron3gen_noun,
    WCCLRelation.all_num_noun,
    WCCLRelation.window,
    WCCLRelation.verb_noun,
    WCCLRelation.bi_adv,
    WCCLRelation.adj_noun_adj,
    WCCLRelation.verb_prep_noun,
    WCCLRelation.adj_noun_noun,
    WCCLRelation.noun_prep_noun,
    WCCLRelation.agr_noun_adj_1h,
    WCCLRelation.all_burk_noun_1h,
    WCCLRelation.all_ger_qub_1h,
    WCCLRelation.all_adv_part_1h,
    WCCLRelation.sth_adjgen_1h,
    WCCLRelation.gndnoun_adj_1h,
    WCCLRelation.all_noun_noun_1h,
    WCCLRelation.all_noun_self_1h,
    WCCLRelation.ppron3gen_noun_1h,
    WCCLRelation.all_num_noun_1h,
    WCCLRelation.window_1h,
    WCCLRelation.verb_noun_1h,
    WCCLRelation.adj_noun_adj_1h,
    WCCLRelation.verb_prep_noun_1h,
    WCCLRelation.adj_noun_noun_1h,
    WCCLRelation.noun_prep_noun_1h
)
