#include "LevelController.h"
#include "ResourceManager.h"
#include <iostream>
#include "Score.h"

LevelController::LevelController(const Level& lvl, b2World& world, sf::RenderWindow& win, MyListener& listener)
	:m_board(lvl.getBoardObjs(), world), m_window(win), m_world(world), m_toolbar(lvl.getToolbarObjs()),
	m_locConditons(lvl.getLocConditions()), m_actConditions(lvl.getActConditions()),
	m_mouseImg(sf::Vector2f(-100.f, -100.f), baseBall),
	m_frame(sf::Vector2f(FRAME_X, FRAME_Y), frame), m_score(INIT_SCORE, DYNAMIC)

{
	listener.setBoardReference(m_board);
}

void LevelController::loadNewLevel(const Level& level, const bool dynamicScore)
{
	m_finished = false;
	m_board = Board(level.getBoardObjs(), m_world);
	m_toolbar = Toolbar(level.getToolbarObjs());
	m_locConditons = level.getLocConditions();
	m_actConditions = level.getActConditions();
	m_score.setDynamic(dynamicScore);
	m_score.set(INIT_SCORE);
}

bool LevelController::run()
{
	m_score.play();

	while (m_window.isOpen() && !m_finished)
	{
		drawAll(NOT_RUNNING);
		
		sf::Event event;

		while (m_window.pollEvent(event) && !m_finished)// fix 
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					m_score.stop();
					return false;//level finished without win
				}
				else if (event.mouseButton.button == sf::Mouse::Button::Left)
					leftClick(event);
				break;
			}
			case sf::Event::MouseMoved:
				auto mouseLoc = m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
				whereAmI(mouseLoc);
				updateMouseLoc(mouseLoc);
				break;
			}
			
        }
    }

	while(replaySolution() && m_finished)
	{
		m_board.resetObjectsPositions();
		tryRunning();
	}

	if (m_finished)
		m_score.stop();
	
  	return m_finished;

}


void LevelController::leftClick(const sf::Event event)
{				
	auto mouseLoc = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	
	if (clickOnToolbar(mouseLoc))
	{
		handleToolbarClick(mouseLoc);
	}

	else if (clickOnBoard(mouseLoc))
	{
		handleBoardClick(mouseLoc);
	}

}
void LevelController::handleBoardClick(const sf::Vector2f mouseLoc)
{
	if (m_selected != none)
	{
		if (m_selected == belt)
		{
			if (m_board.tryConnecting(mouseLoc)) //tries to connect
			{
				if (m_board.doneConnecting())
					clearMouse();
			}
			else //if failed to connect we return the belt to the toolbar
			{
				clearMouse();
				m_toolbar.addOrIncrease(belt);
			}
			
		}

		else if(m_board.tryToAdd(m_mouseObj))//returns true if managed added obj
			clearMouse();
	}
	else //if(m_selected == none)
		grabFromBoard(m_board.handleClick(mouseLoc, m_selected), mouseLoc);
}

void LevelController::handleToolbarClick(const sf::Vector2f mouseLoc)
{
	if(m_selected == none)
	{
		setSelected(m_toolbar.handleClick(mouseLoc),mouseLoc);
		if (m_selected == play)
		{
			if (tryRunning())//apply gravitiy check if game was won
				m_finished = true;//leave the while and next level
			else
				m_board.resetObjectsPositions();//from before gravity
			clearMouse();
		}
	}
	else
	{	
		if(m_selected == belt)
			m_board.resetConnections();
		
		else if (m_selected == mouseEngine || m_selected == conveyor)
			returnConnectableToToolbar();


		m_toolbar.addOrIncrease(m_selected);
		clearMouse();
	}
}

void LevelController::returnConnectableToToolbar()
{
	if (Connectable* connectable = m_board.isConnectedAndConnectable(m_mouseObj.get()))
	{
		m_board.deleteConnection(connectable);
		m_toolbar.addOrIncrease(belt);
	}
}

void LevelController::setSelected(const Type_t type, const sf::Vector2f mouseLoc)
{
	m_selected = type;
	createOnHandObj(mouseLoc);
	createMouseImg (mouseLoc);
}

void LevelController::whereAmI(const sf::Vector2f mouseLoc) 
{
	if(clickOnToolbar(mouseLoc)) //maybe use set funcs and check if need both ifs
		m_mouseOnToolBr = true;
	if(clickOnBoard(mouseLoc))
		m_mouseOnToolBr = false;
}

void LevelController::grabFromBoard(const std::shared_ptr<GameObj> obj, const sf::Vector2f loc)
{
	if(m_selected != belt)
	{
		m_mouseObj = obj;

		if (obj != nullptr)
			m_selected = obj->getType();
		else
			m_selected = none;
	}
		createMouseImg (loc);

}

