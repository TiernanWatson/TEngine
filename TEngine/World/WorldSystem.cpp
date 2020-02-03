#include "WorldSystem.h"
#include "World.h"
#include "WorldScript.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/Camera.h"
#include "../ECS/Components/PointLight.h"
#include "../Resources/Types/Model.h"
#include "../Resources/ResourceLoader.h"
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

		// Crysuit
		//Model& model = ResourceLoader::Instance().GetModel("D:\\3D Models\\nanosuit\\nanosuit.obj");
		Model& model = ResourceLoader::Instance().GetModel("D:\\3D Models\\muro\\muro.obj");
		for (uint32 i = 0; i < 10; i++)
		{
			/*for (uint32 j = 0; j < 5; j++)
			{*/
				for (Mesh* m : model.GetMeshes())
				{
					uint32 mId = e.NewEntityWith<Transform, MeshComponent>();

					Transform& t = e.GetComponent<Transform>(mId);
					Vector3 dir = (i % 2 == 0) ? Vector3::right : Vector3::left;
					t.position = Vector3::down * 1.75f + dir * 2.f /** (float32)j*/ + Vector3::forward * 2.f * (float32)i;
					t.scale = Vector3::one * 0.02f;

					MeshComponent& mc = e.GetComponent<MeshComponent>(mId);
					mc.mesh = m;
				}
			//}
		}

		// Main Camera
		currentWorld->mainCameraEntity = e.NewEntityWith<Transform, Camera>();

		Transform& t2 = e.GetComponent<Transform>(currentWorld->mainCameraEntity);
		t2.scale = Vector3::one;
		t2.position = Vector3::forward * 10.f;
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
