tool='/home/michalw/mgr/cmakebin/bin/TuplesBuilder'
output_dir_base='/home/michalw/dane/storage'

kipi='/home/michalw/dane/storage/kipi/kipi.crp'
kgr7='/home/michalw/dane/storage/kgr7/kgr7.crp' # no sjp corpus

relations_dir='/home/michalw/mgr/data/patterns/fixed_merged'

relations[0]="${relations_dir}/2rw1h.ccl"
relations[1]="${relations_dir}/2rw.ccl"

relations[2]="${relations_dir}/2w1h.ccl"
relations[3]="${relations_dir}/2w.ccl"

relations[4]="${relations_dir}/2r1h.ccl"
relations[5]="${relations_dir}/2r.ccl"

corpora=${kipi}
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
