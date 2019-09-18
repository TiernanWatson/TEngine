#pragma once
#include "../Core/PortableTypes.h"

namespace TEngine
{
	/**
	* Base for systems in the ECS model
	**/
	class System
	{
	public:
		virtual void Init() {};

		virtual void VariableUpdate(float32 deltaTime) {};

		virtual void FixedUpdate(float32 timeStep);

		virtual void ShutDown();
	};
}
