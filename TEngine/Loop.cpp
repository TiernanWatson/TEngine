#include "Loop.h"
#include "Core/Config/Config.h"
#include "Helpers/DebugSystem.h"

//#undef _DEBUG

namespace TEngine
{
	Loop::Loop() 
		: systemsStack(sizeof(WindowManager) + sizeof(InputSystem)
			+ sizeof(WorldSystem) + sizeof(RenderSystem))
	{
		windowManager = systemsStack.NewOnStack<WindowManager>();
		inputSystem = systemsStack.NewOnStack<InputSystem>();
		worldSystem = systemsStack.NewOnStack<WorldSystem>();
		renderSystem = systemsStack.NewOnStack<RenderSystem>();
#ifdef _DEBUG
		debugSystem = new DebugSystem();
#endif
	}

	Loop::~Loop()
	{
		// Subsystems will be freed as stack is deconstructed
#ifdef _DEBUG
		delete debugSystem;
#endif
	}

	Loop& Loop::Instance()
	{
		static Loop instance;
		return instance;
	}

	Clock& Loop::GetClock()
	{
		return gameClock;
	}

	void Loop::Run()
	{
		StartUp();
		while (isRunning) 
		{
			Update();
		}
		ShutDown();
	}

	void Loop::Stop()
	{
		isRunning = false;
	}

	void Loop::StartUp()
	{
		Config::Instance().LoadFrom("D:\\TEngine\\TEngine\\Engine.ini");
		windowManager->StartUp();
		inputSystem->StartUp(windowManager->GetWindow());
		worldSystem->StartUp();
		renderSystem->StartUp(windowManager->GetWindow(), worldSystem);
#ifdef _DEBUG
		debugSystem->StartUp(windowManager->GetWindow());
#endif
	}

	void Loop::ShutDown()
	{
#ifdef _DEBUG
		debugSystem->ShutDown();
#endif
		renderSystem->ShutDown();
		worldSystem->ShutDown();
		inputSystem->ShutDown();
		windowManager->ShutDown();
	}

	/**
	* Handles the calling of fixed and variable update
	**/
	void Loop::Update()
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
	void Loop::FixedUpdate(const float32 timeStep)
	{
		worldSystem->FixedUpdate(timeStep);
#ifdef _DEBUG
		debugSystem->FixedUpdate(timeStep);
#endif
	}

	/**
	* Updates as fast as possible, not fixed
	**/
	void Loop::VariableUpdate(const float32 deltaTime)
	{
		inputSystem->Update();
		worldSystem->Update(deltaTime);
		renderSystem->Update(deltaTime);
#ifdef _DEBUG
		debugSystem->VariableUpdate(deltaTime);
#endif
		windowManager->Update(deltaTime);
	}
}
