#include <KWSE/Inc/KWSE.h>
#include"GameState.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{

	KWSE::MainApp().AddState<GameState>("GameState");

	KWSE::MainApp().Run({ L"Final Shadow Temp" });

	return 0;
}
