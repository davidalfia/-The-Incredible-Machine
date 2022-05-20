#pragma once
#include "ClickButton.h"
#include "ToolbarButton.h"


using toolbarPair = std::pair<Type_t, int>;
using toolbarObjects = std::vector<toolbarPair>;
using toolbar = std::vector<ToolbarButton>;

class Toolbar
{
	
public:
	Toolbar(const toolbarObjects);
	bool clickedOnMe(const sf::Vector2f ) const;
	Type_t handleClick(const sf::Vector2f );
	void addOrIncrease(const Type_t, const int amount = 1);
	void deleteObj(const Type_t&);
	void draw(sf::RenderWindow&);

private:
	void add(const Type_t, const int);
	void updateLocs();
	void setBar();

	toolbar m_toolbar;
	int m_page = 0;
	sf::RectangleShape m_bar;

	std::shared_ptr<Button> m_play;
	std::shared_ptr<ClickButton> m_arrowRButton;
	std::shared_ptr<ClickButton> m_arrowLButton;

};


