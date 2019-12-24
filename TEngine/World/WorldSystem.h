#pragma once
#include "../Core/PortableTypes.h"

namespace TEngine
{
	class World;

	class WorldSystem
	{
	private:
		World* currentWorld;

	public:
		void StartUp();
		void Update(float32 deltaTime);
		void FixedUpdate(float32 timeStep);
		void ShutDown();

		World* GetCurrentWorld() const;
	};
}
