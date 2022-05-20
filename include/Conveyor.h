#pragma once
#include "Factory.h"
#include "Connectable.h"

class Conveyor : public Connectable
{
public:
	Conveyor (const ObjInfo& info, const bool movable, b2World &world);
	
private:
	static bool m_registerit;
};
