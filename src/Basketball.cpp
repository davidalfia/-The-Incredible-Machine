#include "Basketball.h"


BasketBall::BasketBall (const ObjInfo& info, const bool movable, b2World &world)
    :Ball(info._loc, movable, world, basketBall)
{
}

bool BasketBall::m_registerit = ObjFactory::registerit(basketBall, [](const ObjInfo& info, const bool movable, b2World &world) -> std::shared_ptr<GameObj> { return std::make_shared<BasketBall>(info,movable,world); });