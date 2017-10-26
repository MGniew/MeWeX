
#include "Instance.h"


namespace structure
{
	namespace storage
	{


Instance::Instance(
	size_t pFeatureCount,
	size_t pClass)
:
	mFeatureVector(pFeatureCount),
	mClass(pClass)
{

}


Instance::Instance(
	FeatureVector 	pFeatureVector,
	size_t 			pClass)
:
	mFeatureVector(pFeatureVector),
	mClass(pClass)
{

}


Instance::Instance()
:
	mClass(0)
{

}


auto Instance::getFeatureVector() const -> FeatureVector const&
{
	return mFeatureVector;
}


auto Instance::getFeatureVector() -> FeatureVector&
{
	return mFeatureVector;
}


int Instance::getClass() const
{
	return mClass;
}


std::ostream& operator<<(std::ostream& pStream, Instance const& pInstance)
{
	for (size_t f = 0; f < pInstance.getFeatureVector().size(); ++f)
	{
		pStream << pInstance.getFeatureVector()[f] << ',';
	}
	pStream << pInstance.getClass();
	return pStream;
}


	}
}
