#include <KWSE/Inc/KWSE.h>
#include"GameState.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{

	KWSE::MainApp().AddState<GameState>("GameState");

	KWSE::MainApp().Run({ L"Genetic Algorithm  _  TSP" });

	return 0;
}