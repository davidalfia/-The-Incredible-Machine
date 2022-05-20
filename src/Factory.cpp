#include "Factory.h"

ObjFactory::ObjFactory()
{
}


std::shared_ptr<GameObj> ObjFactory::create(const ObjInfo& info, const bool movable, b2World &world)
{
	auto it = ObjFactory::getMap().find(info._typ);
	if (it == ObjFactory::getMap().end())
		return nullptr;

	return it->second(info,movable,world);
}

bool ObjFactory::registerit(const Type_t& name, const funcPtr f) 
{
	ObjFactory::getMap().emplace(name, f);
	return true;
}