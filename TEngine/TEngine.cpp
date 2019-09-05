// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Core/PortableTypes.h"
#include "Core/Memory/StackAllocator.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4.h"
#include "Core/Math/TMath.h"

using namespace TEngine;

int main()
{
	std::cout << "The constants available: " << std::endl;
	std::cout << "PI: " << TMath::PI << std::endl;
	std::cout << "PI_2: " << TMath::PI_2 << std::endl;
	std::cout << "PI_4: " << TMath::PI_4 << std::endl;
	std::cout << "EPSILON: " << TMath::EPSILON << std::endl;
	std::cout << "RAD2DEG: " << TMath::RAD2DEG << std::endl;
	std::cout << "DEG2RAD: " << TMath::DEG2RAD << std::endl;
	
	std::cout << "Float size is: " << sizeof(float32) << " and Matrix4 is: " << sizeof(Matrix4) << std::endl;
}

