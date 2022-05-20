#pragma once
#include"Ball.h"
#include "Factory.h"

class BaseBall : public Ball
{
public:
	BaseBall (const ObjInfo& info, const bool movable, b2World &world);
	

private:
	static bool m_registerit;
};
