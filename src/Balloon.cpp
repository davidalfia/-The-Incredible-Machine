#include "Balloon.h"
const int INIT_WIDTH =  32;
const int INIT_HEIGHT = 48;
const int END_WIDTH =   10;
const int END_HEIGHT =  10;
const int ANIM_WIDTH =  90;
const int ANIM_HEIGHT = 73;

const float START_GRAVITY = -0.3;
const float END_GRAVITY =    0.2;


Balloon::Balloon(const ObjInfo& info, const bool movable, b2World &world)
    :GameObj(info._loc, true, movable, world, balloon)
{
    setGravityScale(START_GRAVITY);
    setIntRect(sf::IntRect(0,0,INIT_WIDTH,INIT_HEIGHT));
    updateBodySize();
}

bool Balloon::m_registerit = ObjFactory::registerit(balloon, [](const ObjInfo& info, const bool movable, b2World &world) -> std::shared_ptr<GameObj> { return std::make_shared<Balloon>(info,movable,world); });


void Balloon::draw(sf::RenderWindow& window)
{
    if(endOfAnimation())
    {
        setGravityScale(END_GRAVITY);
        setBodySize(sf::Vector2f(END_WIDTH,END_HEIGHT));
    }
	else if(isOn())
		animate();

	BaseImg::draw(window);
		
}

void Balloon::setStatus(const bool status)
{
    GameObj::setStatus(status);
    if(status)
        ResourceManager::instance().playSFXballoon();
}

void Balloon::animate()
{
	if(getClock().getElapsedTime().asSeconds() > ANIMATION_TIME)
	{
		BaseImg::nextIntRect(ANIM_WIDTH,ANIM_HEIGHT);
		getClock().restart();	
	}	
}

void Balloon::backToStartingPlace()
{
    setStatus(false);
    setGravityScale(START_GRAVITY);
    setIntRect(sf::IntRect(0,0,INIT_WIDTH,INIT_HEIGHT));
    updateBodySize();
    setEndAnimation(false);
    GameObj::backToStartingPlace();

}