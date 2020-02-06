#pragma once
#include "../Core/PortableTypes.h"
#include "../ECS/EntityManager.h"
#include <vector>

namespace TEngine
{
	class WorldScript;
	struct Camera;

	/**
	* Describes a world_ in the game (i.e. all its entities_, etc..)
	**/
	class World
	{
	public:
		void Awake();
		void Start();
		void Update(F32 deltaTime);
		void FixedUpdate(F32 timeStep);
		void Stop();

		EntityManager& GetEntities();
		U32 GetMainCameraEnt() const;

	private:
		EntityManager entities_;
		std::vector<WorldScript*> scripts_;
		U32 main_cam_ent_;

		friend class WorldSystem;
	};
}
