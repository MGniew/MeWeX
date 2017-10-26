
##########################################################################################################
# constants
tool='/home/michalw/mgr/cmakebin/bin/Miner'
input_dir_base='/home/michalw/dane/storage'
output_dir_base='/home/michalw/dane/results'
relation_dir='/home/michalw/mgr/data/patterns'

rounds='3'
folds='5'
threads='10'
fix_relevant_order='1'
kbest_length='50000'
write_kbests='1'

quality_functions='-q prc()'
relevant_set="/home/michalw/mgr/data/units/WN_2014_10_20_ling_2014_11.csv"
morfeusz='/home/michalw/dane/storage/morfeusz.csv'
frequency='6'

bigram_functions="-a frequency() -a ef() -a ief() -a jaccard() -a dice() -a sorgenfrei() -a or() -a us() -a ct1() -a ct2() -a me() -a sc() -a wsc() -a smd() -a sfbmd() -a sec(e=3.4) -a sec(e=3.5) -a sec(e=3.6) -a sec(e=3.7) -a sec(e=3.8) -a sec(e=3.9) -a sec(e=4) -a sec(e=4.1) -a sec(e=4.2) -a sec(e=4.3) -a sec(e=4.4) -a sec(e=4.5) -a wsec(1.15) -a wsec(e=1.2) -a wsec(e=1.25) -a wsec(e=1.3) -a wsec(e=1.35) -a wsec(e=1.4) -a wsec(e=1.45) -a wsec(e=1.5) -a wsec(e=1.55) -a wsec(e=1.6) -a wsec(e=1.65) -a tscore() -a zscore() -a px2() -a wx2() -a g2()"

command="${tool} -r ${relevant_set} ${quality_functions} -R ${rounds} -F ${folds} -T ${threads} -e ${fix_relevant_order} -K ${kbest_length} -w ${write_kbests} ${bigram_functions}"

corpus="${input_dir_base}/kipi"


####################
# Przelaczniki
# compute flex storage
COMPUTE_FLEX=true
# compute fix storage
COMPUTE_FIX=true

####################
# wzorzec:
# 	dlugosc_budowa_ekstrakcja_korpus
# przyklad: 
#	2_okno_okno_2r

### OKNA ###
echo 'Okna.'
# zwykle okno - jeden z baseline'ow
################################
# budowa:	okno
# ekstrakcja:	2, okno
if [ "$COMPUTE_FLEX" = true ]
then
	echo 'Budowa: okno, ekstrakcja: 2, okno'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/window2.csv)"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:       okno
	# ekstrakcja:   2, okno
	echo 'Budowa: okno + dziura, ekstrakcja: 2, okno'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/window1h2.csv)"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}
fi

if [ "$COMPUTE_FIX" = true ]
then
	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno
	echo 'Budowa: okno, ekstrakcja: 2, okno, order'
	crp='2rwfix'
	stat="relation(^,file=${relation_dir}/window2fix.csv)"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno
	echo 'Budowa: okno + dziura, ekstrakcja: 2, okno, order'
	crp='2rw1hfix'
	stat="relation(^,file=${relation_dir}/window2fix1h.csv)"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
fi


if [ "$COMPUTE_FLEX" = true ]
then
	# okno, morfeusz
	################################
	# budowa:	okno, morfeusz
	# ekstrakcja:	2, okno, morfeusz
	echo 'Budowa: okno, ekstrakcja: 2, okno, morfeusz'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/window2.csv),every_word(^,file=${morfeusz}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	# okno, morfeusz
	################################
	# budowa:       okno, morfeusz
	# ekstrakcja:   2, okno, morfeusz
	echo 'Budowa: okno + dziura, ekstrakcja: 2, okno, morfeusz'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/window21h.csv),every_word(^,file=${morfeusz}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}
fi

if [ "$COMPUTE_FIX" = true ]
then
	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno, morfeusz
	echo 'Budowa: okno, ekstrakcja: 2, okno, order, morfeusz'
	crp='2rwfix'
	stat="and(relation(^,file=${relation_dir}/window2fix.csv),every_word(^,file=${morfeusz}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno, morfeusz
	echo 'Budowa: okno + dziura, ekstrakcja: 2, okno, order, morfeusz'
	crp='2rw1hfix'
	stat="and(relation(^,file=${relation_dir}/window2fix1h.csv),every_word(^,file=${morfeusz}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
