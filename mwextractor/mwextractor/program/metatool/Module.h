
#pragma once

#include <functional>
#include <string>


namespace program
{
	namespace metatool
	{


class Module
{
public:
	typedef size_t Id;

public:
	Module(Id pModuleId, std::string&& 		pName);
	Module(Id pModuleId, std::string const& pName);

	Module(Module&& 				pModule) 	= default;
	Module(Module const& 			pModule) 	= default;
	Module& operator=(Module&& 		pModule) 	= default;
	Module& operator=(Module const& pModule) 	= default;

	virtual ~Module() = default;


	Id getModuleId() const;

	std::string const& getName() const;


	bool operator==(Module const& pModule) 	const;
	bool operator!=(Module const& pModule) 	const;
	bool operator<(Module const& pModule) 	const;
	bool operator>(Module const& pModule) 	const;
	bool operator<=(Module const& pModule) 	const;
	bool operator>=(Module const& pModule) 	const;

private:
	Id			mModuleId;
	std::string mName;
};


	}
}


namespace std
{

template <>
struct hash<program::metatool::Module>
{
	typedef program::metatool::Module 	Module;
	typedef Module::Id 					ModuleId;

	size_t operator()(Module const& pModule) const
	{
		return std::hash<ModuleId>()(pModule.getModuleId());
	}
};

}
