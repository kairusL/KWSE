#pragma once


namespace KWSE
{
	class AppState;

	struct AppConfig
	{
		// Default Constructor 
		AppConfig() = default;

		AppConfig(std::wstring appName)
			: appName(std::move(appName))
		{}

		AppConfig(std::wstring appName, uint32_t windowWidth, uint32_t windowHeight)
			: appName(std::move(appName)), windowWidth(windowWidth), windonHeight(windowHeight)
		{}

		std::wstring appName = L"KWSE";
		uint32_t windowWidth = 1280;
		uint32_t windonHeight = 720;
	};

	class App
	{
	public:

		template <class StateType,class = std::void_t<std::is_base_of<AppState,StateType>>>
		void AddState(std::string stateName)
		{
			auto state = mAppStates.emplace(std::move(stateName), std::make_unique<StateType>());
			if (mCurrentState == nullptr)
			{
				LOG("App -- Starting state: &s", mCurrentState);
				mCurrentState = state.first->second.get();
			}
		}

		void ChangeState(const std::string& stateName);


		void Run(AppConfig appConfig);
		void Quit() { mRunning = false; }

	private:
		AppConfig mAppConfig;
		Core::Window mWindow;
		bool mRunning = false;

		// AppState
		std::map<std::string, std::unique_ptr<AppState>> mAppStates;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;

	};
}