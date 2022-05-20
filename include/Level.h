#pragma once

#include "globals.h"
 


using toolbarPair 	 = std::pair<Type_t, int>;

using conditionToWinLoc = std::pair<int, std::pair<sf::Vector2f, sf::Vector2f>>; //id of object that needs to be in the square with sqSize, sqLoc
using conditionToWinAct = int;	//id that needs to be on

using boardObjects   = std::vector<ObjInfo>;
using toolbarObjects = std::vector<toolbarPair>;

using conditionsLocs = std::vector<conditionToWinLoc>;
using conditionsActs = std::vector<conditionToWinAct>;
 
class Level
{
public:
	Level(); 
	Level(const bool);

	void addBoardObj(const ObjInfo&);
	void addToolbarObj(const Type_t, const int);

	void addCondLoc (const int, const sf::Vector2f, const sf::Vector2f);
	void addCondAct (const int);

	void addName(const std::string&);
	void addLevelGoal(const std::string&);

	const std::string& getLevelName() const { return m_name; }
	const std::string& getLevelGoal() const { return m_levelGoal; }

	const boardObjects&   getBoardObjs() const { return m_initial; }
	const toolbarObjects& getToolbarObjs() const {return m_toolbar; }

	const conditionsLocs& getLocConditions() const { return m_locConditons; }
	const conditionsActs& getActConditions() const { return m_actConditions; }

private:

	boardObjects   m_initial;
	toolbarObjects m_toolbar;

	conditionsLocs m_locConditons;
	conditionsActs m_actConditions;

	std::string m_name;
	std::string m_levelGoal;
};
