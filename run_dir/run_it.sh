#!/bin/bash


bin/TuplesBuilder \
-c corpusList.txt \
-t nkjp \
-r ccl \
-w wccl.ccl \
-o output/tuples


bin/Continger \
-i output/tuples \
-o contingency


bin/Indexer \
-i output/tuples \
-o index.csv
# -f 'every_word(^)'


bin/FeatureMaker \
-I output/tuples \
-O output/feat_results \
-f 'vam(wsc(), sfbmd(),me(),tscore(),g2(),jaccard(),sorgenfrei(),us(),sec(e=3.8),wsec(e=1.15),wo(),wtfo(),ct1(),ct2())' \
-p standarization \
-r mwe.txt \
-c output/tuples/contingency \
-P n \
-i output/tuples/index.csv
# -s 'every_word(^)' \


bin/Heuristic \
-I output/tuples \
-O output/heur_results \
-g output/tuples/index.csv \
-s output/tuples/contingency \
-c 'lc(method=HC,methods_config=config.ini,vam=vam(wsc(), sfbmd(),me(),tscore(),g2(),jaccard(),sorgenfrei(),us(),sec(e=3.8),wsec(e=1.15),wo(),wtfo(),ct1(),ct2()),aggregator=ms(0,0,0,0,0,0,0,0,0,0,0,0,0,0),quality_function=ap(length=100),quality_kbest_length=200,threads=8,min_value=-1.0,max_value=1.0,step_value=0.01)' \
-r mwe.txt


bin/Cover \
-I output/tuples \
-s cover_stats.txt \
-r cover_rel_set.txt \
-R mwe.txt


bin/Miner \
-I output/tuples \
-O output/mine_results \
-P n \
-r mwe.txt \
-q ap \
-a frequency


bin/Digger \
-I output/tuples \
-O output/dig_results \
-v 'vam(wsc(), sfbmd(),me(),tscore(),g2(),jaccard(),sorgenfrei(),us(),sec(e=3.8),wsec(e=1.15),wo(),wtfo(),ct1(),ct2())' \
-g 'ms(score=borda_score(),-0.38,-0.8,0.44,0.52,0.32,-0.5,0.84,0.96,0.72,0.12,0.02,0.36,0.24,-0.16)' \
-q 'hit(length=100)' \
-r mwe.txt \
-i output/tuples/index.csv \
-S output/tuples/contingency \
-P n \
-T nkjp \
-R ccl \
-W wccl.ccl \
-C corpusList.txt \
-k 100


bin/Judger \
-s output/tuples \
-l output/dig_results/0.kbest.csv \
-r mwe.txt \
-o output/judge_results \
-q ap


bin/WebTool \
-I corpusList.txt \
-T nkjp \
-R ccl \
-W wccl.ccl \
-K output/output.txt \
-k 50 \
-r 'vam(wsc(), sfbmd(),me(),tscore(),g2(),jaccard(),sorgenfrei(),us(),sec(e=3.8),wsec(e=1.15),wo(),wtfo(),ct1(),ct2())' \
-a 'max_sum(score=borda_score(),-0.38,-0.8,0.44,0.52,0.32,-0.5, 0.84,0.96,0.72,0.12,0.02,0.36,0.24,-0.16)'
#-r w_order \
#-r w_tf_order \
#-r expected_frequency \
#-r frequency \
#-r w_order \

