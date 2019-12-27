#include "WorldSystem.h"
#include "World.h"
#include "WorldScript.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/Camera.h"
#include "../ECS/Components/PointLight.h"
#include "../Render/Material/Material.h"
#include "../Render/Models/Model.h"
#include "../Render/Material/Shaders.h"
#include "../Core/IO/FileSystem.h"
#include "../Helpers/Debug.h"
#include "../Resources/ExampleScene/Scripts/MoveCamera.h"

namespace TEngine
{
	void WorldSystem::StartUp()
	{
		//
		// Temporarily sets up a test world until serialization etc is done!
		//

		currentWorld = new World();
		EntityManager& e = currentWorld->GetEntities();

		const char* vertSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Resources\\Shaders\\Vertex\\3default.vert");

		const char* fragSource = FileSystem::Instance().ReadString(
			"D:\\TEngine\\TEngine\\Resources\\Shaders\\Fragment\\3default.frag");

		uint32 s = Shaders::CreateShader("default", vertSource, fragSource);

		delete vertSource, fragSource;

		// Crysuit
		Model* model = new Model("D:\\3D Models\\nanosuit\\nanosuit.obj");
		for (Mesh& m : model->meshes)
		{
			Material* mat = new Material(nullptr, s);
			m.materials.push_back(mat);

			uint32 mId = e.NewEntityWith<Transform, MeshComponent>();

			Transform& t = e.GetComponent<Transform>(mId);
			t.position = Vector3::down * 1.5f;
			t.scale = Vector3::one * 0.2f;

			MeshComponent& mc = e.GetComponent<MeshComponent>(mId);
			mc.mesh = &m;
		}

		// Cube
		/*
		uint32 id = e.NewEntityWith<Transform, MeshComponent>();
		std::vector<Vertex> verts{   
			Vertex{Vector3(-0.5f, -0.5f, 0.5f)},
			Vertex{Vector3(0.5f, -0.5f, 0.5f)},
			Vertex{Vector3(0.5f, 0.5f, 0.5f)},
			Vertex{Vector3(-0.5f, 0.5f, 0.5f)},
			Vertex{Vector3(-0.5f, -0.5f, -0.5f)},
			Vertex{Vector3(0.5f, -0.5f, -0.5f)},
			Vertex{Vector3(0.5f, 0.5f, -0.5f)},
			Vertex{Vector3(-0.5f, 0.5f, -0.5f)}
		};
		std::vector<uint32> indices{
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};
		std::vector<Vector3> normals{
			// front
			Vector3::back,
			Vector3::back,
			Vector3::back,
			Vector3::back,
			// right
			Vector3::right,
			Vector3::right,
			Vector3::right,
			Vector3::right,
			// back
			Vector3::forward,
			Vector3::forward,
			Vector3::forward,
			Vector3::forward,
			// left
			Vector3::left,
			Vector3::left,
			Vector3::left,
			Vector3::left,
			// bottom
			Vector3::down,
			Vector3::down,
			Vector3::down,
			Vector3::down,
			// top
			Vector3::up,
			Vector3::up,
			Vector3::up,
			Vector3::up
		};
		std::vector<Texture> texts;
		Mesh* mesh = new Mesh(verts, indices, texts);
		Material* mat = new Material(nullptr, s);
		mesh->materials.push_back(mat);
		//mesh->normals = normals;

		MeshComponent& m = e.GetComponent<MeshComponent>(id);
		m.mesh = mesh;

		Transform& t = e.GetComponent<Transform>(id);
		t.scale = Vector3::one;*/

		// Main Camera
		currentWorld->mainCameraEntity = e.NewEntityWith<Transform, Camera>();

		Transform& t2 = e.GetComponent<Transform>(currentWorld->mainCameraEntity);
		t2.scale = Vector3::one;
		t2.position = Vector3::back * 4.f;
		//t2.rotation = Vector3{ 0.3f, -0.3f, 0.f };

		MoveCamera* moveCam = new MoveCamera();
		currentWorld->scripts.push_back(moveCam);
		((WorldScript*)moveCam)->world = currentWorld;

		// Point Light
		/*uint32 lid = e.NewEntityWith<Transform, PointLight>();

		Transform& t3 = e.GetComponent<Transform>(lid);
		t3.position = Vector3::up * 2.f + Vector3::back * 1.f;
		t3.scale = Vector3::one;

		PointLight& p = e.GetComponent<PointLight>(lid);
		p.color = Vector3::one;
		p.intensity = 1.f;*/
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
