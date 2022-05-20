#include "FancyWall.h"

FancyWall::FancyWall (const ObjInfo& info, const bool movable, b2World &world)
    :Resizable(info, movable, world, fancyWall)
{
}

bool FancyWall::m_registerit = ObjFactory::registerit(fancyWall, [](const ObjInfo& info, const bool movable, b2World &world) -> std::shared_ptr<GameObj> { return std::make_shared<FancyWall>(info,movable,world);});
