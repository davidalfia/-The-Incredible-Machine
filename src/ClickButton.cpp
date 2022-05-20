#include "ClickButton.h"

ClickButton::ClickButton(const sf::Vector2f& center, const Type_t obj, const sf::Vector2i intRectSize)
    :Button(center, obj)
{
    BaseImg::setIntRect(sf::IntRect(0, 0, intRectSize.x, intRectSize.y));
}

ClickButton::~ClickButton()
{
}

bool ClickButton::mouseOnMe(const sf::Vector2f loc) 
{
    if(Button::mouseOnMe(loc))
    {
        nextIntRect();
        return true;
    }

    prevIntRect();
    return false;    
}
