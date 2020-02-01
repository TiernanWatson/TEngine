#include "Engine.h"
#include "Core/Config/Config.h"
#include "Render/D3D11/D3D11Renderer.h"
#include "Helpers/DebugSystem.h"

//#undef _DEBUG

namespace TEngine
{
	Engine* Engine::instance = nullptr;

	Engine::Engine() 
		: systemsStack(sizeof(WindowManager) + sizeof(InputSystem)
			+ sizeof(WorldSystem) + sizeof(D3D11Renderer))
	{
		windowManager = systemsStack.NewOnStack<WindowManager>();
		inputSystem = systemsStack.NewOnStack<InputSystem>();
		worldSystem = systemsStack.NewOnStack<WorldSystem>();
		renderer = systemsStack.NewOnStack<D3D11Renderer>();
#ifdef _DEBUG
		debugSystem = new DebugSystem();
#endif
		instance = this;
	}

	Engine::~Engine()
	{
		// Subsystems will be freed as stack is deconstructed
#ifdef _DEBUG
		delete debugSystem;
#endif
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

	void Engine::StartUp()
	{
		//Config::Instance().LoadFrom("D:\\TEngine\\TEngine\\Engine.ini");
		//windowManager->StartUp();
		//inputSystem->StartUp(windowManager->GetWindow());
		worldSystem->StartUp();
		//renderer->StartUp(windowManager->GetWindow(), worldSystem);
		renderer->StartUp();
#ifdef _DEBUG
		//debugSystem->StartUp(windowManager->GetWindow());
#endif
	}

	void Engine::ShutDown()
	{
#ifdef _DEBUG
		//debugSystem->ShutDown();
#endif
		renderer->ShutDown();
		worldSystem->ShutDown();
		//inputSystem->ShutDown();
		//windowManager->ShutDown();
	}

	/**
	* Handles the calling of fixed and variable update
	**/
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

	/**
	* Updates at a fixed time step, defaulted to 50Hz
	**/
	void Engine::FixedUpdate(const float32 timeStep)
	{
		worldSystem->FixedUpdate(timeStep);
#ifdef _DEBUG
		//debugSystem->FixedUpdate(timeStep);
#endif
	}

	/**
	* Updates as fast as possible, not fixed
	**/
	void Engine::VariableUpdate(const float32 deltaTime)
	{
		//inputSystem->Update();
		worldSystem->Update(deltaTime);

		renderer->ClearBuffer(0.f, 0.f, 0.f);
		renderer->Render(deltaTime);
		renderer->DrawTriangle();
		renderer->Present();

#ifdef _DEBUG
		//debugSystem->VariableUpdate(deltaTime);
#endif
		//windowManager->Update(deltaTime);
	}
}
