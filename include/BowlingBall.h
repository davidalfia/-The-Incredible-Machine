#pragma once
#include "Ball.h"
#include "Factory.h"


class BowlingBall : public Ball
{
public:
	BowlingBall(const ObjInfo& info, const bool movable, b2World& world);

private:
	static bool m_registerit;
};
