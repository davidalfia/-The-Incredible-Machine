#include "GameObj.h"

GameObj::GameObj(const sf::Vector2f& center, const bool dynamic, const bool movable, b2World &world, const Type_t type)
	:Button(center, type), m_phyObj(world, center, dynamic, type), m_movable(movable), m_initialLoc(center)
{
	m_ID = ID;
	ID ++;
	updateLoc();
	m_phyObj.setID(m_ID);
}

void GameObj::setIdZero()
{
	ID = 0;
	m_ID = ID;
	ID++;
	m_phyObj.setID(m_ID);
}

void GameObj::updateLoc()
{
	auto pos = m_phyObj.getPosition();
	BaseImg::setPosition(sf::Vector2f(pos.x * PPM, pos.y * PPM));
	BaseImg::setRotation(m_phyObj.getAngle());
}

void GameObj::backToStartingPlace()
{
	setPosition(m_initialLoc);
}

void GameObj::setInitialLoc()
{
	m_initialLoc = getLocation();
}

void GameObj::setPosition(const sf::Vector2f loc)
{
	m_phyObj.setPosition(loc);
	updateLoc();
}

void GameObj::setGravityScale(const float scale)
{
	m_phyObj.setGravityScale(scale);
}

void GameObj::updateBodySize()
{
	m_phyObj.setSize(BaseImg::getSize());
}

void GameObj::rotateBody(const int whichAngle)
{
	m_phyObj.setAngle(whichAngle);
	BaseImg::setRotation(m_phyObj.getAngle());
}

ObjInfo GameObj::getInfo() const
{
	ObjInfo info;
	info._loc = getLocation();
	info._typ = getType();
	return info;
}

int GameObj::aboveOrBelow(const GameObj& other) const
{
	if(this->getLocation().y > other.getLocation().y)
		return 1;

	return -1;
}

bool GameObj::isBelow(const GameObj& other) const
{
	if (this->getGlobalBounds().top > other.getLocation().y)
		return true;

	return false;
}

bool GameObj::pixelPerfectColides(const GameObj& other) const
{
	if(Collision::PixelPerfectTest(this->getSprite(), other.getSprite()))
		return true;
	
	return false;
}

void GameObj::setBodySize(const sf::Vector2f size)
{
	m_phyObj.setSize(size);
}