#include "MoveCamera.h"
#include "../../../Helpers/Debug.h"
#include "../../../World/World.h"
#include "../../../ECS/Components/Transform.h"
#include "../../../ECS/EntityManager.h"
#include "../../../Input/Input.h"

#include "../../../Platform/Windows/WinHeader.h"

void MoveCamera::Update(F32 deltaTime)
{
	U32 camId = world_->GetMainCameraEnt();
	Transform& t = world_->GetEntities().GetComponent<Transform>(camId);

	F32 forward = Input::GetKey(KeyCode::W) ? -1.f : 0.f;
	forward = Input::GetKey(KeyCode::S) ? 1.f : forward;
	F32 right = Input::GetKey(KeyCode::D) ? 1.f : 0.f;
	right = Input::GetKey(KeyCode::A) ? -1.f : right;

	Vector3 move = Vector3::kForward * forward + Vector3::kRight * right;
	t.position += move * deltaTime;
}
