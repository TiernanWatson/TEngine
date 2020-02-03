#include "Engine.h"
#include "Core/Config/Config.h"
#include "Render/D3D11/D3D11Renderer.h"
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
	Engine* Engine::instance = nullptr;

	Engine::Engine() 
		: systemsStack(SYS_STACK_SIZE)
	{
		maxFixedSteps = CONFIG_INT32("Loop", "maxFixedSteps", ConfigVar("8"));
		fixedTimeStep = CONFIG_FLOAT32("Loop", "fixedTimeStep", ConfigVar("0.02"));

		inputSystem = systemsStack.NewOnStack<InputSystem>();
		worldSystem = systemsStack.NewOnStack<WorldSystem>();
		renderer = systemsStack.NewOnStack<RENDERER>();
#ifdef _DEBUG
		debugRenderer = systemsStack.NewOnStack<DebugUIRenderer>();
#endif
		instance = this;
	}

	Engine::~Engine()
	{
		// Subsystems will be freed as stack is deconstructed
	}

	Clock& Engine::GetClock()
	{
		return gameClock;
	}

	RENDERER& Engine::GetRenderer() const
	{
		return *renderer;
	}

	WorldSystem& Engine::GetWorldSys() const
	{
		return *worldSystem;
	}

	InputSystem& Engine::GetInputSys() const
	{
		return *inputSystem;
	}

	DebugUIRenderer& Engine::GetDebugRenderer() const
	{
		return *debugRenderer;
	}

	void Engine::StartUp()
	{
		inputSystem->StartUp();
		worldSystem->StartUp();
		renderer->StartUp();
#ifdef _DEBUG
		debugRenderer->StartUp();
#endif
	}

	void Engine::ShutDown()
	{
#ifdef _DEBUG
		debugRenderer->ShutDown();
#endif
		renderer->ShutDown();
		worldSystem->ShutDown();
		inputSystem->ShutDown();
	}

	void Engine::Update()
	{
		gameClock.Update();

		accumulatedTime += gameClock.GetDeltaTime();

		// If game lags, make sure fixed update catches up
		uint8 stepCount = 0;
		while (accumulatedTime >= fixedTimeStep && stepCount <= maxFixedSteps) 
		{
			accumulatedTime -= fixedTimeStep;
			FixedUpdate(fixedTimeStep);
			stepCount++;
		}

		VariableUpdate((float32)gameClock.GetDeltaTime());
	}

	void Engine::FixedUpdate(const float32 timeStep)
	{
		worldSystem->FixedUpdate(timeStep);
	}

	void Engine::VariableUpdate(const float32 deltaTime)
	{
		inputSystem->Update();
		worldSystem->Update(deltaTime);

		renderer->ClearBuffer(0.f, 0.f, 0.f);
		renderer->Render(deltaTime);
#ifdef _DEBUG
		debugRenderer->VariableUpdate(deltaTime);
#endif
		renderer->Present();
	}
}
