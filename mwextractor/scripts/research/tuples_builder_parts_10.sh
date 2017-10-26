tool='/home/michalw/mgr/cmakebin/bin/TuplesBuilder'
output_dir_base='/home/michalw/dane/storage'

kipi_parts='/home/michalw/dane/storage/kipi_parts_10/kipi_parts_10.crp'
kgr7_parts='/home/michalw/dane/storage/kgr7_parts_10/kgr7_parts_10.crp' # no sjp corpus

relations_dir='/home/michalw/mgr/data/patterns/fixed_merged'

relations[0]="${relations_dir}/2rw1h.ccl"
relations[1]="${relations_dir}/2rw.ccl"

relations[2]="${relations_dir}/2w1h.ccl"
relations[3]="${relations_dir}/2w.ccl"

relations[4]="${relations_dir}/2r1h.ccl"
relations[5]="${relations_dir}/2r.ccl"

corpora=${kipi_parts}
#corpora=${kgr7}

for relation in ${relations[@]}
do
	crp=${corpora##*/}
	crp=${crp%.crp}
	rel=${relation##*/}
	rel=${rel%.ccl}
	output_dir="${output_dir_base}/${crp}/${rel}/"
	mkdir -p ${output_dir}
	echo "building '${output_dir}'."
	${tool} -c ${corpora} -w ${relation} -t nkjp -r iob-chan -o ${output_dir}
done
