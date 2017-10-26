##########################################################################################################
# constants
tool='/home/michalw/mgr/cmakebin/bin/Cover'

input_dir_base='/home/michalw/dane/storage'
relevant_set="/home/michalw/mgr/data/units/WN_2014_10_20_ling_2014_11.csv"

corpus='kipi'

relations[0]="${relations_dir}/2rw1h.ccl"
relations[1]="${relations_dir}/2rw.ccl"

relations[2]="${relations_dir}/2w1h.ccl"
relations[3]="${relations_dir}/2w.ccl"

relations[4]="${relations_dir}/2r1h.ccl"
relations[5]="${relations_dir}/2r.ccl"

####################
# cel:
#	+ obliczenie statystyk pokrycia wzorców
kipi_corporas=(
	'2r' '2r1h' '2w' '2w1h' '2rw' '2rw1h')

for crp in ${kipi_corporas[@]}
do
	crp_path="${input_dir_base}/${corpus}/${crp}"
	${tool} -I ${crp_path} -s statistics_flex.csv -r relevant_units_flex.csv -R ${relevant_set} -e 0
	${tool} -I ${crp_path} -s statistics_fix.csv -r relevant_units_fix.csv -R ${relevant_set} -e 1
done
