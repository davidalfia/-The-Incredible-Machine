#include "BrickWall.h"

BrickWall::BrickWall (const ObjInfo& info, const bool movable, b2World &world)
    :Resizable(info, movable, world, brickWall)
{
}

bool BrickWall::m_registerit = ObjFactory::registerit(brickWall, [](const ObjInfo& info, const bool movable, b2World &world) -> std::shared_ptr<GameObj> { return std::make_shared<BrickWall>(info,movable,world);});
