#include"MyListener.h"


void MyListener::BeginContact(const b2Contact* contact)
{

}

void MyListener::EndContact(const b2Contact* contact)
{

}

void MyListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* body1 = fixtureA->GetBody();
    b2Body* body2 = fixtureB->GetBody();

    auto obj1 = m_board->getObjWithId((int)(size_t)body1->GetUserData());
    auto obj2 = m_board->getObjWithId((int)(size_t)body2->GetUserData());

    m_board->getCollisionObj().processCollision(*obj1,*obj2);
}


void MyListener::setBoardReference(Board& board)
{
    m_board = &board;
}