#include "ToolbarButton.h"

ToolbarButton::ToolbarButton(const sf::Vector2f center, const Type_t objType, const int amount)
	:m_amount(amount),
	Button(center, objType)
{
	//setSize(sf::Vector2u(BUTTON_OBJ_SIZE,BUTTON_OBJ_SIZE));
	setScale(BUTTON_SCALE);
	m_text.setFont(ResourceManager::instance().getFont(ResourceManager::Font::kongtext));
	m_text.setCharacterSize(10);//fix
	m_text.setFillColor(sf::Color::Black);
	setString();
}

void ToolbarButton::setString()
{
	if (m_amount != -1)
		m_text.setString(std::to_string(m_amount));
}

void ToolbarButton::increase()
{
	if(m_amount != INFINITE_AMOUNT)
	{
		m_amount++;
		setString();
	}
}

void ToolbarButton::decrease()
{
	if (m_amount != INFINITE_AMOUNT)
	{
		m_amount--;
		setString();
	}
}

bool ToolbarButton::isEmpty() const
{
	return (m_amount == 0);
}

void ToolbarButton::setPosition(const sf::Vector2f pos)
{
	BaseImg::setPosition(pos);
	m_text.setPosition(sf::Vector2f(pos.x - 10, pos.y + getSize().y/2));//fix NUM_DIFF and -10 set origin center
}

void ToolbarButton::draw(sf::RenderWindow& w)
{
	BaseImg::draw(w);
	w.draw(m_text);
}

