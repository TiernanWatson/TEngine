// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Loop.h"
#include "Core/IO/FileSystem.h"

using namespace TEngine;

int main()
{
	char* result = FileSystem::Instance().ReadString("D:\\TEngine\\TEngine\\Engine.ini");

	std::cout << result << std::endl;

	std::cout << "strlen: " << strlen(result) << std::endl;

	/*Loop& loop = Loop::Instance();

	loop.Run();*/

	return 0;
}