void LevelController::clearMouse()
{
	m_selected = none;
	m_mouseObj = nullptr;
}

void LevelController::createOnHandObj(const sf::Vector2f loc)
{
	ObjInfo info;

	if(m_selected == brickWall || m_selected  == pipeWall || m_selected == fancyWall)
		info = wallInitTransforms;
		//also for pipe and fancy

	info._typ = m_selected;
	info._loc = loc;

	m_mouseObj = ObjFactory::create(info,MOVABLE,m_world);
}

void LevelController::createMouseImg(const sf::Vector2f loc)
{
	m_mouseImg = BaseImg(loc, Type_t(m_selected + BUTTON_DELTA_TYPE));
}

void LevelController::updateMouseLoc(const sf::Vector2f loc)
{
	m_mouseImg.setPosition(loc);

	m_board.setMousePos(loc,m_mouseObj);
	
	if(m_mouseObj)
		m_mouseObj->setPosition(loc);

}

bool LevelController::clickOnToolbar(const sf::Vector2f mouseLoc)const
{
	return m_toolbar.clickedOnMe(mouseLoc);
}

bool LevelController::clickOnBoard(const sf::Vector2f mouseLoc)const
{
	return m_board.clickedOnMe(mouseLoc);
}

void LevelController::drawAll(const bool running)
{
	m_window.clear();
	drawStatic(running);

	if (m_selected < play)
	{
		if(m_mouseOnToolBr || m_selected == belt)
		{
			m_mouseImg.draw(m_window);
		}
		else if(m_mouseObj && !m_mouseOnToolBr)
		{
			m_mouseObj->draw(m_window);
		}	
	}
	m_window.display();
}

void LevelController::drawStatic(const bool running)
{
	m_board.draw(m_window, running);
	m_frame.draw(m_window);
	m_toolbar.draw(m_window);
	m_score.draw(m_window);
}

bool LevelController::replaySolution()
{
	BaseImg nextLevelMesseage((PUZZLE_COMPLETE),Type_t::puzzleComplete);
	Button replay(REPLAY_BUTTON,Type_t::replayButton);
	Button advance(ADVANCE_BUTTON,Type_t::advanceButton);
	sf::Text levelScore;
	setText(levelScore);
	sf::Event evnt;

	nextLevelMesseage.draw(m_window);
	advance.draw(m_window);
	replay.draw(m_window);
	m_window.draw(levelScore);
	m_window.display();

	while (m_window.isOpen())
	{

		while (m_window.waitEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				m_window.close();
				return false;

			case sf::Event::MouseButtonReleased:
				auto mouseLoc = m_window.mapPixelToCoords({evnt.mouseButton.x, evnt.mouseButton.y});

				if (advance.mouseOnMe(mouseLoc))
				{
					return false;
				}
				if (replay.mouseOnMe(mouseLoc))
				{
					return true;
				}
				break;
			}
		}
	}
	return true;
}


void LevelController::setText(sf::Text& levelScore)
{
	levelScore.setFont(ResourceManager::instance().getFont(ResourceManager::Font::CourierNew));
	levelScore.setString("Score: " + std::to_string(m_score.get()));
	levelScore.setPosition(LEVEL_SCORE_TEXT_LOC);
	levelScore.setFillColor(sf::Color::Black);
	levelScore.setCharacterSize(CHARATER_SIZE);
	levelScore.setOutlineThickness(CHARATER_OUTLINE_THICKNESS);
}

bool LevelController::tryRunning()
{

	m_score.stop();
	m_board.hideObjButtons();
	while (m_window.isOpen())
	{

		if (checkIfLevelFinished())
			return true;

		m_world.Step(TIMESTEP, VELITER, POSITER);

		drawAll(RUNNING);
		
		b2Body* body = m_world.GetBodyList();
		while(body)
		{
			body->SetAwake(true);
			body = body->GetNext();
		}

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					m_score.play();
					return false;
				}
				break;
			default:
				break;
			}
        }
    }
	return false;//we never get here
}

bool LevelController::checkIfLevelFinished() const
{
	for(auto i = 0; i < m_locConditons.size(); i++)
	{
		if (!m_board.isItemInLoc(m_locConditons[i]))
			return false;
	}

	for(auto x = 0 ; x < m_actConditions.size(); x++)
	{
		if(!m_board.isItemOn(m_actConditions[x]))
			return false;
	}

	return true;
}

void LevelController::drawTinyBoard (sf::RenderTexture& tinyBoard) const
{
	m_board.drawTinyBoard(tinyBoard);
}

void LevelController::saveNewLevel()
{
	m_board.saveLevelToFile();
}
