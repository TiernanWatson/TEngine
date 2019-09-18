#pragma once
#include "../Core/PortableTypes.h"
#include "Components/Transform.h"

namespace TEngine
{
	/**
	* An entity in the game world, part of the ECS system
	**/
	class Entity
	{
	public:
		Entity();

	private:
		uint32 id;

		Transform transform;

		static uint32 currentId; // Last used ID
	};
}
