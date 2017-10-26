##########################################################################################################
# constants

tool='python /home/michalw/mgr/scripts/cv_quality_results_merger.py'
rounds='3'
folds='5'
file_with_paths_to_dirs=${1}

readarray -t paths < ${file_with_paths_to_dirs}

for value in ${paths[@]}
do
	find ${value} | grep quality | grep 0.csv | sort -t '.' -k 2 -n > "${value}/to_merge_list_0.txt"
	${tool} "${value}/merged_qualities_0.csv" "${value}/to_merge_list_0.txt" ${rounds} ${folds} &
done
