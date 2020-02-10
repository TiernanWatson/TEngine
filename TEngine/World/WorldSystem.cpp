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
		// Temporarily sets kUp a test world_ until serialization etc is done!
		//
		current_world_ = new World();
		EntityManager& e = current_world_->GetEntities();

		// Crysuit
		//Model& model = ResourceLoader::Instance().GetModel("D:\\3D Models\\nanosuit\\nanosuit.obj");
		Model& model = ResourceLoader::Instance().GetModel("D:\\3D Models\\muro\\muro.obj");
		for (U32 i = 0; i < 10; i++)
		{
			for (Mesh* m : model.GetMeshes())
			{
				U32 mId = e.NewEntityWith<Transform, MeshComponent>();

				Transform& t = e.GetComponent<Transform>(mId);
				Vector3 dir = (i % 2 == 0) ? Vector3::kRight : Vector3::kLeft;
				t.position = Vector3::kDown * 1.75f + dir * 2.f + Vector3::kForward * 2.f * (F32)i;
				t.scale = Vector3::kOne * 0.02f;

				MeshComponent& mc = e.GetComponent<MeshComponent>(mId);
				mc.mesh = m;
			}
		}

		// Main Camera
		current_world_->main_cam_ent_ = e.NewEntityWith<Transform, Camera>();

		Transform& t2 = e.GetComponent<Transform>(current_world_->main_cam_ent_);
		t2.scale = Vector3::kOne;
		t2.position = Vector3::kForward * 10.f;
		//t2.rotation = Vector3{ 0.3f, -0.3f, 0.f };

		MoveCamera* move_cam = new MoveCamera();
		current_world_->scripts_.push_back(move_cam);
		((WorldScript*)move_cam)->world_ = current_world_;

		// Point Light
		/*U32 lid = e.NewEntityWith<Transform, PointLight>();

		Transform& t3 = e.GetComponent<Transform>(lid);
		t3.position = Vector3::kUp * 2.f + Vector3::kBack * 1.f;
		t3.scale = Vector3::kOne;

		PointLight& p = e.GetComponent<PointLight>(lid);
		p.color = Vector3::kOne;
		p.intensity = 1.f;*/
	}

	void WorldSystem::Update(F32 delta_time)
	{
		if (current_world_ == nullptr) return;

		current_world_->Update(delta_time);
	}

	void WorldSystem::FixedUpdate(F32 time_step)
	{
		if (current_world_ == nullptr) return;

		current_world_->FixedUpdate(time_step);
	}

	void WorldSystem::ShutDown()
	{
		delete current_world_;
	}

	World* WorldSystem::GetCurrentWorld() const
	{
		return current_world_;
	}
}
