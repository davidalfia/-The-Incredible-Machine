#include "MouseEngine.h"
const int WIDTH = 48;
const int HEIGHT = 32;

MouseEngine::MouseEngine(const ObjInfo& info, const bool movable, b2World &world)
    :Connectable(info, movable, world)
{
    setIntRect(sf::IntRect(0,0,WIDTH,HEIGHT));
    updateBodySize();
}

MouseEngine::~MouseEngine()
{
}

bool MouseEngine::m_registerit = ObjFactory::registerit(mouseEngine, [](const ObjInfo& info, const bool movable, b2World &world)->std::shared_ptr<GameObj> { return std::make_shared<MouseEngine>(info,movable,world); });




void MouseEngine::setStatus(const bool status)
{
    GameObj::setStatus(status);

    if(status)
        ResourceManager::instance().playSFXengine();
    else
        ResourceManager::instance().stopSFXengine();

}