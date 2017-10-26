##########################################################################################################
# constants
tool='/home/michalw/mgr/cmakebin/bin/Reductor'

input_dir_base='/home/michalw/dane/storage'
relevant_set="/home/michalw/mgr/data/units/WN_2014_10_20_ling_2014_11.csv"

corpus='kipi'
kipi_corporas=(
	'2r' '2r1h' '2w' '2w1h' '2rw' '2rw1h')

morfeusz='every_word(^,file=/home/michalw/dane/storage/morfeusz.csv)'
morfeusz_freq_5="and(${morfeusz},frequency(>,5))"

ratio=5
value=0.05

for crp in ${kipi_corporas[@]}
do
	crp_path="${input_dir_base}/${corpus}/${crp}"

	output_path="${input_dir_base}/${corpus}_sub${ratio}/${crp}"
	mkdir -p ${output_path}
	${tool} -i ${crp_path} -o ${output_path} -e 1 -r ${relevant_set} -p ${value}
	
	output_path="${input_dir_base}/${corpus}_sub${ratio}/${crp}_morfeusz"
	mkdir -p ${output_path}
	${tool} -i ${crp_path} -o ${output_path} -e 1 -r ${relevant_set} -p ${value} -f ${morfeusz}
	
	output_path="${input_dir_base}/${corpus}_sub${ratio}/${crp}_morfeuszFreq5"
	mkdir -p ${output_path}
	${tool} -i ${crp_path} -o ${output_path} -e 1 -r ${relevant_set} -p ${value} -f ${morfeusz_freq_5}
done
