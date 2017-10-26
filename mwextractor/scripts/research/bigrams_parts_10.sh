# TODO: Schematy i wybor czestych relacji

##########################################################################################################
# constants
tool='/home/michalw/mgr/cmakebin/bin/Miner'
input_dir_base='/home/michalw/dane/storage'
relation_dir='/home/michalw/mgr/data/patterns/fixed_merged'

corpus="${input_dir_base}/kipi_parts_10_tfidf"
output_dir_base='/home/michalw/dane/results/kipi_parts_10_tfidf'

##########################################################################################################
mkdir -p ${output_dir_base}

rounds='3'
folds='5'
threads='24'
fix_relevant_order='1'
write_kbests='0'

quality_functions='-q aprc() -q apoh()'
relevant_set="/home/michalw/mgr/data/units/WN_2014_10_20_ling_2014_11.csv"
morfeusz='/home/michalw/dane/storage/morfeusz.csv'
frequency='5'

non_param_bigram_functions="-a frequency() -a ef() -a ief() -a jaccard() -a dice() -a sorgenfrei() -a or() -a us() -a ct1() -a ct2() -a me() -a sc() -a wsc() -a smd() -a sfbmd() -a tscore() -a zscore() -a px2() -a wx2() -a g2()"

sec_function="-a sec(e=3.1) -a sec(e=3.2) -a sec(e=3.3) -a sec(e=3.4) -a sec(e=3.5) -a sec(e=3.6) -a sec(e=3.7) -a sec(e=3.8) -a sec(e=3.9) -a sec(e=4) -a sec(e=4.1) -a sec(e=4.2) -a sec(e=4.3) -a sec(e=4.4) -a sec(e=4.5) -a sec(e=4.6) -a sec(e=4.7) -a sec(e=4.8) -a sec(e=4.9) -a sec(e=5) -a sec(e=5.1) -a sec(e=5.2) -a sec(e=5.3) -a sec(e=5.4) -a sec(e=5.5) -a sec(e=5.6) -a sec(e=5.7) -a sec(e=5.8) -a sec(e=5.9) -a sec(e=6)"

wsec_function="-a wsec(e=1.05) -a wsec(e=1.1) -a wsec(e=1.15) -a wsec(e=1.2) -a wsec(e=1.25) -a wsec(e=1.3) -a wsec(e=1.35) -a wsec(e=1.4) -a wsec(e=1.45) -a wsec(e=1.5) -a wsec(e=1.55) -a wsec(e=1.6) -a wsec(e=1.65) -a wsec(e=1.7) -a wsec(e=1.75) -a wsec(e=1.8) -a wsec(e=1.85) -a wsec(e=1.9) -a wsec(e=1.95) -a wsec(e=2)"

bigram_functions="${non_param_bigram_functions} ${sec_function} ${wsec_function}"

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
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Okno, morfeusz # Okno'
	crp='2w'
	stat="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
 
	echo 'Okno, morfeusz, czestosc # Okno'
	crp='2w'
	stat="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2w.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
	
	echo 'Okno, dziura # Okno, dziura'
	crp='2w1h'
	stat="relation(^,file=${relation_dir}/2w1h.csv)"
	extr="relation(^,file=${relation_dir}/2w1h.csv)"
	out_dir="${output_dir_base}/2_oknoDziura_okno_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
 
	echo 'Okno, dziura, morfeusz # Okno, dziura'
	crp='2w1h'
	stat="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_oknoDziura_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
 
	echo 'Okno, dziura, morfeusz, czestosc # Okno, dziura'
	crp='2w1h'
	stat="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2w1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_oknoDziura_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

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
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, okno # Relacje'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/2rw.csv)"
	extr="relation(^,file=${relation_dir}/2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura # Relacje, dziura'
	crp='2r1h'
	stat="relation(^,file=${relation_dir}/2r1h.csv)"
	extr="relation(^,file=${relation_dir}/2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, okno # Relacje, dziura'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/2rw1h.csv)"
	extr="relation(^,file=${relation_dir}/2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}


	# wydobywanie tylko czestych
	################################
	echo 'Relacje # Relacje czeste'
	crp='2r'
	stat="relation(^,file=${relation_dir}/2r.csv)"
	extr="relation(^,file=${relation_dir}/f2r.csv)"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, okno # Relacje czeste'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/2rw.csv)"
	extr="relation(^,file=${relation_dir}/f2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
 
	echo 'Relacje, dziura # Relacje czeste, dziura'
	crp='2r1h'
	stat="relation(^,file=${relation_dir}/2r1h.csv)"
	extr="relation(^,file=${relation_dir}/f2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, okno # Relacje czeste, dziura'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/2rw1h.csv)"
	extr="relation(^,file=${relation_dir}/f2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
	
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
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, okno, morfeusz # Relacje'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, morfeusz # Relacje, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, morfeusz, okno # Relacje, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	
	# wydobywanie tylko czestych
	################################
	echo 'Relacje, morfeusz # Relacje czeste'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, okno, morfeusz # Relacje czeste'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
 
	echo 'Relacje, dziura, morfeusz # Relacje czeste, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, okno, morfeusz # Relacje czeste, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
	
	### Koniec relacji ###
	echo 'Koniec relacji z morfeuszem.'
fi

if [ "${RELACJE_MORFEUSZ_CZESTOSC}" == true ] 
then
	### ###
	echo 'Relacje, morfeusz, czestosc ${frequency}...'

	echo 'Relacje, morfeusz, czestosc # Relacje'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, okno, morfeusz, czestosc # Relacje'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, morfeusz, czestosc # Relacje, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, morfeusz, okno, czestosc # Relacje, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	
	# wydobywanie tylko czestych
	################################
	echo 'Relacje, morfeusz, czestosc # Relacje czeste'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, okno, morfeusz, czestosc # Relacje czeste'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
 
	echo 'Relacje, dziura, morfeusz, czestosc # Relacje czeste, dziura'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	echo 'Relacje, dziura, okno, morfeusz, czestosc # Relacje czeste, dziura'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,file=${morfeusz}),corpora_frequency(>,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}_morfeusz_freq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv) -a w_tf_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
	
	### Koniec relacji ###
	echo 'Koniec relacji z morfeuszem i czestoscia.'
fi
