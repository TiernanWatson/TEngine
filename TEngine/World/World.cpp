#include "World.h"
#include "WorldScript.h"

namespace TEngine
{
	void World::Awake()
	{
		for (WorldScript* s : scripts)
			s->Awake();
	}

	void World::Start()
	{
		for (WorldScript* s : scripts)
			s->Start();
	}

	void World::Update(float32 deltaTime)
	{
		for (WorldScript* s : scripts)
			s->Update(deltaTime);
	}

	void World::FixedUpdate(float32 timeStep)
	{
		for (WorldScript* s : scripts)
			s->FixedUpdate(timeStep);
	}

	void World::Stop()
	{
		for (WorldScript* s : scripts)
			s->Stop();
	}

	uint32 World::GetMainCameraEnt() const
	{
		return mainCameraEntity;
	}

	EntityManager& World::GetEntities() 
	{
		return entities;
	}
}
