#include "Board.h"
#include <vector>

using boardObjects = std::vector<ObjInfo>;

Board::Board(const boardObjects& objects, b2World& world)
	:m_background(sf::Vector2f(BOARD_W, BOARD_H))
{
	setBoard(objects, world);
	m_background.setPosition(sf::Vector2f(FRAME_SIZE, FRAME_SIZE));
	m_background.setFillColor(sf::Color(18, 160, 159)); //background color
}

void Board::setBoard(const boardObjects& objects, b2World& world)
{

	for (auto i = 0; i < objects.size(); i++)
	{
		m_objects.push_back(ObjFactory::create(objects[i], UNMOVABLE, world));
		if(i == 0)
			m_objects[i]->setIdZero();
	}

}

GameObj* Board::getObjWithId(const int obj) const
{
	for (auto& i : m_objects)
	{
		if (i->getID() == obj)
			return i.get();
	}
	return nullptr;//never gets here
}

void Board::draw(sf::RenderWindow& window, const bool running)
{
	window.draw(m_background);
	if (running)
		updateImgLocs();

	for (auto& obj : m_objects)
		obj->draw(window);

	m_connections.draw(window);
}

void Board::updateImgLocs()
{
	for (auto& obj : m_objects)
		obj->updateLoc();

	m_connections.checkConnections();
}

bool Board::tryToAdd(const std::shared_ptr<GameObj> current)
{
	if (current && !collides(*current.get()))
	{
		current->setInitialLoc();
		m_objects.push_back(current);
		return true;
	}
	return false;
}


bool Board::collides(const GameObj& current) const
{
	for (auto& i : m_objects)
	{
		if (checkCollison((*i.get()), current) && current.getID() != i->getID())
		{
			return true;
		}
	}
	return false;
}

bool Board::checkCollison(const GameObj& obj2, const GameObj& obj1) const
{
	if(obj1.pixelPerfectColides(obj2))
		return true;

	return false;
}

std::shared_ptr<GameObj> Board::handleClick(const sf::Vector2f mouseLoc, Type_t& selected)
{
	std::shared_ptr<GameObj> obj = nullptr;
	Resizable* resizableObj = nullptr;
	for (auto i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->mouseOnMe(mouseLoc))
		{

			Type_t clicked = m_objects[i]->handleClick(mouseLoc);
			if (clicked == connectButton)
			{
				if (Connectable* connectable = isConnectedAndConnectable(m_objects[i].get()))
				{
					selected = belt;
					m_connections.unplug(connectable);
				}
			}

			else if(m_objects[i]->isMovable())
			{
				if (clicked == rotateButton || clicked == resizeButton) //means it resized or rotated
				{
					resizableObj = static_cast <Resizable*> (m_objects[i].get());
					if (collides(*resizableObj))
						resizableObj->fixLastChange(clicked);
				}

				else
				{
					obj = m_objects[i];
					m_objects.erase(m_objects.begin() + i);
				}

			}
			break;
		}
	}
	return obj;
}

std::shared_ptr<GameObj> Board::findConnectable(const sf::Vector2f mouseLoc) const
{

	for (auto i = 0; i < m_objects.size(); i++)
	{
		if (connectButton == m_objects[i]->handleClick(mouseLoc))
			return m_objects[i];
	}
	return nullptr;
}

void Board::resetObjectsPositions()
{
	for (auto& obj : m_objects)
		obj->backToStartingPlace();
}

bool Board::isItemInLoc(const conditionToWinLoc cond) const
{
	sf::RectangleShape rect(cond.second.first);
	rect.setPosition(cond.second.second);

	for (auto& obj : m_objects)
		if (obj->getID() == cond.first)
			if (obj->getGlobalBounds().intersects(rect.getGlobalBounds()))
				return true;

	return false;
}

bool Board::isItemOn(const conditionToWinAct cond) const
{
	for (auto& obj : m_objects)
		if (obj->getID() == cond)
			if(obj->isOn())
				return true;
	
	return false; 
}

void Board::saveLevelToFile() const
{
	auto file = FileHandler(ResourceManager::instance().getLevelPath(), SAVE);
	file.saveNewLevel(getObjInfo());
}


std::vector<ObjInfo> Board::getObjInfo() const
{
	auto info = std::vector<ObjInfo>();
	for (auto& obj : m_objects)
		info.push_back(obj->getInfo());
	return info;
}

void Board::checkMouseOver(const sf::Vector2f loc, const std::shared_ptr<GameObj>  mouseImg)
{
	bool paintRed = false;

	for (auto& obj : m_objects)
	{
		if (mouseImg && checkCollison(*obj.get(), *mouseImg.get()))
			paintRed = true;
			
		if (obj->mouseOnMe(loc))
		{
			if (obj->isMovable())
			{
				obj->setMouse(true);
				setEveryoneElseFalse(obj->getID());
			}

		}
	}
	if(mouseImg)
	{
		if (paintRed)
			mouseImg->setColor(sf::Color::Red);
		else
		{
			mouseImg->setColor(sf::Color::White);
		}
	}
	

}

void Board::setEveryoneElseFalse(const int except)
{
	for (auto& obj : m_objects)
		if (obj->getID() != except)
			obj->setMouse(false);
}

bool Board::clickedOnMe(const sf::Vector2f loc) const
{
	if (m_background.getGlobalBounds().contains(loc))
		return true;

	return false;
}


void Board::drawTinyBoard(sf::RenderTexture& tinyBoard) const
{
	tinyBoard.clear(sf::Color(18, 160, 159));

	for (auto& obj : m_objects)
		obj->drawSmall(tinyBoard);

	tinyBoard.display();
}

bool Board::tryConnecting(const sf::Vector2f mouseLoc)
{
	std::shared_ptr<GameObj> obj = findConnectable(mouseLoc);

	if (obj.get())
		return (m_connections.tryConnecting(obj));

	m_connections.reset();
	return false;
}

bool Board::doneConnecting()
{
	return m_connections.doneConnecting();
}


void Board::setMousePos(const sf::Vector2f mouseLoc, const std::shared_ptr<GameObj> mouseImg)
{
	checkMouseOver(mouseLoc, mouseImg);

	m_connections.setMousePos(mouseLoc);
}
