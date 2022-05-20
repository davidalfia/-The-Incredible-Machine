#pragma once

#include <map>
#include <typeinfo>
#include <typeindex>

#include "GameObj.h"
#include "BaseBall.h"
#include "Balloon.h"
#include "Basketball.h"
#include "BowlingBall.h"
#include "BrickWall.h"
#include "Conveyor.h"
#include "MouseEngine.h"
#include "Trampoline.h"
#include "Scissors.h"


using HitFunctionPtr = void (*)(GameObj&, GameObj&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

class Collisions
{
public:

    Collisions();

    void processCollision(GameObj& object1, GameObj& object2);
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2);
    HitMap initializeCollisionMap();
};

namespace
{
    void scissorsBalloon(GameObj& object1, GameObj& object2)
    {
        if(object1.getGlobalBounds().left > object2.getGlobalBounds().left+object2.getGlobalBounds().width/2)
            object2.setStatus(true);
    }
    void balloonScissors(GameObj& object1, GameObj& object2)
    {
        scissorsBalloon(object2,object1);
    }


    void conveyorBalloon(GameObj& object1, GameObj& object2)
    {
        Conveyor&  conv  = static_cast<Conveyor&>(object1);
        
        if(conv.isOn())
        {
            b2Vec2 force;
            force.x = 0.0125f;
            force.y = 0.0f;

            force.x *= object1.aboveOrBelow(object2);

            object2.applyForce(force);
        }
    }
    void balloonConveyor(GameObj& object1, GameObj& object2)
    {
        conveyorBalloon(object2, object1);
    }


    void conveyorBasket(GameObj& object1, GameObj& object2)
    {
        Conveyor&  conv  = static_cast<Conveyor&>(object1);
    
        if(conv.isOn())
        {
            b2Vec2 force;
            force.x = 0.05f;
            force.y = 0.0f;

            force.x *= object1.aboveOrBelow(object2);

            object2.applyForce(force);
        }
    }
    void basketConveyor(GameObj& object1, GameObj& object2)
    {
        conveyorBasket(object2, object1);
    }

    void conveyorBase(GameObj& object1, GameObj& object2)
    {
       Conveyor&  conv  = static_cast<Conveyor&>(object1);

       if(conv.isOn())
        {
            b2Vec2 force;
            force.x = 0.005f;
            force.y = 0.0f;

            force.x *= object1.aboveOrBelow(object2);

            object2.applyForce(force);
        }
    }
    void baseConveyor(GameObj& object1, GameObj& object2)
    {
        conveyorBase(object2, object1);
    }


    void ballEngine(GameObj& object1, GameObj& object2)
    {
        MouseEngine&  engine  = static_cast<MouseEngine&>(object2);

        engine.setStatus(true);
    
    }
    void engineBall(GameObj& object1, GameObj& object2)
    {
        ballEngine(object2, object1);
    }

    void trampBall(GameObj& object1, GameObj& object2)
    {
        if(object1.isBelow(object2))
        {
            b2Vec2 force;
            force.x = 0.0;
            force.y = 0.125;
            object2.applyForce(force);
            object1.setStatus(true);
        }
    }
    void ballTramp(GameObj& object1, GameObj& object2)
    {
        trampBall(object2, object1);
    }

}
