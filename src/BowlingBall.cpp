#include "BowlingBall.h"

BowlingBall::BowlingBall(const ObjInfo& info, const bool movable, b2World& world)
    :Ball(info._loc, movable, world, bowlingBall)
{
}

bool BowlingBall::m_registerit = ObjFactory::registerit(bowlingBall, [](const ObjInfo& info, const bool movable, b2World& world) -> std::shared_ptr<GameObj> { return std::make_shared<BowlingBall>(info, movable, world); });