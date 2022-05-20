#pragma once

#include "Board.h"
#include "FileHandler.h"
#include "LevelController.h"
#include "Level.h"
#include "ClickButton.h"

class OverallController
{
public:

	OverallController(b2World& world, MyListener& listener);
	void run();
	
private:

	void draw(sf::RenderWindow&);
	void drawMenu(sf::RenderWindow&);
	void drawChoseLevel(sf::RenderWindow&);
	void setButtons();
	void volumeUp();
	void volumeDown();
	void closeWindow();
	void setLevel();
	Type_t getSelection(const sf::Vector2f) const;
	void handleClick(const sf::Vector2f);
	void handleMouseMove(const sf::Vector2f);
	void menuMode(const sf::Vector2f);
	void loadBuildMode();
	void saveLevelToFile();
	void chooseLevelMode(const sf::Vector2f);
	void drawTexts(sf::RenderWindow&);
	void setMenuTexts();
	void setChoseLevelTexts();
	void setText();
	

	std::vector<ClickButton> m_menuButtons;
	std::vector<ClickButton> m_choseLevelButtons;
	sf::RenderWindow m_window;
	std::vector<Level> m_levels;
	b2World& m_world;
	BaseImg m_background;
	BaseImg m_choseLevelMenu;
	BaseImg m_sound;
	sf::Text m_levelGoal;
	sf::Text m_levelName;
	sf::Text m_levelNo;
	int m_numOfLevel = 0;
	LevelController m_levelController;
	sf::RenderTexture m_smallBoard;
	int m_mode = MENU;
};
sf::IntRect getIntRectOfMenuIcon(const int i);
sf::IntRect getIntRectOfChoseLevelIcon(const int i);
