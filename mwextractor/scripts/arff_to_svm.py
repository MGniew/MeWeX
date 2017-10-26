# Skrypt ma za zadanie konwersje plikow w formacie ARFF
# do formatow macierzowych odpowiednich dla programow LibSVM

def main(p_arff_file, p_svm_file):
	with open(p_arff_file, 'r') as arff:
		with open(p_svm_file,  'w') as svm:
			atr_count = 0
			for line in arff:
				line = line.strip()
				if line.startswith('@A'):
					atr_count += 1
				if line.startswith('@D'):
					break
			for line in arff:
				parts = line.strip().split(',')
				# +1 coz without reprezentation
				features = ['%d:%s' % iv for iv in enumerate(parts[1 - atr_count:-1])] 
				cls = parts[-1]
				string = '%s %s\n' % (cls, ' '.join(features))
				svm.write(string)


if __name__ == '__main__':
	import sys
	main(sys.argv[1], sys.argv[2])
