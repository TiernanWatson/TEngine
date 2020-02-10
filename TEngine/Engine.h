#pragma once
#include "Core/PortableTypes.h"
#include "Core/Time/Clock.h"
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
			return *instance_;
		}

	private:
		Engine();
		~Engine();

		static Engine* instance_;

		bool is_running_ = true;
		U8 max_fixed_steps_;			// Maximum number of fixed steps in kOne iteration
		F32 fixed_time_step_;			// Period of time step
		F64 accumulated_time_ = 0.f;  // Time accumulated since last update

		Clock game_clock_;

		StackAllocator systems_stack_;	// Manages memory for all subsystems

		InputSystem* input_system_;
		RENDERER* renderer_;
		WorldSystem* world_system_;
#if _DEBUG
		DebugUIRenderer* debug_renderer_;
#endif

		// For updating the engine at fixed time step
		void FixedUpdate(const F32 time_step);
		// For updating the engine as fast as possible
		void VariableUpdate(const F32 delta_time);

		friend class WindowsOS;
	};
}
