#pragma once
#include "../Core/PortableTypes.h"

namespace TEngine
{
	class World;

	class WorldSystem
	{
	public:
		void StartUp();
		void Update(F32 delta_time);
		void FixedUpdate(F32 time_step);
		void ShutDown();

		World* GetCurrentWorld() const;

	private:
		World* current_world_;
	};
}
