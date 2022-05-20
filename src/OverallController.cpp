#include "OverallController.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include "ResourceManager.h"



OverallController::OverallController(b2World& world, MyListener& listener)
	:m_world(world),
	m_levels(FileHandler(ResourceManager::instance().getLevelPath(), OPEN).readLevels()),
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "IncredibleMachine", sf::Style::Default),
	m_background(sf::Vector2f(MENU_X, MENU_Y), menuBackground),
	m_sound(sf::Vector2f(SOUND_X, SOUND_Y),sound),
	m_choseLevelMenu(sf::Vector2f(MENU_X, MENU_Y), choseLevelMenu),
	m_levelController(m_levels[m_numOfLevel], world, m_window, listener)
	
{
	m_window.setFramerateLimit(60);
	m_smallBoard.create(TINY_BOARD_W, TINY_BOARD_H);
	m_sound.setIntRect(sf::IntRect(MID_VOL_X, VOL_Y_RECT, VOL_WIDTH, VOL_HEIGHT));// fix to const globals

	setButtons();
	setLevel();
	setText();
}


void OverallController::run()
{
	ResourceManager::instance().setSong((int)ResourceManager::Sound::menu);
	while (m_window.isOpen())
	{
		m_window.clear();
		draw(m_window);
		m_window.display();

		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:

				closeWindow();
				break;

			case sf::Event::KeyPressed:

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					closeWindow();
				break;

			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				handleClick(location);
				break;
			}

			case sf::Event::MouseMoved:

				auto mouseLoc = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				handleMouseMove(mouseLoc);
				break;
			}
		}
	}
}


void OverallController::handleClick(const sf::Vector2f loc)
{

	if (m_mode == CHOOSE_LEVEL)
	{
		chooseLevelMode(loc);
	}
	else
		menuMode(loc);

}

void OverallController::chooseLevelMode(const sf::Vector2f loc)
{

	switch (getSelection(loc))
	{
	case playButton:
	{
		m_mode = 0;
		return;
	}
	case upButton:
	{
		m_numOfLevel = (++m_numOfLevel) % m_levels.size();
		setLevel();
		return;
	}
	case downButton:
	{
		if (--m_numOfLevel == -1)
			m_numOfLevel = int(m_levels.size() - 1);// try to fix with modulo
		setLevel();
		return;
	}
	default:
		return;
	}

}

void OverallController::drawTexts(sf::RenderWindow& window)
{
	setText();
	window.draw(m_levelGoal);
	window.draw(m_levelName);
	window.draw(m_levelNo);
}

void OverallController::setMenuTexts()
{
	m_levelName.setPosition(LEVEL_NAME_TEXT_LOC_MENU);
	m_levelNo.setPosition(LEVEL_NO_TEXT_LOC_MENU);
}

void OverallController::setChoseLevelTexts()
{
	m_levelName.setPosition(LEVEL_NAME_TEXT_LOC_CHOSE_LEVEL);
	m_levelNo.setPosition(LEVEL_NO_TEXT_LOC_CHOSE_LEVEL);
}

void OverallController::setText()
{
	m_levelGoal.setFont(ResourceManager::instance().getFont(ResourceManager::Font::CourierNew));
	m_levelGoal.setPosition(LEVEL_GOAL_TEXT_LOC);
	m_levelGoal.setFillColor(sf::Color::Black);
	m_levelGoal.setCharacterSize(CHARATER_SIZE);
	m_levelGoal.setOutlineThickness(CHARATER_OUTLINE_THICKNESS);


	m_levelName.setFont(ResourceManager::instance().getFont(ResourceManager::Font::CourierNew));
	m_levelName.setFillColor(sf::Color::Black);
	m_levelName.setCharacterSize(CHARATER_SIZE);
	m_levelName.setOutlineThickness(CHARATER_OUTLINE_THICKNESS);

	m_levelNo.setFont(ResourceManager::instance().getFont(ResourceManager::Font::CourierNew));
	m_levelNo.setFillColor(sf::Color::Black);
	m_levelNo.setCharacterSize(CHARATER_SIZE);
	m_levelNo.setOutlineThickness(CHARATER_OUTLINE_THICKNESS);

	if(m_mode != BUILD)
	{
		m_levelNo.setString("LEVEL:" + std::to_string(m_numOfLevel+1));
		m_levelName.setString(m_levels[m_numOfLevel].getLevelName());
		m_levelGoal.setString(m_levels[m_numOfLevel].getLevelGoal());
	}
	else
	{
		m_levelNo.setString("");
		m_levelName.setString("FREE BUILD MODE");
		m_levelGoal.setString("relax and enjoy building a world with the objects from the game\n(you can also make your own levels!\n read the README file to will find out how)\nhappy building!");
	}
	
}



void OverallController::menuMode(const sf::Vector2f loc)
{
	switch (getSelection(loc))
	{
	case startButton:
	{
		if (m_mode == MENU)
			ResourceManager::instance().setSong((int)ResourceManager::Sound::background);
		else if (m_mode == BUILD)
			ResourceManager::instance().setSong((int)ResourceManager::Sound::build);
		bool won = m_levelController.run();
		if (m_mode == MENU && won)
		{
			m_numOfLevel = (m_numOfLevel + 1) % m_levels.size();
			setLevel();
		}
		ResourceManager::instance().setSong((int)ResourceManager::Sound::menu);
		m_levelController.drawTinyBoard(m_smallBoard);
		return;
	}
	case exitButton:
	{
		closeWindow();
		return;
	}
	case upSound:
	{
		volumeUp();
		return;
	}
	case downSound:
	{
		volumeDown();
		return;
	}
	case reset:
	{
		setLevel();
		return;
	}
	case choseLevel:
	{
		m_mode = CHOOSE_LEVEL;
		return;
	}
	case build:
	{
		if (m_mode == BUILD)
			m_mode = MENU;
		else
			m_mode = BUILD;
		setLevel();
		return;
	}
	case save:
	{
		saveLevelToFile();
		return;
	}
	default:
		return;
	}
}

