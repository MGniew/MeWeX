##########################################################################################################
# constants
tool1='/home/michalw/mgr/cmakebin/bin/Indexer'
tool2='/home/michalw/mgr/cmakebin/bin/Normalizer'

input_dir_base='/home/michalw/dane/storage'

corpus='kipi_parts_20'

kipi_corporas=(
	'2r' '2r1h' '2w' '2w1h' '2rw' '2rw1h')

for crp in ${kipi_corporas[@]}
do
	crp_path="${input_dir_base}/${corpus}/${crp}"
	#${tool1} -i ${crp_path} -o index_all.csv
	out_crp_path="${input_dir_base}/${corpus}_tfidf/${crp}"
	mkdir -p ${out_crp_path}
	${tool2} -i ${crp_path} -o ${out_crp_path} -d "tfidf()"
done
