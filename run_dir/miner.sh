#!/bin/bash

if [ $# -ne 3 ]
  then
    printf "\nScript that runs program Miner to evaluate quality of given VAM. It takes 3 arguments: directory with tuples, file with VAM and length of k-best list.\n\nexample:\n \"./medium_all_3 vam1 100\"\n\n"

else

VAM=$(cat 'heuristic/'$2 | sed -n 1p)
AGGREGATOR=$(cat 'heuristic/'$2 | sed -n 2p)

mkdir -p results/$1

bin/Miner \
-I 'tuples/'$1 \
-O results/$1 \
-P n \
-r mwe/mwe.txt \
-F 3 \
-R 5 \
-e 0 \
-q "ap(length=$3)" \
-v $VAM \
-g $AGGREGATOR \
-w 1 \
-W 1000

cd results/$1
cp ../input input
cp ../cv_quality_results_merger.py cv.py
python cv.py aggregated_output input 5 3
rm input
rm cv.py

fi