void OverallController::loadBuildMode()
{
	Level newLevel(BUILD);
	m_levelController.loadNewLevel(newLevel, STATIC);
	m_levelController.drawTinyBoard(m_smallBoard);
}

void OverallController::saveLevelToFile()
{
	m_levelController.saveNewLevel();
}

void OverallController::handleMouseMove(const sf::Vector2f mouseLoc)
{
	if(m_mode != CHOOSE_LEVEL)
		for (auto i = 0; i < m_menuButtons.size() ; i++)
			m_menuButtons[i].mouseOnMe(mouseLoc);
	
	else
		for (auto i = 0; i < m_choseLevelButtons.size() ; i++)
			m_choseLevelButtons[i].mouseOnMe(mouseLoc);

}

Type_t OverallController::getSelection(const sf::Vector2f loc) const
{
	if (m_mode == CHOOSE_LEVEL)
	{
		for (auto button : m_choseLevelButtons)
			if (button.mouseOnMe(loc))
				return button.getType();
	}
	else //MENU and BUILD modes
	{
		for (auto button : m_menuButtons)
		{
			if ((button.getType() == choseLevel && m_mode == BUILD) ||
				(button.getType() == save && m_mode == MENU))
				continue;
			if (button.mouseOnMe(loc))
				return button.getType();
		}
	}
	return none;
}

void OverallController::draw(sf::RenderWindow& window)
{
	sf::Sprite tinyBoard(m_smallBoard.getTexture());
	tinyBoard.setPosition(268, 70);//fix
	m_levelController.drawStatic(false);
	m_window.draw(tinyBoard);


	if (m_mode == CHOOSE_LEVEL)
	{
		setChoseLevelTexts();
		drawChoseLevel(window);
	}
	else
	{
		setMenuTexts();
		drawMenu(window);
	}
	drawTexts(window);
}

void OverallController::drawMenu(sf::RenderWindow& window)
{
	m_background.draw(window);
	for (auto& button : m_menuButtons)
	{
		if ((button.getType() == choseLevel && m_mode == BUILD) ||
			(button.getType() == save && m_mode == MENU))
			continue;
		button.draw(window);
	}
	m_sound.draw(window);
}

void OverallController::drawChoseLevel(sf::RenderWindow& window)
{
	m_choseLevelMenu.draw(window);
	for (auto& button : m_choseLevelButtons)
		button.draw(window);
}

void OverallController::setButtons()
{
	for (int i = exitButton; i < endMenuButtons; i++)
		m_menuButtons.push_back(ClickButton(sf::Vector2f(0, 0), Type_t(i), sf::Vector2i(getIntRectOfMenuIcon(i - exitButton).width, getIntRectOfMenuIcon(i - exitButton).height)));
	for (int i = playButton; i < endChoseLevelButtons; i++)
		m_choseLevelButtons.push_back(ClickButton(sf::Vector2f(0, 0), Type_t(i), sf::Vector2i(getIntRectOfChoseLevelIcon(i - playButton).width, getIntRectOfChoseLevelIcon(i - playButton).height)));

	for (auto i = 0; i < m_menuButtons.size(); i++)
	{
		//m_menuButtons[i].setIntRect(getIntRectOfMenuIcon(i));
		m_menuButtons[i].setPosition(sf::Vector2f(MENU_BUTTONS_LOC[i][0], MENU_BUTTONS_LOC[i][1]));
	}
	for (auto i = 0; i < m_choseLevelButtons.size(); i++)
	{
		//m_choseLevelButtons[i].setIntRect(getIntRectOfChoseLevelIcon(i));
		m_choseLevelButtons[i].setPosition(sf::Vector2f(CHOSE_LEVEL_BUTTONS_LOC[i][0], CHOSE_LEVEL_BUTTONS_LOC[i][1]));
	}
}

void OverallController::volumeUp()
{
	ResourceManager::instance().volUp();
	m_sound.nextIntRect();

}

void OverallController::volumeDown()
{
	ResourceManager::instance().volDown();
	m_sound.prevIntRect();
}

void OverallController::closeWindow()
{
	m_window.close();
}

void OverallController::setLevel()
{
	if(m_mode == BUILD)
		loadBuildMode();
	else
	{		
		m_levelController.loadNewLevel(m_levels[m_numOfLevel], DYNAMIC);
		m_levelController.drawTinyBoard(m_smallBoard);
	}
}

sf::IntRect getIntRectOfMenuIcon(const int i)
{
	return sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(MENU_BUTTONS_INT_RECT[i][0], MENU_BUTTONS_INT_RECT[i][1]));
}

sf::IntRect getIntRectOfChoseLevelIcon(const int i)
{
	return sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(CHOSE_LEVEL_BUTTONS_INT_RECT[i][0], CHOSE_LEVEL_BUTTONS_INT_RECT[i][1]));
}
