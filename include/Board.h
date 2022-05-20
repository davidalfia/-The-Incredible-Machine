#pragma once

#include "Level.h"
#include "Balloon.h"
#include "BaseBall.h"
#include "Basketball.h"
#include "BowlingBall.h"
#include "BrickWall.h"
#include "Collisions.h"
#include "FileHandler.h"
#include "Conveyor.h"
#include "MouseEngine.h"
#include "Connections.h"
#include "Connectable.h"



using conditionToWinLoc = std::pair<int, std::pair<sf::Vector2f, sf::Vector2f>>; 

class Board
{
public:

	Board(const boardObjects&, b2World& );
	void setBoard(const boardObjects& , b2World&);
	void draw(sf::RenderWindow&, const bool);
	void drawTinyBoard (sf::RenderTexture&) const;
	bool tryToAdd(const std::shared_ptr<GameObj>); 
	std::shared_ptr<GameObj> handleClick(const sf::Vector2f, Type_t&);
	void resetObjectsPositions();

	bool clickedOnMe(const sf::Vector2f) const;
	bool checkCollison(const GameObj& obj2, const GameObj& obj1) const;
	bool collides(const GameObj&) const;
	bool isItemInLoc(const conditionToWinLoc) const;
	bool isItemOn(const conditionToWinAct cond) const;

	void saveLevelToFile() const;

	void checkMouseOver(const sf::Vector2f ,const std::shared_ptr<GameObj>);
	void hideObjButtons() { setEveryoneElseFalse(NO_ONE); }

	GameObj* getObjWithId(const int) const;

	Collisions getCollisionObj() const { return m_collision;}

	bool tryConnecting(const sf::Vector2f);
	bool doneConnecting();
	void resetConnections() { m_connections.reset(); }
	void deleteConnection(Connectable* obj) { m_connections.deleteConnection(obj); }
	Connectable* isConnectedAndConnectable(GameObj* obj) const { return m_connections.isConnectedAndConnectable(obj); }
	void setMousePos(const sf::Vector2f, const std::shared_ptr<GameObj>);

private:


	void updateImgLocs();
	void setEveryoneElseFalse(const int);
	std::vector< ObjInfo> getObjInfo() const;
	std::shared_ptr<GameObj> findConnectable(const sf::Vector2f) const; 

	std::vector <std::shared_ptr<GameObj>> m_objects;
	Connections m_connections;
	sf::RectangleShape m_background;
	Collisions m_collision; 

};
