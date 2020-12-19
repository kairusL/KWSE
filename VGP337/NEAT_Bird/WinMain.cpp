#include <KWSE/Inc/KWSE.h>
#include"GameState.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	KWSE::AppConfig config;
	config.appName = L"Neat BIRD";
	config.windowHeight = 853;
	config.windowWidth = 480;
	KWSE::MainApp().AddState<GameState>("GameState");

	KWSE::MainApp().Run(config);

	return 0;
}