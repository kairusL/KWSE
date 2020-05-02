#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace KWSE;
using namespace KWSE::Core;
using namespace KWSE::Graphics;



void KWSE::App::ChangeState(const std::string & stateName)
{
	if (auto iter = mAppStates.find(stateName); iter!=mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}

void App::Run(AppConfig appConfig)
{
	LOG("APP -- Running ...");

	// Remove AppConfig default value 
	mAppConfig = std::move(appConfig);

	// Setup our application window
	LOG("APP -- Creating window ...");

	// Initialize timer
	TimeUtil::Initialize();

	// Import own value for the window  
	mWindow.Initialize(GetModuleHandle(NULL), mAppConfig.appName.c_str(), mAppConfig.windowWidth,mAppConfig.windonHeight);

	auto handle = mWindow.GetWindowHandle();

	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);

	LOG("APP -- Entering main loop ...");


	mRunning = true;

	while (mRunning &&mWindow.IsActive())
	{

		mWindow.ProcessMessage();
		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

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

		auto deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);

		GraphicsSystem::Get()->BeginRender();

		// Draw stuff here...
		mCurrentState->Render();


		GraphicsSystem::Get()->EndRender();
	}

	// CleanState
	mCurrentState->Terminate();

	GraphicsSystem::StaticTerminate();

	LOG("APP -- Shutting down ...");

	mWindow.Terminate();

	LOG("APP -- Exiting ...");

}