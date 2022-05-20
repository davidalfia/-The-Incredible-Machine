#pragma once

#include "Board.h"
#include "Level.h"
#include "Toolbar.h"
#include "MyListener.h"
#include "Score.h"


class LevelController
{
public:

	LevelController(const Level&, b2World& world, sf::RenderWindow&, MyListener& );

	bool run();

	bool clickOnToolbar(const sf::Vector2f )const;
	bool clickOnBoard(const sf::Vector2f)const;
	void createMouseImg(const sf::Vector2f);
	void updateMouseLoc(const sf::Vector2f);
	void loadNewLevel(const Level&, const bool);

	void whereAmI(const sf::Vector2f);
	void clearMouse();

	bool replaySolution();

	void drawAll(const bool);
	void drawStatic(const bool running);
	void drawTinyBoard (sf::RenderTexture& tinyBoard) const;
	void dealWithToolbar(const sf::Vector2f mouseLoc);
	void dealWithBoard(const sf::Vector2f mouseLoc);
	void saveNewLevel();
private:
	Score m_score;
	Board m_board;
	sf::RenderWindow& m_window;
	b2World& m_world;
	Toolbar m_toolbar;

	bool m_finished = false;

	Type_t m_selected = none;
	std::shared_ptr<GameObj> m_mouseObj = nullptr;
	BaseImg m_mouseImg;

	BaseImg m_frame;
	conditionsLocs m_locConditons;
	conditionsActs m_actConditions;

	bool m_mouseOnToolBr = false;
	void setText(sf::Text&);
	bool tryRunning();
	bool checkIfLevelFinished() const;
	void grabFromBoard(const std::shared_ptr<GameObj>, const sf::Vector2f);
	void createOnHandObj(const sf::Vector2f);
	void setSelected(const Type_t, const sf::Vector2f);
	void leftClick(const sf::Event);
	void handleBoardClick(const sf::Vector2f);
	void handleToolbarClick(const sf::Vector2f);
	void returnConnectableToToolbar();
};
