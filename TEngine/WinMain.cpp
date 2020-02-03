// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsOS.h"
#include "Core/Exception.h"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ PWSTR pCmdLine, 
	_In_ int nCmdShow)
{
	// Want to see exceptions in VS debugger in development
#ifndef _DEBUG
	try
	{
#endif
		TEngine::WindowsOS game(
			hInstance,
			pCmdLine,
			nCmdShow
		);

		game.Init();
		game.Run();

		return 0;
#ifndef _DEBUG
	}
	catch (TEngine::Exception const& e)
	{
		MessageBox(
			nullptr, 
			e.DisplayString(), 
			"Game Exception Thrown", 
			MB_OK | MB_ICONEXCLAMATION
		);
	}
	catch (std::exception const& e)
	{
		MessageBox(
			nullptr, 
			e.what(), 
			"STD Exception Thrown", 
			MB_OK | MB_ICONEXCLAMATION
		);
	}
	catch (...)
	{
		MessageBox(
			nullptr,
			"Unknown exception occurred",
			"Exception",
			MB_OK | MB_ICONEXCLAMATION
		);
	}

	return -1;
#endif
}
#endif  // PLATFORM_WINDOWS