fi


if [ "$COMPUTE_FLEX" = true ]
then
	# okno, morfeusz, freq
	################################
	# budowa:       okno, morfeusz
	# ekstrakcja:   2, okno, morfeusz
	echo 'Budowa: okno, ekstrakcja: 2, okno, morfeusz, czestosc'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/window2.csv),every_word(^,file=${morfeusz}),frequency(>=,${frequency}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	# okno, morfeusz, freq
	################################
	# budowa:       okno, morfeusz
	# ekstrakcja:   2, okno, morfeusz
	echo 'Budowa: okno + dziura, ekstrakcja: 2, okno, morfeusz, czestosc'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/window1h2.csv),every_word(^,file=${morfeusz}),frequency(>=,${frequency}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}
fi

if [ "$COMPUTE_FIX" = true ]
then
	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno
	echo 'Budowa: okno, ekstrakcja: 2, okno, order, morfeusz, czestosc'
	crp='2rwfix'
	stat="and(relation(^,file=${relation_dir}/window2fix.csv),every_word(^,file=${morfeusz}),frequency(>=,${frequency}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	# zwykle okno - jeden z baseline'ow
	################################
	# budowa:	okno
	# ekstrakcja:	2, okno
	echo 'Budowa: okno, ekstrakcja: 2, okno, order, morfeusz, czestosc'
	crp='2rw1hfix'
	stat="and(relation(^,file=${relation_dir}/window2fix1h.csv),every_word(^,file=${morfeusz}),frequency(>=,${frequency}))"
	extr=${stat}
	out_dir="${output_dir_base}/2_okno_okno_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
fi

### Koniec okien ###
echo 'Koniec okien.'
echo ''

### ###
echo 'Relacje.'

if [ "$COMPUTE_FLEX" = true ]
then
	# wszystkie relacje
	################################
	# budowa:	relacje
	# ekstrakcja:	2, relacje
	echo 'Budowa: relacje, ekstirakcja: 2, relacje'
	crp='2r'
	stat="relation(^,file=${relation_dir}/2r.csv)"
	extr=${stat}
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + okno
	# ekstrakcja:	2, relacje
	echo 'Budowa: relacje + okno, ekstrakcja: 2, relacje'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/2rw.csv)"
	extr="relation(^,file=${relation_dir}/2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura
	# ekstrakcja:	2, relacje
	echo 'Budowa: relacje + dziura, ekstrakcja: 2, relacje'
	crp='2r1h'
	stat="relation(^,file=${relation_dir}/2r1h.csv)"
	extr="relation(^,file=${relation_dir}/2r.csv)"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura + okno
	# ekstrakcja:	2, relacje
	echo 'Budowa: relacje + dziura + okno, ekstrakcja: 2, relacje'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/2rw1h.csv)"
	extr="relation(^,file=${relation_dir}/2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}


	# wydobywanie tylko czestych
	################################
	# budowa:	relacje
	# ekstrakcja:	2, relacje czeste
	echo 'Budowa: relacje, ekstrakcja: 2, relacje czeste'
	crp='2r'
	stat="relation(^,file=${relation_dir}/2r.csv)"
	extr="relation(^,file=${relation_dir}/f2r.csv)"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + okno
	# ekstrakcja:	2, relacje czeste
	echo 'Budowa: relacje + okno, ekstrakcja: 2, relacje czeste'
	crp='2rw'
	stat="relation(^,file=${relation_dir}/2rw.csv)"
	extr="relation(^,file=${relation_dir}/f2r.csv)"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura
	# ekstrakcja:	2, relacje czeste
	echo 'Budowa: relacje + dziura, ekstrakcja: 2, relacje czeste'
	crp='2r1h'
	stat="relation(^,file=${relation_dir}/2r1h.csv)"
	extr="relation(^,file=${relation_dir}/f2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura + okno
	# ekstrakcja:	2, relacje czeste
	echo 'Budowa: relacje + dziura + okno, ekstrakcja: 2, relacje czeste'
	crp='2rw1h'
	stat="relation(^,file=${relation_dir}/2rw1h.csv)"
	extr="relation(^,file=${relation_dir}/f2r1h.csv)"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}
fi

