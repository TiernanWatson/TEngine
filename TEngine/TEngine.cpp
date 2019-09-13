// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Core/Config/Config.h"
#include "Loop.h"
#include "Core/IO/FileSystem.h"

using namespace TEngine;

int main()
{
	Loop& loop = Loop::Instance();

	loop.Run();

	return 0;
}

