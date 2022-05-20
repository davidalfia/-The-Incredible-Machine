#include "Button.h"
#include "globals.h"
#include "ResourceManager.h"


Button::Button(const sf::Vector2f& center, const Type_t obj)
	:BaseImg(center, obj),
	m_type(obj)
{
}

bool Button::mouseOnMe(const sf::Vector2f loc)
{
	if (getGlobalBounds().contains(loc))
		return true;

	return false;
}
Type_t Button::handleClick( const sf::Vector2f loc)
{
	if(mouseOnMe(loc))
		return getType();
	
	return none;

}

Type_t Button::getType() const
{
	return Type_t(m_type % BUTTON_DELTA_TYPE);
}


