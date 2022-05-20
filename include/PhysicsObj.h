#pragma once

#include <box2d/box2d.h>
#include "globals.h"
#include "ResourceManager.h"

class PhysicsObj
{
private:

    b2Body*         m_body;
    b2FixtureDef    m_fixtureDef;
    b2Fixture*      m_fixture;
    Type_t          m_type;

public:

    PhysicsObj(b2World &, const sf::Vector2f&, const bool, const Type_t);
    ~PhysicsObj();

    b2Vec2 getPosition() const { return  m_body->GetPosition(); }
    float getAngle() const { return m_body->GetAngle();}
    void setAngle(const int);
    void setPosition(const sf::Vector2f);
    void setGravityScale(const float);
    void setSize(const sf::Vector2f);
    void applyForce(const b2Vec2&);
    int randomNumber(const int min, const int max);
    void setID(const int);
};
