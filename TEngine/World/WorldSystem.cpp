#include "WorldSystem.h"
#include "World.h"
#include "WorldScript.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/Camera.h"
#include "../Render/Material/Material.h"
#include "../Core/IO/FileSystem.h"

namespace TEngine
{
	void WorldSystem::StartUp()
	{
		//
		// Temporarily sets up a test world until serialization etc is done!
		//

		currentWorld = new World();
		EntityManager& e = currentWorld->GetEntities();
		uint32 id = e.NewEntityWith<Transform, MeshComponent>();

		const char* vertSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Resources\\Shaders\\Vertex\\3default.vert");

		const char* fragSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Resources\\Shaders\\Fragment\\3default.frag");

		Shader* s = new Shader(vertSource, fragSource);

		delete vertSource, fragSource;

		std::vector<Vertex> verts{ Vertex{Vector3(-1.5f, -1.5f, 0.0f)}, Vertex{Vector3(0.0f, 1.5f, 0.0f)}, Vertex{Vector3(1.5f, -1.5f, 0.0f)} };
		std::vector<uint32> indices{ 0, 1, 2 };
		std::vector<Texture> texts;
		Mesh* mesh = new Mesh(verts, indices, texts);
		Material* mat = new Material(nullptr, s);
		mesh->materials.push_back(mat);

		MeshComponent& m = e.GetComponent<MeshComponent>(id);
		m.mesh = mesh;

		Transform& t = e.GetComponent<Transform>(id);
		t.scale.x = 1.f;
		t.scale.y = 1.f;
		t.scale.z = 1.f;

		currentWorld->mainCameraEntity = e.NewEntityWith<Transform, Camera>();

		Transform& t2 = e.GetComponent<Transform>(currentWorld->mainCameraEntity);
		t2.scale.x = 1.f;
		t2.scale.y = 1.f;
		t2.scale.z = 1.f;
		t2.position = Vector3::back * 5.f;
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
