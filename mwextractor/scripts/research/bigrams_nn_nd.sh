# TODO: Schematy i wybor czestych relacji

##########################################################################################################
# constants
tool='/home/michalw/mgr/cmakebin/bin/Miner'
input_dir_base='/home/michalw/dane/storage'
relation_dir='/home/michalw/mgr/data/patterns/fixed_merged'

corpus="${input_dir_base}/kipi"
output_dir_base='/home/michalw/dane/results/kipi_nn_fix_standarization_nd'

##########################################################################################################
mkdir -p ${output_dir_base}

rounds='3'
folds='5'
threads='26'
fix_relevant_order='1'
write_kbests='0'
frequency=5

quality_functions='-q aprc()'
relevant_set="/home/michalw/mgr/data/units/MWE_2015_01_20.postlem.csv"
morfeusz='/home/michalw/dane/storage/morfeusz.csv'

# wsc: zamiennik pmi, nie bardzo...
# g2: zamienniek px2?
# orders dodane potem
features="-f vam(wsc(),me(),sfbmd(),tscore(),g2(),jaccard(),sorgenfrei(),us(),sec(e=3.8),wsec(e=1.15),"

nn_functions='
	-p standarization()
        -c mlp(12,5,2,1)
        -c mlp(12,6,2,1)
        -c mlp(12,7,2,1)
        -c mlp(12,8,2,1)
        -c mlp(12,9,2,1)
        -c mlp(12,10,2,1)
        -c mlp(12,11,2,1)
        -c mlp(12,12,2,1)
        -c mlp(12,13,2,1)
        -c mlp(12,14,2,1)
        -c mlp(12,15,2,1)
        -c mlp(12,16,2,1)
        -c mlp(12,5,2,1,learning_rate=0.1)
        -c mlp(12,6,2,1,learning_rate=0.1)
        -c mlp(12,7,2,1,learning_rate=0.1)
        -c mlp(12,8,2,1,learning_rate=0.1)
        -c mlp(12,9,2,1,learning_rate=0.1)
        -c mlp(12,10,2,1,learning_rate=0.1)
        -c mlp(12,11,2,1,learning_rate=0.1)
        -c mlp(12,12,2,1,learning_rate=0.1)
        -c mlp(12,13,2,1,learning_rate=0.1)
        -c mlp(12,14,2,1,learning_rate=0.1)
        -c mlp(12,15,2,1,learning_rate=0.1)
        -c mlp(12,16,2,1,learning_rate=0.1)
        -c mlp(12,5,3,1)
        -c mlp(12,6,3,1)
        -c mlp(12,7,3,1)
        -c mlp(12,8,3,1)
        -c mlp(12,9,3,1)
        -c mlp(12,10,3,1)
        -c mlp(12,11,3,1)
        -c mlp(12,12,3,1)
        -c mlp(12,13,3,1)
        -c mlp(12,14,3,1)
        -c mlp(12,15,3,1)
        -c mlp(12,16,3,1)
        -c mlp(12,5,3,1,learning_rate=0.1)
        -c mlp(12,6,3,1,learning_rate=0.1)
        -c mlp(12,7,3,1,learning_rate=0.1)
        -c mlp(12,8,3,1,learning_rate=0.1)
        -c mlp(12,9,3,1,learning_rate=0.1)
        -c mlp(12,10,3,1,learning_rate=0.1)
        -c mlp(12,11,3,1,learning_rate=0.1)
        -c mlp(12,12,3,1,learning_rate=0.1)
        -c mlp(12,13,3,1,learning_rate=0.1)
        -c mlp(12,14,3,1,learning_rate=0.1)
        -c mlp(12,15,3,1,learning_rate=0.1)
        -c mlp(12,16,3,1,learning_rate=0.1)'

# 48

bigram_functions="${nn_functions}"

command="${tool} -r ${relevant_set} ${quality_functions} -R ${rounds} -F ${folds} -T ${threads} -e ${fix_relevant_order} -w ${write_kbests} ${bigram_functions}"

OKNA='true'
RELACJE='true'
RELACJE_MORFEUSZ='true'
RELACJE_MORFEUSZ_CZESTOSC='true'

####################
# wzorzec:
# 	dlugosc_budowa_ekstrakcja_korpus
# przyklad: 
#	2_okno_okno_2r

