
#pragma once

#include "Config.h"

#include "../../structure/builder/CorporaParser.h"
#include "../../structure/builder/OrthExtractor.h"

#include "../../structure/storage/ContingencyTableSource.h"
#include "../../structure/storage/KBestTupleList.h"

#include "../../function/association/RankerData.h"


namespace program
{
	namespace web_tool
	{


class WebTool
{
public:
	typedef structure::storage::MatrixTupleStorage 						MatrixTupleStorage;
	typedef structure::builder::CorporaParser::TupleStoragePtrS			MatrixTupleStoragePtrS;
	typedef std::shared_ptr<structure::storage::ContingencyTableSource>	ContingencyTableSourcePtrS;
	typedef MatrixTupleStorage::TupleIdVector							TupleIdVector;
	typedef structure::storage::KBestTupleList							KBestTupleList;

	typedef function::association::RankerData							RankerData;
	typedef std::shared_ptr<RankerData>									RankerDataPtrS;

	typedef structure::builder::OrthExtractor::OrthFormMap				OrthFormMap;

public:
	/* TODO: Conception: build features using webtool */
	enum class WorkType
	{
		BUILD_RANKING,
		BUILD_FEATURES
	};

public:
	void start(Config const& pConfig);

private:
	MatrixTupleStoragePtrS 		parseCorpora() const;

	void						disperseStorage(MatrixTupleStoragePtrS const& pStorage) const;

	RankerDataPtrS				buildRankerData(MatrixTupleStoragePtrS const& pStorage,
			                                    TupleIdVector& pExtractionIds) const;

	KBestTupleList				generateKBest(RankerDataPtrS const& pRankerData,
											  TupleIdVector const& pExtractionIds) const;

	OrthFormMap					extractOrths(RankerDataPtrS const& pRankerData,
											 KBestTupleList const& pKBestList) const;

	void						writeKBest(RankerDataPtrS const& pRankerData,
			                               KBestTupleList const& pKBestList,
			                               OrthFormMap const& pOrthMap) const;



private:
	Config mConfig;
};


	}
}
