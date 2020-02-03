#pragma once
#include "Core/PortableTypes.h"
#include "Core/Time/Clock.h"
#include "Window/WindowManager.h"
#include "Input/InputSystem.h"
#include "World/WorldSystem.h"
#include "Core/Memory/StackAllocator.h"

// Removes the need for inheritance and thus vtable speed reduction
#ifdef DIRECTX 
#include "Render/D3D11/D3D11Renderer.h" 
#define RENDERER D3D11Renderer
#elif defined(OPENGL) 
#include "Render/GL/GLRenderer.h"
#define RENDERER GLRenderer
#endif

namespace TEngine
{
	class DebugUIRenderer;

	class Engine
	{
	public:
		void StartUp();
		void Update();
		void ShutDown();

		Clock& GetClock();

		RENDERER& GetRenderer() const;
		WorldSystem& GetWorldSys() const;
		InputSystem& GetInputSys() const;
#ifdef _DEBUG
		DebugUIRenderer& GetDebugRenderer() const;
#endif

		static Engine& Get()
		{
			return *instance;
		}

	private:
		Engine();
		~Engine();

		static Engine* instance;

		bool isRunning = true;
		uint8 maxFixedSteps;			// Maximum number of fixed steps in one iteration
		float32 fixedTimeStep;			// Period of time step
		float64 accumulatedTime = 0.f;  // Time accumulated since last update

		Clock gameClock;

		StackAllocator systemsStack;	// Manages memory for all subsystems

		InputSystem* inputSystem;
		RENDERER* renderer;
		WorldSystem* worldSystem;
#if _DEBUG
		DebugUIRenderer* debugRenderer;
#endif

		// For updating the engine at fixed time step
		void FixedUpdate(const float32 timeStep);
		// For updating the engine as fast as possible
		void VariableUpdate(const float32 deltaTime);

		friend class WindowsOS;
	};
}
