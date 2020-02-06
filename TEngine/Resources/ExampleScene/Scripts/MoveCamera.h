#pragma once
#include "../../../World/WorldScript.h"

using namespace TEngine;

class MoveCamera : public WorldScript
{
public:
	void Update(F32 deltaTime) override;
};
