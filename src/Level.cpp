#include "Level.h"


Level::Level()
{
}

Level::Level(const bool)
{
for (int i = balloon; i < play; ++i)
	{
		addToolbarObj(Type_t(i), INFINITE_AMOUNT);
	}
	addCondLoc(-1, sf::Vector2f(0,0), sf::Vector2f(0,0));//adding impossible condition so level doesnt finishf
}

void Level::addBoardObj(const ObjInfo& obj)
{
	m_initial.push_back(obj);
}

void Level::addToolbarObj (const Type_t obj, const int amount)
{
	m_toolbar.push_back(std::pair(obj, amount));
}

void Level::addCondLoc (const int id, const sf::Vector2f loc, const sf::Vector2f size)
{
	m_locConditons.push_back(std::pair(id,std::pair(loc, size)));
}

void Level::addCondAct (const int id)
{
	m_actConditions.push_back(id);
}

void Level::addName(const std::string& name)
{
	m_name = name;
}

void Level::addLevelGoal(const std::string& levelGoal)
{
	m_levelGoal = levelGoal;
}
