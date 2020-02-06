#include "World.h"
#include "WorldScript.h"

namespace TEngine
{
	void World::Awake()
	{
		for (WorldScript* s : scripts_)
			s->Awake();
	}

	void World::Start()
	{
		for (WorldScript* s : scripts_)
			s->Start();
	}

	void World::Update(F32 delta_time)
	{
		for (WorldScript* s : scripts_)
			s->Update(delta_time);
	}

	void World::FixedUpdate(F32 time_step)
	{
		for (WorldScript* s : scripts_)
			s->FixedUpdate(time_step);
	}

	void World::Stop()
	{
		for (WorldScript* s : scripts_)
			s->Stop();
	}

	U32 World::GetMainCameraEnt() const
	{
		return main_cam_ent_;
	}

	EntityManager& World::GetEntities() 
	{
		return entities_;
	}
}
