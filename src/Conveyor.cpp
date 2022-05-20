#include "Conveyor.h"
const int WIDTH = 80;
const int HEIGHT = 16;

Conveyor::Conveyor (const ObjInfo& info, const bool movable, b2World &world)
    :Connectable(info, movable, world)
{
    setIntRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
    updateBodySize();
    
}

bool Conveyor::m_registerit = ObjFactory::registerit(conveyor, [](const ObjInfo& info, bool movable, b2World &world)->std::shared_ptr<GameObj> { return std::make_shared<Conveyor>(info,movable,world); });
