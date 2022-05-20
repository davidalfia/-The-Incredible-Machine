#pragma once

#include "Board.h"

class MyListener : public b2ContactListener
{
public:
    void BeginContact(const b2Contact* contact);
   
    void EndContact(const b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);


    void setBoardReference(Board&);

private:

    Board* m_board = nullptr;
};