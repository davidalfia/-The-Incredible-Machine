#include "Collisions.h"

Collisions::Collisions()
{
}

HitMap Collisions::initializeCollisionMap()
{
    HitMap map;

    map[Key(typeid(Balloon), typeid(Conveyor))]   = &balloonConveyor;
    map[Key(typeid(Conveyor), typeid(Balloon))]   = &conveyorBalloon;

    map[Key(typeid(BowlingBall), typeid(Conveyor))]   = &basketConveyor;
    map[Key(typeid(Conveyor), typeid(BowlingBall))]   = &conveyorBasket;

    map[Key(typeid(BasketBall), typeid(Conveyor))]   = &basketConveyor;
    map[Key(typeid(Conveyor), typeid(BasketBall))]   = &conveyorBasket;

    map[Key(typeid(Conveyor), typeid(BaseBall))]   = &conveyorBase;
    map[Key(typeid(BaseBall), typeid(Conveyor))]   = &baseConveyor;

    map[Key(typeid(MouseEngine), typeid(BaseBall))]   = &engineBall;
    map[Key(typeid(BaseBall), typeid(MouseEngine))]   = &ballEngine;

    map[Key(typeid(MouseEngine), typeid(BasketBall))]   = &engineBall;
    map[Key(typeid(BasketBall), typeid(MouseEngine))]   = &ballEngine;

    map[Key(typeid(MouseEngine), typeid(BowlingBall))]   = &engineBall;
    map[Key(typeid(BowlingBall), typeid(MouseEngine))]   = &ballEngine;

    map[Key(typeid(Trampoline), typeid(BasketBall))]   = &trampBall;
    map[Key(typeid(BasketBall), typeid(Trampoline))]   = &ballTramp;

    map[Key(typeid(Trampoline), typeid(BaseBall))]   = &trampBall;
    map[Key(typeid(BaseBall), typeid(Trampoline))]   = &ballTramp;

    map[Key(typeid(Trampoline), typeid(BowlingBall))]   = &trampBall;
    map[Key(typeid(BowlingBall), typeid(Trampoline))]   = &ballTramp;

    map[Key(typeid(Balloon), typeid(Scissors))]   = &balloonScissors;
    map[Key(typeid(Scissors), typeid(Balloon))]   = &scissorsBalloon;

    return map;
}

HitFunctionPtr Collisions::lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();

    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    
    if (mapEntry == collisionMap.end())
    { 
        return nullptr;
    }

    return mapEntry->second;
}

void Collisions::processCollision(GameObj& object1, GameObj& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    
    if (!phf)
    {
        return;
    }

    phf(object1, object2);
}
