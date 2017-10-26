mkdir -p ../../../dane/results/kipi/
mkdir -p ../../../dane/results/kipi_parts_tfidf/
mkdir -p ../../../dane/results/kipi_sub20/

time ./bigrams.sh > ../../../dane/results/kipi/log.txt
time ./bigrams_parts.sh > ../../../dane/results/kipi_parts_tfidf/log.txt
time ./bigrams_sub20.sh > ../../../dane/results/kipi_sub20/log.txt
