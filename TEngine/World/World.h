#pragma once
#include "../Core/PortableTypes.h"
#include "../ECS/EntityManager.h"
#include <vector>

namespace TEngine
{
	class WorldScript;

	class World
	{
	public:
		void Awake();
		void Start();
		void Update(float32 deltaTime);
		void FixedUpdate(float32 timeStep);
		void Stop();

		EntityManager& GetEntities();

	private:
		EntityManager entities;

		std::vector<WorldScript> scripts;
	};
}
