#include "Precompiled.h"
#include "App.h"

using namespace KWSE;
using namespace KWSE::Core;
using namespace KWSE::Graphics;



void App::Run()
{
	LOG("APP -- Running ...");

	// Setup our application window
	LOG("APP -- Creating window ...");

	mWindow.Initialize(GetModuleHandle(NULL), L"Hello DirectX", 1280, 720);

	auto handle = mWindow.GetWindowHandle();

	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);

	LOG("APP -- Entering main loop ...");


	mRunning = true;

	while (mRunning &&mWindow.IsActive())
	{

		mWindow.ProcessMessage();
		if (!mWindow.IsActive())
		{
			LOG("APP -- window destroyed. Exiting app ...");
			Quit();
			continue;
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			LOG("APP -- window destroyed. Exiting app ...");
			Quit();
			continue;
		}
	GraphicsSystem::Get()->BeginRender();

	// Draw stuff here...

	GraphicsSystem::Get()->EndRender();
	}


	GraphicsSystem::StaticTerminate();

	LOG("APP -- Shutting down ...");

	mWindow.Terminate();

	LOG("APP -- Exiting ...");

}