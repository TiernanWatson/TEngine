// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "Core/PortableTypes.h"
#include "Core/Memory/StackAllocator.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4.h"
#include "Core/Math/TMath.h"

using namespace TEngine;

int main()
{
	Vector3 v1(1.f, 1.f, 1.f);
	Vector3 v2 = v1;

	v2.x = 2.f;

	std::cout << "V1: " << v1.ToString() << " V2: " << v2.ToString() << std::endl;
}

