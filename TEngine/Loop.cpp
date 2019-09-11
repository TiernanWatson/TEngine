#include "Loop.h"

namespace TEngine
{
	Loop::Loop() 
	{
		windowManager = new WindowManager();
	}

	Loop::~Loop()
	{
		delete windowManager;
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

	void Loop::StartUp()
	{
		windowManager->StartUp();
	}

	void Loop::ShutDown()
	{
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
	* Updates at a fixed time step, defaulted to 50FPS
	**/
	void Loop::FixedUpdate(const float32 timeStep)
	{
		
	}

	/**
	* Updates as fast as possible, not fixed
	**/
	void Loop::VariableUpdate(const float32 deltaTime)
	{
		windowManager->Update(deltaTime);
	}
}