if [ "$COMPUTE_FIX" = true ]
then
	# porownanie z miara szyku
	################################
	# budowa:	relacje szyku
	# ekstrakcja:	2 + o, relacje szyku 
	echo 'Budowa: relacje szyku, ekstrakcja: 2, relacje szyku'
	crp='2rfix'
	stat="relation(^,file=${relation_dir}/2rfix.csv)"
	extr="relation(^,file=${relation_dir}/2rfix.csv)"
	out_dir="${output_dir_base}/2_szyk_szyk_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:	relacje + okno
	# ekstrakcja:	2 + o, relacje szyku
	echo 'Budowa: relacje szyku + okno, ekstrakcja: 2, relacje szyku'
	crp='2rwfix'
	stat="relation(^,file=${relation_dir}/2rwfix.csv)"
	extr="relation(^,file=${relation_dir}/2rfix.csv)"
	out_dir="${output_dir_base}/2_szykOkno_szyk_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:	relacje + dziura
	# ekstrakcja:	2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura, ekstrakcja: 2, relacje szyku'
	crp='2r1hfix'
	stat="relation(^,file=${relation_dir}/2r1hfix.csv)"
	extr="relation(^,file=${relation_dir}/2r1hfix.csv)"
	out_dir="${output_dir_base}/2_szykDziura_szykDziura_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:	relacje + dziura + okno
	# ekstrakcja:	2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura + okno, ekstrakcja: 2, relacje szyku'
	crp='2rw1hfix'
	stat="relation(^,file=${relation_dir}/2rw1hfix.csv)"
	extr="relation(^,file=${relation_dir}/2r1hfix.csv)"
	out_dir="${output_dir_base}/2_szykOknoDziura_szykDziura_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	"${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}"


	# porownanie z miara szyku, czeste relacje
	################################
	# budowa:       relacje szyku czeste
	# ekstrakcja:   2 + o, relacje szyku 
	echo 'Budowa: relacje szyku, ekstrakcja: 2, czeste relacje szyku'
	crp='2rfix'
	stat="relation(^,file=${relation_dir}/2rfix.csv)"
	extr="relation(^,file=${relation_dir}/f2rfix.csv)"
	out_dir="${output_dir_base}/2_szyk_szykCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + okno
	# ekstrakcja:   2 + o, relacje szyku
	echo 'Budowa: relacje szyku + okno, ekstrakcja: 2, czeste relacje szyku'
	crp='2rwfix'
	stat="relation(^,file=${relation_dir}/2rwfix.csv)"
	extr="relation(^,file=${relation_dir}/f2rfix.csv)"
	out_dir="${output_dir_base}/2_szykOkno_szykCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura, ekstrakcja: 2, czeste relacje szyku'
	crp='2r1hfix'
	stat="relation(^,file=${relation_dir}/2r1hfix.csv)"
	extr="relation(^,file=${relation_dir}/f2r1hfix.csv)"
	out_dir="${output_dir_base}/2_szykDziura_szykDziuraCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura + okno
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura + okno, ekstrakcja: 2, czeste relacje szyku'
	crp='2rw1hfix'
	stat="relation(^,file=${relation_dir}/2rw1hfix.csv)"
	extr="relation(^,file=${relation_dir}/f2r1hfix.csv)"
	out_dir="${output_dir_base}/2_szykOknoDziura_szykDziuraCzeste_${crp}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
fi

### Morfeusz ###
echo ''
echo 'Morfeusz.'

if [ "$COMPUTE_FLEX" = true ]
then
	# morfeusz, wydobywanie wszystkich relacji
	################################
	# budowa:       relacje
	# ekstrakcja:   2, relacje, morfeusz
	echo 'Budowa: relacje, ekstrakcja: 2, relacje, morfeusz'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:       relacje + okno
	# ekstrakcja:   2, relacje, morfeusz
	echo 'Budowa: relacje + okno, ekstrakcja: 2, relacje, morfeusz'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:       relacje + dziura
	# ekstrakcja:   2, relacje, morfeusz
	echo 'Budowa: relacje + dziura, ekstrakcja: 2, relacje, morfeusz'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:       relacje + dziura + okno
	# ekstrakcja:   2, relacje, morfeusz
	echo 'Budowa: relacje + dziura + okno, ekstrakcja: 2, relacje, morfeusz'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}


	# morfeusz, wydobywanie tylko czestych
	################################
	# budowa:	relacje
	# ekstrakcja:	2, relacje czeste, morfeusz
	echo 'Budowa: relacje, ekstrakcja: 2, relacje czeste, morfeusz'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + okno
	# ekstrakcja:	2, relacje czeste, morfeusz
	echo 'Budowa: relacje + okno, ekstrakcja: 2, relacje czeste, morfeusz'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura
	# ekstrakcja:	2, relacje czeste, morfeusz
	echo 'Budowa: relacje + dziura, ekstrakcja: 2, relacje czeste, morfeusz'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura + okno
	# ekstrakcja:	2, relacje czeste, morfeusz
	echo 'Budowa: relacje + dziura + okno, ekstrakcja: 2, relacje czeste, morfeusz'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}
