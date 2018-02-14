#!/bin/bash

if [ $# -le 3 ]
  then
    printf "\nScript that runs program Heuristic to tune vector of weigths for association measure aggregator. First argument is name od directory with tuples, second length o k-best list and rest are listed association measures which have to be used for training.\n\nexample:\n\"./heurPSO.sh medium_all_3 100 tscore zscore ct1 jaccard cval dice\"\n\n"

else

TUPLES='tuples/'$1
AGGREGATOR='ms('
VAM='vam('

for var in "${@:3}"
do
VAM+=$var'(),'
AGGREGATOR+='0,'
done

VAM=${VAM::-1}')'
AGGREGATOR=${AGGREGATOR::-1}')'

LC="lc(method=PSO,methods_config=config.ini,vam=$VAM,aggregator=$AGGREGATOR,quality_function=ap(length=$2),quality_kbest_length=$2,threads=6,min_value=-1.0,max_value=1.0,step_value=0.01)"

bin/Heuristic \
-I $TUPLES \
-O heuristic/$1'_'$2'_weigths' \
-g $TUPLES/index.csv \
-s $TUPLES/contingency \
-c $LC \
-r mwe/mwe.txt

echo $VAM > heuristic/$1'_'$2'_report'  
sed -n '7~1s/[^[]*\(\[[^]]*]\)./\1,/gp' report_file >> heuristic/$1'_'$2'_report'

rm report_file

fi

