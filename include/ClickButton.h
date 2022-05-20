#pragma once
#include "Button.h"


class ClickButton : public Button
{
public:
    ClickButton(const sf::Vector2f& , const Type_t, const sf::Vector2i);
    ~ClickButton();

    bool mouseOnMe(const sf::Vector2f) override;
private:
    bool m_mouseOnMe = false;
};

