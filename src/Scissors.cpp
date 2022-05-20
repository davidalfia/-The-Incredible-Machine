#include "Scissors.h"


Scissors::Scissors(const ObjInfo& info, const bool movable, b2World &world)
    :GameObj(info._loc, STATIC, movable, world, info._typ)
{
}

bool Scissors::m_registerit = ObjFactory::registerit(scissors, [](const ObjInfo& info, const bool movable, b2World &world)->std::shared_ptr<GameObj> { return std::make_shared<Scissors>(info,movable,world); });

