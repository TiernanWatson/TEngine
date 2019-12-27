#include "MoveCamera.h"
#include "../../../Helpers/Debug.h"
#include "../../../World/World.h"
#include "../../../ECS/Components/Transform.h"
#include "../../../ECS/EntityManager.h"
#include "../../../Input/Input.h"

void MoveCamera::Update(float32 deltaTime)
{
	uint32 camId = world->GetMainCameraEnt();
	Transform& t = world->GetEntities().GetComponent<Transform>(camId);
	
	float32 forward = Input::GetKey(KeyCode::W) ? 1.f : 0.f;
	forward = Input::GetKey(KeyCode::S) ? -1.f : forward;
	float32 right = Input::GetKey(KeyCode::D) ? 1.f : 0.f;
	right = Input::GetKey(KeyCode::A) ? -1.f : right;

	Vector3 move = Vector3::forward * forward + Vector3::right * right;
	t.position += move * deltaTime;
}
