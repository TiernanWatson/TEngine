#pragma once
#include "../Core/PortableTypes.h"

namespace TEngine
{
	class WorldScript
	{
	public:
		virtual void Awake();
		virtual void Start();
		virtual void Update(float32 deltaTime);
		virtual void FixedUpdate(float32 timeStep);
		virtual void Stop();
	};
}
