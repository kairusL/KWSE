#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace KWSE;
using namespace KWSE::Core;
using namespace KWSE::Graphics;
using namespace KWSE::Input;



void KWSE::App::ChangeState(const std::string & stateName)
{
	if (auto iter = mAppStates.find(stateName); iter!=mAppStates.end())
	{
		LOG("App -- Changing state: %s", stateName.c_str());
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
	mWindow.Initialize(GetModuleHandle(NULL), mAppConfig.appName.c_str(), mAppConfig.windowWidth,mAppConfig.windowHeight);

	auto handle = mWindow.GetWindowHandle();

	// Initialize the input system
	InputSystem::StaticInitialize(handle);

	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);
	SimpleDraw::StaticInitialize();
	DebugUI::StaticInitialize(handle);



	//Initialize the starting state
	ASSERT(mCurrentState, "App -- No app state found! App must have at lease one AppState.");
	mCurrentState->Initialize();

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

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}


		auto inputSystem = InputSystem::Get();
		inputSystem->Update();

		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
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

		DebugUI:: BeginRender();
		mCurrentState->DebugUI();
		DebugUI::EndRender();


		GraphicsSystem::Get()->EndRender();
	}
	
	LOG("APP -- Shutting down ...");

	// CleanState
	mCurrentState->Terminate();

	DebugUI::StaticTerminate();
	SimpleDraw::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	InputSystem::StaticTerminate();


	mWindow.Terminate();

	LOG("APP -- Exiting ...");

}