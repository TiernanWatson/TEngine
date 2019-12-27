#pragma once
#include "../Core/PortableTypes.h"
#include "../ECS/EntityManager.h"
#include <vector>

namespace TEngine
{
	class WorldScript;
	struct Camera;

	/**
	* Describes a world in the game (i.e. all its entities, etc..)
	**/
	class World
	{
	public:
		void Awake();
		void Start();
		void Update(float32 deltaTime);
		void FixedUpdate(float32 timeStep);
		void Stop();

		EntityManager& GetEntities();
		uint32 GetMainCameraEnt() const;

	private:
		EntityManager entities;
		std::vector<WorldScript*> scripts;
		uint32 mainCameraEntity;

		friend class WorldSystem;
	};
}