fi

if [ "$COMPUTE_FIX" = true ]
then
	# porownanie z miara szyku, morfeusz
	################################
	# budowa:       relacje szyku
	# ekstrakcja:   2 + o, relacje szyku 
	echo 'Budowa: relacje szyku, ekstrakcja: 2, relacje szyku, morfeusz'
	crp='2rfix'
	stat="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szyk_szyk_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + okno
	# ekstrakcja:   2 + o, relacje szyku
	echo 'Budowa: relacje szyku + okno, ekstrakcja: 2, relacje szyku, morfeusz'
	crp='2rwfix'
	stat="and(relation(^,file=${relation_dir}/2rwfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szykOkno_szyk_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura, ekstrakcja: 2, relacje szyku, morfeusz'
	crp='2r1hfix'
	stat="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szykDziura_szykDziura_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura + okno
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura + okno, ekstrakcja: 2, relacje szyku, morfeusz'
	crp='2rw1hfix'
	stat="and(relation(^,file=${relation_dir}/2rw1hfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szykOknoDziura_szykDziura_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}


	# porownanie z miara szyku, czeste, morfeusz
	################################
	# budowa:       relacje szyku czeste
	# ekstrakcja:   2 + o, relacje szyku 
	echo 'Budowa: relacje szyku, ekstrakcja: 2, czeste relacje szyku, morfeusz'
	crp='2rfix'
	stat="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2rfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szyk_szykCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + okno
	# ekstrakcja:   2 + o, relacje szyku
	echo 'Budowa: relacje szyku + okno, ekstrakcja: 2, czeste relacje szyku, morfeusz'
	crp='2rwfix'
	stat="and(relation(^,file=${relation_dir}/2rwfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2rfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szykOkno_szykCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura, ekstrakcja: 2, czeste relacje szyku, morfeusz'
	crp='2r1hfix'
	stat="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1hfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szykDziura_szykDziuraCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura + okno
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura + okno, ekstrakcja: 2, czeste relacje szyku, morfeusz'
	crp='2rw1hfix'
	stat="and(relation(^,file=${relation_dir}/2rw1hfix.csv),every_word(^,${morfeusz}))"
	extr="and(relation(^,file=${relation_dir}/f2r1hfix.csv),every_word(^,${morfeusz}))"
	out_dir="${output_dir_base}/2_szykOknoDziura_szykDziuraCzeste_${crp}_morfeusz"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
fi

### Morfeusz i czestosc ###
echo ''
echo 'Morfeusz i czestosc.'

