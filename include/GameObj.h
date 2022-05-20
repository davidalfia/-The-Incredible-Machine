#pragma once
#include "Button.h"
#include "PhysicsObj.h"
#include "CollisionsSFML.h"

static int ID = 0;

class GameObj : public Button
{
public:

	GameObj(const sf::Vector2f&, const bool, const bool, b2World &, const Type_t);
	virtual ~GameObj(){}

	virtual void backToStartingPlace();

	void setGravityScale(const float);
	int getID() const { return m_ID; }
	bool isMovable() const { return m_movable; }
	void updateBodySize();
	virtual ObjInfo getInfo() const; 
	void rotateBody(const int);
	void updateLoc();

	//for collisions
	int aboveOrBelow(const GameObj& other) const;
	bool isBelow(const GameObj& other) const;

	void wakeUp();

	void setMouse(const bool onMe) { m_mouseOnMe = onMe; } 
	bool getMouseOverMe() const { return m_mouseOnMe; }

	virtual void setPosition(const sf::Vector2f);
	virtual void setInitialLoc();

	void applyForce(const b2Vec2& force) { m_phyObj.applyForce(force); }

	bool pixelPerfectColides(const GameObj&) const;

	bool isOn() const { return m_status; }

	virtual void setStatus(const bool status) { m_status = status; }

	void setBodySize(const sf::Vector2f size);

	sf::Clock getClock() const{return m_clock;}

	void setIdZero();

private:

	PhysicsObj m_phyObj;
	bool m_movable;
	int m_ID;
	sf::Vector2f m_initialLoc;
	bool m_mouseOnMe = false;

	sf::Clock m_clock;
	bool m_status = OFF;
	
};
