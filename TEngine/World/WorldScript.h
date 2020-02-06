#pragma once
#include "../Core/PortableTypes.h"

namespace TEngine
{
	class WorldScript
	{
	public:
		virtual void Awake() { };
		virtual void Start() { };
		virtual void Update(F32 delta_time) { };
		virtual void FixedUpdate(F32 time_step) { };
		virtual void Stop() { };

	protected:
		class World* world_;

		friend class WorldSystem;
	};
}
