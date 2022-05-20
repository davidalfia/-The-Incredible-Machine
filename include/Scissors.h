#pragma once
#include "GameObj.h"
#include "Factory.h"

class Scissors : public GameObj
{
public:
	Scissors(const ObjInfo&, const bool, b2World &);
private:

    static bool m_registerit ;
};
