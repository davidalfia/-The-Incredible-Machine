#include "MyListener.h"
//#include <fstream>
#include <iostream>
#include <box2d/box2d.h>
#include "OverallController.h"


int main()
{   
	try
	{
		MyListener listener;
		auto m_world = std::make_unique<b2World>(b2Vec2(0, 9.81));
		m_world->SetContactListener(&listener);
		OverallController game((*m_world.get()), listener);
		game.run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{ 
		std::cerr << ex.what()<< std::endl;
	} 
}
