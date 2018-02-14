#!/bin/bash

if [ $# -ne 3 ]
  then
    printf "\nScript that runs programs TuplesBuilder, Continger, Indexer and Cover to generate data needed for further processing of MWE. It takes 3 arguments: file with corpora, file with relations and value X used for tuple filter frequency(>,X).\n\nexample:\n \"./generate_tuples.sh nkjp all 5\"\n\n"

else

CORPORA=$1
RELATIONS=$2
FILTER=$3
OUTPUT=$CORPORA'_'$RELATIONS'_'$FILTER
FILTER_STR='frequency(>,'$FILTER')'

mkdir -p tuples/$OUTPUT


bin/TuplesBuilder \
-c corpora/$CORPORA.txt \
-t nkjp \
-r ccl \
-w relations/$RELATIONS.ccl \
-o tuples/$OUTPUT


bin/Continger \
-i tuples/$OUTPUT \
-o contingency \
-f $FILTER_STR


bin/Indexer \
-i tuples/$OUTPUT \
-o index.csv \
-f $FILTER_STR


bin/Cover \
-I tuples/$OUTPUT \
-s cover_stats.csv \
-r cover_rel_set.txt \
-R mwe/mwe.txt

fi
