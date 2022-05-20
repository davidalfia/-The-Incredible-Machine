#include "PipeWall.h"

PipeWall::PipeWall (const ObjInfo& info, const bool movable, b2World &world)
    :Resizable(info, movable, world, pipeWall)
{
}

bool PipeWall::m_registerit = ObjFactory::registerit(pipeWall, [](const ObjInfo& info, const bool movable, b2World &world) -> std::shared_ptr<GameObj> { return std::make_shared<PipeWall>(info,movable,world);});
