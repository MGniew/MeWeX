
#include "Module.h"


namespace program
{
	namespace metatool
	{


Module::Module(Id pModuleId, std::string&& pName)
:
	mModuleId(pModuleId),
	mName(std::forward<std::string>(pName))
{

}


Module::Module(Id pModuleId, std::string const& pName)
:
	mModuleId(pModuleId),
	mName(pName)
{

}


auto Module::getModuleId() const -> Id
{
	return mModuleId;
}


std::string const& Module::getName() const
{
	return mName;
}


bool Module::operator==(Module const& pModule) const
{
	return getName() == pModule.getName();
}


bool Module::operator!=(Module const& pModule) const
{
	return !((*this) == pModule);
}


bool Module::operator<(Module const& pModule) const
{
	return getName() < pModule.getName();
}


bool Module::operator>(Module const& pModule) const
{
	return getName() > pModule.getName();
}


bool Module::operator<=(Module const& pModule) const
{
	return !((*this) > pModule);
}


bool Module::operator>=(Module const& pModule) const
{
	return !((*this) < pModule);
}


	}
}