if [ "${OKNA}" == true ]
then
	### OKNA ###
	echo 'Okna.'
	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno
  
	echo 'Okno # Okno' 
	crp='2w'
	stat="relation(^,file=${relation_dir}/2w.csv)"
	extr="relation(^,file=${relation_dir}/2w.csv)"
	out_dir="${output_dir_base}/2_okno_okno_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${lf}

	echo 'Okno, morfeusz # Okno'
	crp='2w'
	stat="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
 
	echo 'Okno, morfeusz, czestosc # Okno'
	crp='2w'
	stat="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
	
	echo 'Okno, dziura # Okno, dziura'
	crp='2w1h'
	stat="relation(^,file=${relation_dir}/2w1h.csv)"
	extr="relation(^,file=${relation_dir}/2w1h.csv)"
	out_dir="${output_dir_base}/2_oknoDziura_okno_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
 
	echo 'Okno, dziura, morfeusz # Okno, dziura'
	crp='2w1h'
	stat="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_oknoDziura_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
 
	echo 'Okno, dziura, morfeusz, czestosc # Okno, dziura'
	crp='2w1h'
	stat="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_oknoDziura_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	### Koniec okien ###
	echo 'Koniec okien.'
	echo ''
fi

if [ "${RELACJE}" == true ] 
then
	### ###
	echo 'Relacje...'

	echo 'Relacje # Relacje'
	crp='2r'
	stat="relation(^,file=${relation_dir}/2r.csv)"
	extr=${stat}
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, okno # Relacje'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/2rw.csv)"
	extr="relation(^,file=${relation_dir}/2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura # Relacje, dziura'
	crp='2r1h'
	stat="relation(^,file=${relation_dir}/2r1h.csv)"
	extr="relation(^,file=${relation_dir}/2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, okno # Relacje, dziura'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/2rw1h.csv)"
	extr="relation(^,file=${relation_dir}/2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}


	# wydobywanie tylko czestych
	################################
	echo 'Relacje # Relacje czeste'
	crp='2r'
	stat="relation(^,file=${relation_dir}/2r.csv)"
	extr="relation(^,file=${relation_dir}/f2r.csv)"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, okno # Relacje czeste'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/2rw.csv)"
	extr="relation(^,file=${relation_dir}/f2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
 
	echo 'Relacje, dziura # Relacje czeste, dziura'
	crp='2r1h'
	stat="relation(^,file=${relation_dir}/2r1h.csv)"
	extr="relation(^,file=${relation_dir}/f2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, okno # Relacje czeste, dziura'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/2rw1h.csv)"
	extr="relation(^,file=${relation_dir}/f2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
	
	### Koniec relacji ###
	echo 'Koniec relacji.'
fi

if [ "${RELACJE_MORFEUSZ}" == true ] 
then
	### ###
	echo 'Relacje, morfeusz...'

	echo 'Relacje, morfeusz # Relacje'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, okno, morfeusz # Relacje'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, morfeusz # Relacje, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, morfeusz, okno # Relacje, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	
	# wydobywanie tylko czestych
	################################
	echo 'Relacje, morfeusz # Relacje czeste'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, okno, morfeusz # Relacje czeste'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
 
	echo 'Relacje, dziura, morfeusz # Relacje czeste, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, okno, morfeusz # Relacje czeste, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
	
	### Koniec relacji ###
	echo 'Koniec relacji z morfeuszem.'
fi

if [ "${RELACJE_MORFEUSZ_CZESTOSC}" == true ] 
then
	### ###
	echo 'Relacje, morfeusz, czestosc ${frequency}...'

	echo 'Relacje, morfeusz, czestosc # Relacje'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, okno, morfeusz, czestosc # Relacje'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, morfeusz, czestosc # Relacje, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, morfeusz, okno, czestosc # Relacje, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	
	# wydobywanie tylko czestych
	################################
	echo 'Relacje, morfeusz, czestosc # Relacje czeste'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, okno, morfeusz, czestosc # Relacje czeste'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
 
	echo 'Relacje, dziura, morfeusz, czestosc # Relacje czeste, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}

	echo 'Relacje, dziura, okno, morfeusz, czestosc # Relacje czeste, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}),frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="w_order(scheme=${corpus}/${crp}/scheme.csv),w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	lf="${features}${order})"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order} ${lf}
	
	### Koniec relacji ###
	echo 'Koniec relacji z morfeuszem i czestoscia.'
fi
