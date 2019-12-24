#include "WorldSystem.h"
#include "World.h"
#include "WorldScript.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"

namespace TEngine
{
	void WorldSystem::StartUp()
	{
		currentWorld = new World();
		EntityManager& e = currentWorld->GetEntities();
		uint32 id = e.NewEntityWith<Transform, MeshComponent>();

		std::vector<Vertex> verts{ Vertex{Vector3(-0.5f, -0.5f, 0.0f)}, Vertex{Vector3(0.0f, 0.5f, 0.0f)}, Vertex{Vector3(0.5f, -0.5f, 0.0f)} };
		std::vector<uint32> indices{ 0, 1, 2 };
		std::vector<Texture> texts;
		Mesh* mesh = new Mesh(verts, indices, texts);

		MeshComponent& m = e.GetComponent<MeshComponent>(id);
		m.mesh = mesh;
	}

	void WorldSystem::Update(float32 deltaTime)
	{
		if (currentWorld == nullptr) return;

		currentWorld->Update(deltaTime);
	}

	void WorldSystem::FixedUpdate(float32 timeStep)
	{
		if (currentWorld == nullptr) return;

		currentWorld->FixedUpdate(timeStep);
	}

	void WorldSystem::ShutDown()
	{
		delete currentWorld;
	}

	World* WorldSystem::GetCurrentWorld() const
	{
		return currentWorld;
	}
}
