#pragma once
#include "Button.h"


class ToolbarButton : public Button
{
public:

	ToolbarButton(const sf::Vector2f,Type_t, const int);
	void increase();
	void decrease();
	bool isEmpty() const;
	void setPosition(const sf::Vector2f);
	void draw(sf::RenderWindow&);
	
private:
	void setString();
	int m_amount;
	sf::Text m_text;
};
