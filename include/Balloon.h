#pragma once
#include "GameObj.h"
#include "Factory.h"

class Balloon : public GameObj
{
public:
	Balloon(const ObjInfo& info, const bool movable, b2World &world);
	void draw(sf::RenderWindow& window) override;
	void backToStartingPlace() override;
	void setStatus(const bool status) override;
	
private:
	void animate();
	static bool m_registerit;
};