if [ "$COMPUTE_FLEX" = true ]
then
	# morfeusz + czestosc
	################################
	# budowa:	relacje
	# ekstrakcja:	2, relacje, morfeusz, czestosc
	echo 'Budowa: relacje, ekstrakcja: 2, relacje, morfeusz, czestosc'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacje_relacje_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + okno
	# ekstrakcja:	2, relacje, morfeusz, czestosc
	echo 'Budowa: relacje + okno, ekstrakcja: 2, relacje, morfeusz, czestosc'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacje_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura
	# ekstrakcja:	2, relacje, morfeusz, czestosc
	echo 'Budowa: relacje + dziura, ekstrakcja: 2, relacje, morfeusz, czestosc'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacje_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura + okno
	# ekstrakcja:	2, relacje, morfeusz, czestosc
	echo 'Budowa: relacje + dziura + okno, ekstrakcja: 2, relacje, morfeusz, czestosc'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacje_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}


	# morfeusz + czestosc, relacje czeste
	################################
	# budowa:	relacje
	# ekstrakcja:	2, relacje czeste, morfeusz, czestosc
	echo 'Budowa: relacje, ekstrakcja: 2, relacje czeste, morfeusz, czestosc'
	crp='2r'
	stat="and(relation(^,file=${relation_dir}/2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacje_relacjeCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + okno
	# ekstrakcja:	2, relacje czeste, morfeusz, czestosc
	echo 'Budowa: relacje + okno, ekstrakcja: 2, relacje czeste, morfeusz, czestosc'
	crp='2rw'
	stat="and(relation(^,file=${relation_dir}/2rw.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOkno_relacjeCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura
	# ekstrakcja:	2, relacje czeste, morfeusz, czestosc
	echo 'Budowa: relacje + dziura, ekstrakcja: 2, relacje czeste, morfeusz, czestosc'
	crp='2r1h'
	stat="and(relation(^,file=${relation_dir}/2r1h.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeDziura_relacjeCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}

	################################
	# budowa:	relacje + dziura + okno
	# ekstrakcja:	2, relacje czeste, morfeusz, czestosc
	echo 'Budowa: relacje + dziura + okno, ekstrakcja: 2, relacje czeste, morfeusz, czestosc'
	crp='2rw1h'
	stat="and(relation(^,file=${relation_dir}/2rw1h.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1h.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_relacjeOknoDziura_relacjeCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr}
fi


if [ "$COMPUTE_FIX" = true ]
then
	# porownanie z miara szyku, morfeusz, czestosc
	################################
	# budowa:       relacje szyku
	# ekstrakcja:   2 + o, relacje szyku 
	echo 'Budowa: relacje szyku, ekstrakcja: 2, relacje szyku, morfeusz, czestosc'
	crp='2rfix'
	stat="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szyk_szyk_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + okno
	# ekstrakcja:   2 + o, relacje szyku
	echo 'Budowa: relacje szyku + okno, ekstrakcja: 2, relacje szyku, morfeusz, czestosc'
	crp='2rwfix'
	stat="and(relation(^,file=${relation_dir}/2rwfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szykOkno_szyk_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura, ekstrakcja: 2, relacje szyku, morfeusz, czestosc'
	crp='2r1hfix'
	stat="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szykDziura_szykDziura_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura + okno
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura + okno, ekstrakcja: 2, relacje szyku, morfeusz, czestosc'
	crp='2rw1hfix'
	stat="and(relation(^,file=${relation_dir}/2rw1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szykOknoDziura_szykDziura_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}


	# porownanie z miara szyku, czeste, morfeusz, czestosc
	################################
	# budowa:       relacje szyku
	# ekstrakcja:   2 + o, relacje szyku 
	echo 'Budowa: relacje szyku, ekstrakcja: 2, czeste relacje szyku, morfeusz, czestosc'
	crp='2rfix'
	stat="and(relation(^,file=${relation_dir}/2rfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2rfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szyk_szykCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + okno
	# ekstrakcja:   2 + o, relacje szyku
	echo 'Budowa: relacje szyku + okno, ekstrakcja: 2, czeste relacje szyku, morfeusz, czestosc'
	crp='2rwfix'
	stat="and(relation(^,file=${relation_dir}/2rwfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2rfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szykOkno_szykCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura, ekstrakcja: 2, czeste relacje szyku, morfeusz, czestosc'
	crp='2r1hfix'
	stat="and(relation(^,file=${relation_dir}/2r1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szykDziura_szykDziuraCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}

	################################
	# budowa:       relacje + dziura + okno
	# ekstrakcja:   2 + o, relacje szyku i dziura
	echo 'Budowa: relacje szyku + dziura + okno, ekstrakcja: 2, czeste relacje szyku, morfeusz, czestosc'
	crp='2rw1hfix'
	stat="and(relation(^,file=${relation_dir}/2rw1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	extr="and(relation(^,file=${relation_dir}/f2r1hfix.csv),every_word(^,${morfeusz}),frequency(>=,${frequency}))"
	out_dir="${output_dir_base}/2_szykOknoDziura_szykDziuraCzeste_${crp}_morfeuszFreq${frequency}"
	mkdir -p ${out_dir}
	order="-a w_order(scheme=${corpus}/${crp}/scheme.csv)"
	${command} -I ${corpus}/${crp} -O ${out_dir} -s ${stat} -x ${extr} ${order}
fi

### Koniec relacji ###
echo 'Koniec relacji.'
echo ''
