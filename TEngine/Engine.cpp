#include "Engine.h"
#include "Core/Config/Config.h"
#include "Render/D3D11/D3D11Renderer.h"
#include "Core/Memory/Memory.h"
#ifdef _DEBUG
#include "Helpers/DebugUIRenderer.h"
#endif

#ifdef _DEBUG
#define SYS_STACK_SIZE sizeof(InputSystem) + sizeof(WorldSystem) + sizeof(RENDERER) + sizeof(DebugUIRenderer)
#else
#define SYS_STACK_SIZE sizeof(InputSystem) + sizeof(WorldSystem) + sizeof(RENDERER)
#endif

namespace TEngine
{
	Engine* Engine::instance_ = nullptr;

	Engine::Engine() 
		: systems_stack_(SYS_STACK_SIZE, Memory::Malloc)
	{
		max_fixed_steps_ = CONFIG_INT32("Loop", "max_fixed_steps_", ConfigVar("8"));
		fixed_time_step_ = CONFIG_FLOAT32("Loop", "fixed_time_step_", ConfigVar("0.02"));

		input_system_ = systems_stack_.NewOnStack<InputSystem>();
		world_system_ = systems_stack_.NewOnStack<WorldSystem>();
		renderer_ = systems_stack_.NewOnStack<RENDERER>();
#ifdef _DEBUG
		debug_renderer_ = systems_stack_.NewOnStack<DebugUIRenderer>();
#endif
		instance_ = this;
	}

	Engine::~Engine()
	{
		// Subsystems will be freed_ as stack is deconstructed
	}

	Clock& Engine::GetClock()
	{
		return game_clock_;
	}

	RENDERER& Engine::GetRenderer() const
	{
		return *renderer_;
	}

	WorldSystem& Engine::GetWorldSys() const
	{
		return *world_system_;
	}

	InputSystem& Engine::GetInputSys() const
	{
		return *input_system_;
	}

	DebugUIRenderer& Engine::GetDebugRenderer() const
	{
		return *debug_renderer_;
	}

	void Engine::StartUp()
	{
		input_system_->StartUp();
		world_system_->StartUp();
		renderer_->StartUp();
#ifdef _DEBUG
		debug_renderer_->StartUp();
#endif
	}

	void Engine::ShutDown()
	{
#ifdef _DEBUG
		debug_renderer_->ShutDown();
#endif
		renderer_->ShutDown();
		world_system_->ShutDown();
		input_system_->ShutDown();
	}

	void Engine::Update()
	{
		game_clock_.Update();

		accumulated_time_ += game_clock_.GetDeltaTime();

		U8 step_count = 0;
		while (accumulated_time_ >= fixed_time_step_ && step_count <= max_fixed_steps_) 
		{
			accumulated_time_ -= fixed_time_step_;
			FixedUpdate(fixed_time_step_);
			step_count++;
		}

		VariableUpdate((F32)game_clock_.GetDeltaTime());
	}

	void Engine::FixedUpdate(const F32 time_step)
	{
		world_system_->FixedUpdate(time_step);
	}

	void Engine::VariableUpdate(const F32 delta_time)
	{
		input_system_->Update();
		world_system_->Update(delta_time);

		renderer_->ClearBuffer(0.f, 0.f, 0.f);
		renderer_->Render(delta_time);
#ifdef _DEBUG
		debug_renderer_->VariableUpdate(delta_time);
#endif
		renderer_->Present();
	}
}
