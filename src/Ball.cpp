#include "Ball.h"

Ball::Ball(const sf::Vector2f& center,const bool movable, b2World &world,const Type_t type)
    :GameObj(center, true, movable, world, type)
{
}
