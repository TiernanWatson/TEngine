#include "Loop.h"
#include "Core/Config/Config.h"

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
	}

	Loop::~Loop()
	{
		// Subsystems will be freed as stack is deconstructed
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
	}

	void Loop::ShutDown()
	{
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

		// If game lags, make sure fixed update catchs up
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
	}

	/**
	* Updates as fast as possible, not fixed
	**/
	void Loop::VariableUpdate(const float32 deltaTime)
	{
		inputSystem->Update();
		worldSystem->Update(deltaTime);
		renderSystem->Update(deltaTime);
		windowManager->Update(deltaTime);
	}
}
