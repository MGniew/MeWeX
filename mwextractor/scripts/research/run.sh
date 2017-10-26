#time ./tuples_builder_parts_20.sh
#time ./disperser.sh

#time ./subsample_5.sh

#mkdir -p ../../../dane/results/kipi/
#mkdir -p ../../../dane/results/kipi_parts_10_tfidf/
#mkdir -p ../../../dane/results/kipi_parts_20_tfidf/
#mkdir -p ../../../dane/results/kipi_sub20/
#mkdir -p ../../../dane/results/kipi_sub20/
#mkdir -p ../../../dane/results/kipi_sub5/
mkdir -p ../../../dane/results/kipi_nn_normalization/

#time ./bigrams.sh > ../../../dane/results/kipi/log.txt 2>&1
#time ./bigrams_parts_10.sh > ../../../dane/results/kipi_parts_10_tfidf/log.txt 2>&1
#time ./bigrams_parts_20.sh > ../../../dane/results/kipi_parts_20_tfidf/log.txt 2>&1
#time ./bigrams_sub20.sh > ../../../dane/results/kipi_sub20/log.txt 2>&1
#time ./bigrams_subsampled.sh > ../../../dane/results/kipi_sub20/log.txt 2>&1

time ./bigrams_nn.sh > ../../../dane/results/kipi_nn_normalization/log.txt 2>&1
