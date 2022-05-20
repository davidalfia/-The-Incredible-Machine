#pragma once
#include "GameObj.h"
#include "globals.h"

class Resizable : public GameObj
{
public:
	Resizable(const ObjInfo& info, const bool, b2World &, const Type_t);
    virtual ~Resizable(){}
	
    int getWhichSize() const    { return m_whichSize; }
    int getAngle() const        { return m_whichAngle; }
    int getIfFliped() const     { return m_isFliped; }

    void setTexture();
    ObjInfo getInfo() const override;
    void fixLastChange(const Type_t);
    void backToStartingPlace() override;
    void draw(sf::RenderWindow&) override;
    bool mouseOnMe(const sf::Vector2f ) override;
    void setPosition(const sf::Vector2f) override;
    Type_t handleClick(const sf::Vector2f ) override;
    void setWhichSize(const int size) { m_whichSize = size; }

private:
	int m_whichSize =   SMALLEST_SIZE;
    int m_whichAngle =  FIRST_ANGLE; 
    int m_isFliped =    NOT_RELEVANT;
    std::vector<Button> m_buttons;

    void makeItBigger();
    void makeItSmaller();
    void shiftL();
    void shiftR();

    void setButtons();
    void resetButtonsPos();
};

