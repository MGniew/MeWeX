
#include <sstream>
#include <fstream>

#include "../../exception/Exception.h"
#include "../../utils/Textual.h"

#include "StreamingFileReader.h"
#include "ArffTupleFeatureStorageIO.h"


namespace structure
{
	namespace io
	{


void ArffTupleFeatureStorageIO::writeToFile(
	std::string const& 				pFilePath,
	TupleFeatureStoragePtrS const& 	pDataSet,
	MatrixTupleStoragePtrS const&	pTupleStorage) const
{
	typedef storage::TupleFeatureStorage::InstanceMap __InstMap;

	std::fstream outputFile(pFilePath, std::ios_base::out);
	EXCEPTION(outputFile.is_open(), "ArffTupleFeatureStorageIO::writeToFile(): Cannot open an output file '" << pFilePath << "'.");
	utils::setStreamMaxDoublePrecision(outputFile);

	for (size_t n = 0; n < pDataSet->getHeaderNoteVector().size(); ++n)
	{
		outputFile << "% " << pDataSet->getHeaderNoteVector()[n] << std::endl;
	}

	outputFile << '%' << std::endl;
	outputFile << "@RELATION \"" << pDataSet->getRelationName() << '\"' << std::endl << std::endl;
	outputFile << "@ATTRIBUTE \"" << pDataSet->getReprezentationName() << "\"\tSTRING" << std::endl;
	outputFile << "@ATTRIBUTE \"" << "relation group" << "\"\tSTRING" << std::endl;
	outputFile << "@ATTRIBUTE \"" << "relation name" << "\"\tSTRING" << std::endl;

	for (size_t a = 0; a < pDataSet->getFeatureNameVector().size(); ++a)
	{
		outputFile << "@ATTRIBUTE \"" << pDataSet->getFeatureNameVector()[a] << "\"\tNUMERIC" << std::endl;
	}

	std::stringstream str;
	str << '{';
	for (size_t c = 0; c < pDataSet->getClassCount(); ++c)
	{
		str << c;
		if (c < pDataSet->getClassCount() - 1)
		{
			str << ',';
		}
	}
	str << '}';

	outputFile << "@ATTRIBUTE \"" << pDataSet->getClassName() << "\"\t" << str.str() << std::endl << std::endl;
	outputFile << "@DATA" << std::endl;

	__InstMap const& instances = pDataSet->getInstanceMap();
	for (auto iter = instances.begin(); iter != instances.end(); ++iter)
	{
		auto const& rel = pTupleStorage->findRelation(pTupleStorage->findTuple(iter->first).getRelation());
		outputFile << '"' << pTupleStorage->createTuplePosWordChain(iter->first) << "\",";
		outputFile << '"' << rel.getGroup() << "\",";
		outputFile << '"' << rel.getName() << "\",";
		storage::FeatureVector const& features = iter->second.getFeatureVector();
		for (size_t f = 0; f < features.size(); ++f)
		{
			outputFile << features[f] << ',';
		}
		outputFile << iter->second.getClass() << std::endl;
	}
}


auto ArffTupleFeatureStorageIO::readFromFile(
	std::string const& 				pFilePath,
	MatrixTupleStoragePtrS const&	pMatrixStorage) const -> TupleFeatureStoragePtrS
{
	typedef storage::Instance 						__Inst;
	typedef storage::MatrixTupleStorage::TupleId 	__TID;

	TupleFeatureStoragePtrS dataSet(new storage::TupleFeatureStorage());

	StreamingFileReader reader(pFilePath);

	std::string line;
	bool 		dataFound = false;
	while (reader.readline(line))
	{
		utils::trim(line);
		if (line[0] == '%')
		{
			if (line.size() > 2)
			{
				dataSet->getHeaderNoteVector().push_back(line.substr(2));
			}
		}
		else if (line[0] == '@')
		{
			char metaType = line[1];
			if (metaType == 'A' || metaType == 'a')
			{
				size_t from 		= line.find('\"');
				size_t to 			= line.find('\"', from + 1);
				std::string name 	= utils::substring(line, from + 1, to - 1);
				char type			= line[line.size() - 1];

				if (type == '}')	/* NOMINAL - class*/
				{
					dataSet->setClassCount(utils::toSizeT(
						line.data() + line.find_last_of("{,") + 1) + 1);
					dataSet->setClassName(name);
				}
				else if (type == 'G' || type == 'g') /* STRING - reprezentation */
				{
					dataSet->setReprezentationName(name);
				}
				else /* NUMERIC - feature */
				{
					dataSet->getFeatureNameVector().push_back(
						std::forward<std::string>(name));
				}
			}
			else if (metaType == 'D' || metaType == 'd')
			{
				dataFound = true;
				break;
			}
			else if (metaType == 'R' || metaType == 'r')
			{
				dataSet->setRelationName(utils::substring(line, line.find('\"') + 1, line.rfind('\"') - 1));
			}
			else
			{
				EXCEPTION(false, "ArffTupleFeatureStorageIO::readFromFile(): Arff file header is not valid.");
			}
		}
	}

	EXCEPTION(dataFound, "ArffTupleFeatureStorageIO::readFromFile(): @DATA not found.");

	size_t instanceNumber = 0;
	std::vector<std::string> parts;
	while (reader.readline(line))
	{
		utils::trim(line);
		EXCEPTION(
			line[0] != '@' && line[0] != '%',
			"ArffTupleFeatureStorageIO::readFromFile(): metadata tag or comment found in instance set, after " << instanceNumber << " instance.");

		++instanceNumber;

		size_t nameEnd = line.rfind('\"');
		utils::split(line.substr(nameEnd + 2), parts, ',');

		EXCEPTION(
			parts.size() == (dataSet->getFeatureCount() + 1),
			"ArffTupleFeatureStorageIO::readFromFile(): wrong field count in instance number " << instanceNumber << '.');

		__TID tid = pMatrixStorage->parseTupleReprezentation(utils::substring(line, 1, nameEnd - 1));
		__Inst instance(
			dataSet->getFeatureCount(),
			atoi(parts.back().c_str()));

		for (size_t f = 0; f < dataSet->getFeatureCount(); ++f)
		{
			instance.getFeatureVector()[f] = utils::toDouble(parts[f]);
		}

		dataSet->getInstanceMap().insert(std::pair<__TID, __Inst>(tid, std::forward<__Inst>(instance)));
	}

	return dataSet;
}


	}
}
