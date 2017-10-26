tool='/home/michalw/mgr/cmakebin/bin/TuplesBuilder'
output_dir_base='/home/michalw/dane/storage'

kipi='/home/michalw/dane/storage/kipi/kipi.crp'
kgr7='/home/michalw/dane/storage/kgr7/kgr7.crp' # no sjp corpus

relations_dir='/home/michalw/mgr/data/patterns'

w2r="${relations_dir}/2r.ccl"
w2rw="${relations_dir}/2rw.ccl"
w2r1h="${relations_dir}/2r1h.ccl"
w2rw1h="${relations_dir}/2rw1h.ccl"

w2rfix="${relations_dir}/2rfix.ccl"
w2rwfix="${relations_dir}/2rwfix.ccl"
w2r1hfix="${relations_dir}/2r1hfix.ccl"
w2rw1hfix="${relations_dir}/2rw1hfix.ccl"

w3r="${relations_dir}/3r.ccl"
w3rw="${relations_dir}/3rw.ccl"
w3r1h="${relations_dir}/3r1h.ccl"
w3rw1h="${relations_dir}/3rw1h.ccl"


relations[0]=${w2r}
relations[1]=${w2rw}
relations[2]=${w2r1h}
relations[3]=${w2rw1h}
relations[4]=${w2rfix}
relations[5]=${w2rwfix}
relations[6]=${w2r1hfix}
relations[7]=${w2rw1hfix}

#relations[8]=${w3r}
#relations[9]=${w3rw}
#relations[10]=${w3r1h}
#relations[11]=${w3rw1h}

corporas[0]=${kipi}
#corporas[1]=${kgr7}

for corpora in ${corporas[@]}
do
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
done
