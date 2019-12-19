// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include "Core/Math/TMath.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4.h"

using namespace TEngine;

int main()
{
	TEngine::Game::Start();

	TEngine::Matrix4 view = Matrix4::ModelToWorld(Vector3::forward * 10.f, Vector3::one, Vector3(0.f, TMath::PI, 0.f)).Inverse();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << view.m[i][j] << ", ";
		}
		std::cout << std::endl;
	}

	return 0;
}

