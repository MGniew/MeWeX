
#include <gtk-3.0/gtk/gtk.h>

#include "MetaTool.h"

//#include "MatrixTupleStorageManager.h"


namespace program
{
	namespace metatool
	{


void MetaTool::run(
	Config const& 	pConfig,
	int 			pArgc,
	char* 			pArgs[])
{
	mConfig = pConfig;

	/*MatrixTupleStorageManager mgr(0, "mtx_storage");
	auto id1 = mgr.loadFromFile("/media/ptakm/data1/michalw/magisterka/mgr/cmakebin/bin/wyniki_small/storage/");
	auto id2 = mgr.loadFromFile("/media/ptakm/data1/michalw/magisterka/mgr/cmakebin/bin/wyniki_small/storage/");
	auto id3 = mgr.loadFromFile("/media/ptakm/data1/michalw/magisterka/mgr/cmakebin/bin/wyniki_small/storage/");
	std::cerr << mgr.getName() << ' ' << id1 << ' ' << id2 << ' ' << id3 << std::endl;

	mgr.removeObject(id2);

	auto id2_2 = mgr.loadFromFile("/media/ptakm/data1/michalw/magisterka/mgr/cmakebin/bin/wyniki_small/storage/");
	auto id3_2 = mgr.loadFromFile("/media/ptakm/data1/michalw/magisterka/mgr/cmakebin/bin/wyniki_small/storage/");
	std::cerr << id2_2 << ' ' << id3_2 << std::endl;*/
}


	}
}
