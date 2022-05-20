#pragma once

#include "Factory.h"
#include "Connectable.h"


class MouseEngine : public Connectable
{
public:
    MouseEngine(const ObjInfo& info, const bool movable, b2World &world);
    ~MouseEngine();

    void setStatus(const bool status) override;

private:
    static bool m_registerit;

};

