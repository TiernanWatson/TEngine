// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

int main()
{
	try 
	{
		TEngine::Game::Start();
	}
	catch (std::exception ex) 
	{
		std::cout << "Unhandled exception: " << ex.what() << std::endl;
		return -1;
	}

	return 0;
}
