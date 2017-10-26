
#pragma once

#include "MatrixTupleStorage.h"
#include "../QueueKBestStructure.h"


namespace structure
{
	namespace storage
	{


typedef QueueKBestStructure<MatrixTupleStorage::TupleId, double>	KBestTupleStructure;
typedef KBestTupleStructure::KBestList								KBestTupleList;
typedef std::vector<KBestTupleList>									KBestTupleListVector;


	}
}
